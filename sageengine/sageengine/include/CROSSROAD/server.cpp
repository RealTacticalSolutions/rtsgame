#include "pchroads.h"
#include "server.h"


void server::startServer()
{
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cout << "WSAStartup failed with error: " << result << std::endl;
        return;
    }
    std::cout << "WSAStartup Succeeded " << std::endl;

    // Create a socket for the server
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }
    std::cout << "Socket Succeeded " << std::endl;

    // Bind the socket to a local address and port
    struct addrinfo* addrResult = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(NULL, PORT, &hints, &addrResult);
    if (result != 0) {
        std::cout << "getaddrinfo failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return;
    }
    std::cout << "Getaddrinfo Succeeded " << std::endl;

    result = bind(listenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (result == SOCKET_ERROR) {
        std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(addrResult);
        closesocket(listenSocket);
        WSACleanup();
        return;
    }
    std::cout << "Bind Succeeded " << std::endl;

    freeaddrinfo(addrResult);

    // Listen for incoming connections
    result = listen(listenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return;
    }
    std::cout << "Listen Succeeded " << std::endl;

    // Notify the client thread that the server is ready
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_serverReady = true;
    }
    g_conditionVariable.notify_one();

    // Accept a client connection
    SOCKET clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return;
    }
    std::cout << "Socket Accept Succeeded " << std::endl;

    // // Receive data from the client
    //char recvBuf[4096];
    //int bytesReceived = recv(clientSocket, recvBuf, sizeof(recvBuf) - 1, 0); // subtract 1 from buffer size to leave space for null terminator
    //if (bytesReceived == SOCKET_ERROR) {
    //    std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
    //    closesocket(clientSocket);
    //    WSACleanup();
    //    return;
    //}
    //// Add null terminator to received data
    //recvBuf[bytesReceived] = '\0';


    //// Parse the JSON data into a vector of TrafficObjects

    //nlohmann::json data = nlohmann::json::parse(recvBuf);
    //for (const auto& obj : data) {
    //    message.push_back({ obj["id"], obj["color"] });
    //    // Print the received data to the console
    //    std::cout << "Received struct from client: id = " << obj["id"] << ", color = " << obj["color"] << std::endl;

    //}

    while (server_running) {
        // Receive data from the client
        char recvBuf[4096];
        int bytesReceived = recv(clientSocket, recvBuf, sizeof(recvBuf) - 1, 0); // subtract 1 from buffer size to leave space for null terminator
        if (bytesReceived == SOCKET_ERROR) {
            std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            WSACleanup();
            return;
        }
        // Add null terminator to received data
        recvBuf[bytesReceived] = '\0';

        // Check if the received message is empty
        if (strlen(recvBuf) == 0) {
            continue; // If the message is empty, wait for the next one
        }

        // Parse the JSON data into a vector of TrafficObjects
        nlohmann::json data = nlohmann::json::parse(recvBuf);
        for (const auto& obj : data) {
            message.push_back({ obj["id"], obj["color"] });
            // Print the received data to the console
            std::cout << "Received struct from client: id = " << obj["id"] << ", color = " << obj["color"] << std::endl;
        }

        // Clean message and fill it with new data
        message.clear();
    }

    // Close the client and server sockets and clean up Winsock
    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();
    return;
}