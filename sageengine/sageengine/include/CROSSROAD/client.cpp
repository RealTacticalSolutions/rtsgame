#include "pchroads.h"
#include "client.h"


#include <random>
std::random_device rdclient; // obtain a random number from hardware
std::mt19937 genclient(rdclient()); // seed the generator

std::uniform_int_distribution<> distrclient(0, 200); // define the range

void client::startClient()
{
    // Initialize Winsock
    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cout << "WSAStartup failed with error: " << result << std::endl;
        return;
    }
    std::cout << "WSAStartup Succeeded " << std::endl;

    // Create a socket for the client
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }
    std::cout << "Socket Succeeded " << std::endl;

    // Resolve the server address and port
    struct addrinfo* addrResult = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    result = getaddrinfo(IP, PORT, &hints, &addrResult);
    if (result != 0) {
        std::cout << "getaddrinfo failed with error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }
    std::cout << "Getaddrinfo Succeeded " << std::endl;

    // Connect to the server
    result = connect(clientSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (result == SOCKET_ERROR) {
        std::cout << "connect failed with error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }
    std::cout << "Connect Succeeded " << std::endl;

    // Wait for the server to be ready
    std::unique_lock<std::mutex> lock(g_mutex);
    while (!g_serverReady) {
        g_conditionVariable.wait(lock);
    }

    //nlohmann::json data = 
    //{ 
    //    {{"id", 123},{"weight", 45.6}},
    //    {{"id", 63},{"weight", 75.6}}
    //};
    std::string id1 = "5.1";
    std::string id2 = "2.1";
    std::string id3 = "11.1";
    std::string id4 = "8.1";

    int weight1 = 0;
    int weight2 = 0;
    int weight3 = 0;
    int weight4 = 0;
    while (client_running) {
        // Send the message to the server
        std::vector<trafficStatusObject> messageclient = { { id1, weight1 }, {id2, weight2}, {id3, weight3}, {id4, weight4} };
        nlohmann::json dataclient;
        client::to_json_traffic(dataclient, messageclient);
        std::string dataStr = dataclient.dump(); // Convert the JSON object to a string
        const char* sendData = dataStr.c_str();
        int bytesSent = send(clientSocket, sendData, strlen(sendData), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            WSACleanup();
            return;
        }
        weight1 = distrclient(genclient);
        weight2 = distrclient(genclient);
        weight3 = distrclient(genclient);
        weight4 = distrclient(genclient);

        // Receive data from the server
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
        nlohmann::json dataserver = nlohmann::json::parse(recvBuf);
        for (const auto& obj : dataserver) {
            message.push_back({ obj["id"], obj["color"] });
            // Print the received data to the console
            std::cout << "Received struct from server: id = " << obj["id"] << ", color = " << obj["color"] << std::endl;
        }


        // Wait for 3.5 seconds before sending the next message
        Sleep(3500);
    }

    // Close the socket and clean up Winsock
    closesocket(clientSocket);
    WSACleanup();
    return;
}
void client::to_json(nlohmann::json& j, const messageObject& s) 
{
    j = nlohmann::json{ { {"id", s.id}, {"color", s.color}} };
}

void client::to_json_message(nlohmann::json& j, const std::vector<messageObject>& objects)
{
    j = nlohmann::json::array();
    for (const auto& obj : objects) {
        j.push_back(nlohmann::json{ {"id", obj.id}, {"color", obj.color} });
    }
}

void client::to_json_traffic(nlohmann::json & j, const std::vector<trafficStatusObject>&objects) 
{
    j = nlohmann::json::array();
    for (const auto& obj : objects) {
    j.push_back(nlohmann::json{ {"id", obj.id}, {"weight", obj.weight} });
    }
}
