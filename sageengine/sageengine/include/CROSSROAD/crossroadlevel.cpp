#include "pchroads.h"
#include "pch.h"
#include "crossroadlevel.h"
#include "color.h"



std::mutex g_mutex;
std::condition_variable g_conditionVariable;

bool g_serverReady = true;
bool server_running = true;
bool client_running = true;


void CrossRoadLevel::init()
{
    IP = "127.0.0.1";
    
    PORT = "11000";
    SERVER_PORT = "11000";

    myClient = new client(IP, PORT, message_ref, lights);
    myServer = new server(SERVER_PORT, lights);

    serverThread = std::thread(&server::startServer, *myServer);
    clientThread = std::thread(&client::startClient, *myClient);
}

void CrossRoadLevel::mainLoop()
{
    
    //Todo probably crashed because message object gets cleared, probably need a message buffer that only reads when the last one is handled
    for (messageObject m : message_ref)
    {
        //if(m.id.size() != 0 || m.color != -1 || m.color >2)
        if (m.id != "0")
        {
            try
            {
                // getId MUST because from string to gameobject index
                int index = getId(lights, m.id);
                if (index == -1)
                {
                    std::cout << "(CrossroadLevel Line 45)ERROR: Index Is -1 From: " << m.id << std::endl;
                    continue;
                }
                else
                {
                    updateColor(index, getColor(m.status));
                }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        else
        {
            std::cout << "message was not complete" << std::endl;
        }

        message_ref.clear();

    }
}

void CrossRoadLevel::cleanup()
{
    server_running = false;
    client_running = false;
    serverThread.join();
    clientThread.join();
    //delete myClient;
    //delete myServer;
}
void CrossRoadLevel::updateColor(int index, glm::vec3 color)
{
    gameObjects_ref[index].properties.color = color;
};