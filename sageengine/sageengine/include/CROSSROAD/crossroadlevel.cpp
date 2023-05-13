#include "pchroads.h"
#include "pch.h"
#include "crossroadlevel.h"
#include "color.h"



std::mutex g_mutex;
std::condition_variable g_conditionVariable;


bool messagereadable = false;

bool g_serverReady = true;

bool server_running = true;
bool client_running = true;


void CrossRoadLevel::init()
{
    IP = "86.94.105.219";
    
    PORT = "11000";
    SERVER_PORT = "11000";

    myClient = new client(IP, PORT, message_ref, timer_ref, lights);
    //myServer = new server(SERVER_PORT, lights);

    //serverThread = std::thread(&server::startServer, *myServer);
    clientThread = std::thread(&client::startClient, *myClient);
}

void CrossRoadLevel::mainLoop()
{
    try {
        //Todo probably crashed because message object gets cleared, probably need a message buffer that only reads when the last one is handled
        if (messagereadable)
        {
            for (messageObject m : message_ref)
            {
                //if(m.id.size() != 0 || m.color != -1 || m.color >2)
                if (m.id.size() > 0)
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
                    std::cout << "m.id size 0" << std::endl;
                }

            }
            message_ref.clear();
            messagereadable = false;
        }
    }
    catch (std::length_error& e) {
        std::cerr << "Caught std::length_error exception: " << e.what() << std::endl;

    }

}

void CrossRoadLevel::cleanup()
{
    server_running = false;
    client_running = false;
    //serverThread.join();
    clientThread.join();
    //delete myClient;
    //delete myServer;
}
void CrossRoadLevel::updateColor(int index, glm::vec3 color)
{
    gameObjects_ref[index]->properties.color = color;
};