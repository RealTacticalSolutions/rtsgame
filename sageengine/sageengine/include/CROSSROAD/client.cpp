#include "pchroads.h"
#include "client.h"
#include <random>

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<> distr(0, 2); // define the range

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
    int id1 = 1;
    int id2 = 2;
    int id3 = 3;
    int id4 = 4;

    int color1 = 0;
    int color2 = 0;
    int color3 = 0;
    int color4 = 0;
    while (client_running) {
        // Send the message to the server
        std::vector<trafficObject> message = { { id1, color1 }, {id2, color2}, {id3, color3}, {id4, color4} };
        nlohmann::json data;
        client::to_json(data, message);
        std::string dataStr = data.dump(); // Convert the JSON object to a string
        const char* sendData = dataStr.c_str();
        int bytesSent = send(clientSocket, sendData, strlen(sendData), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            WSACleanup();
            return;
        }
        color1 = distr(gen);
        color2 = distr(gen);
        color3 = distr(gen);
        color4 = distr(gen);
        // Wait for 3.5 seconds before sending the next message
        Sleep(3500);
    }

    // Close the socket and clean up Winsock
    closesocket(clientSocket);
    WSACleanup();
    return;
}
void client::to_json(nlohmann::json& j, const trafficObject& s) {
    j = nlohmann::json{ { {"id", s.id}, {"color", s.color}} };
}

void client::to_json(nlohmann::json& j, const std::vector<trafficObject>& objects) {
    j = nlohmann::json::array();
    for (const auto& obj : objects) {
        j.push_back(nlohmann::json{ {"id", obj.id}, {"color", obj.color} });
    }
}
