#include "timerObject.h"
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

    while (client_running) {
        // Wait for 0.5 seconds before sending the next message
        Sleep(500);
        // Send the message to the server
        //std::vector<trafficStatusObject> messageclient = { { id1, weight1 }, {id2, weight2}, {id3, weight3}, {id4, weight4} };
        std::vector<trafficStatusObject> messageclient;
        for (size_t i = 0; i < lights.size(); i++)
        {
            messageclient.push_back(trafficStatusObject{ std::stod(lights[i].id), lights[i].weight});
            //std::cout << "Light ID: " << lights[i].id << " Light Weight : " << lights[i].weight << std::endl;
        }
        nlohmann::json dataclient;
        client::to_json_traffic(dataclient, messageclient);
        std::string dataStr = dataclient.dump(); // Convert the JSON object to a string
        dataStr += "\n"; // Add newline character
        const char* sendData = dataStr.c_str();
        int bytesSent = send(clientSocket, sendData, strlen(sendData), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            WSACleanup();
            return;
        }
        std::cout << "message created" << std::endl;

        // Receive data from the server
        char recvBuf[4096];
        int bytesReceived = recv(clientSocket, recvBuf, sizeof(recvBuf) - 1, 0); // subtract 1 from buffer size to leave space for null terminator
        if (bytesReceived == SOCKET_ERROR) {
            std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            WSACleanup();
            return;
        }

        std::cout << "message received" << std::endl;
        // Add null terminator to received data
        recvBuf[bytesReceived] = '\0';

        // Check if the received message is empty
        if (strlen(recvBuf) == 0) {
            continue; // If the message is empty, wait for the next one
        }


        // Todo:: temporary we need a buffer for messages, otherwise it overwrites and crashes
        while (!message.empty())
        {
            std::cout << "message wait loop" << std::endl;
            continue;
        }
        // Parse the JSON data into a vector of TrafficObjects
        try
        {
             nlohmann::json dataserver = nlohmann::json::parse(recvBuf);
            for (const auto& obj : dataserver["trafficlights"]) {
                //std::string id_str = obj["id"]; // read the id as a string
                //double id = std::stod(id_str);  // convert the id string to a double
                double id = obj["id"];
                std::stringstream ss;
                ss << std::fixed << std::setprecision(1) << id;
                std::string id_str = ss.str(); // convert the id double back to a string with one decimal point
                message.push_back({ id_str, obj["status"] });
                // Print the received data to the console   
                //std::cout << "Received struct from server: id = " << id << ", color = " << obj["status"] << std::endl;
                
            }

            timer.id = dataserver["timer"]["id"];
            timer.status = dataserver["timer"]["status"];
            timer.remainingTime = dataserver["timer"]["remainingTime"];
            

            std::cout << "timer ID: " << timer.id << " timer status: " << timer.status << " remainingtime: " << timer.remainingTime << std::endl;


            messagereadable = true;
            std::cout << "send message / data" << std::endl;
        }
		catch (const std::exception e)
		{
			std::cout << "error parsing json client" << std::endl;
		}
		

        
    }

    // Close the socket and clean up Winsock
    closesocket(clientSocket);
    WSACleanup();
    return;
}
void client::to_json(nlohmann::json& j, const messageObject& s) 
{
    j = nlohmann::json{ { {"id", s.id}, {"status", s.status}} };
}

void client::to_json_message(nlohmann::json& j, const std::vector<messageObject>& objects)
{
    j = nlohmann::json::array();
    for (const auto& obj : objects) {
        j.push_back(nlohmann::json{ {"id", obj.id}, {"status", obj.status} });
    }
}

void client::to_json_traffic(nlohmann::json & j, const std::vector<trafficStatusObject>&objects) 
{
    j = nlohmann::json::array();
    for (const auto& obj : objects) {
    j.push_back(nlohmann::json{ {"id", obj.id}, {"weight", obj.weight} });
    }
}
