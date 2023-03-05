#include "pch.h"
#include "application.h"
#include "CROSSROAD/pchroads.h"
#include "color.h"

std::mutex g_mutex;
std::condition_variable g_conditionVariable;
bool g_serverReady = false;
bool server_running = true;
bool client_running = true;

void application::mainLoop()
{
 
    char* IP = "192.168.178.52";
    char* PORT = "27015";
    char* SERVER_PORT = "27015";

    client myClient(IP, PORT);
    server myServer(SERVER_PORT, message);

    std::thread serverThread(&server::startServer, &myServer);
    std::thread clientThread(&client::startClient, &myClient);


    double lastFrameTime = glfwGetTime();
    double lastSecondTime = lastFrameTime;
    int fps = 0;
    char windowTitle[256];

    while (!windowObject->shouldClose())
    {
        double currentFrameTime = glfwGetTime();
        double delta = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        for (auto m : message)
        {
            updateColor(m.id, getColor(m.color));
        }
        glfwPollEvents();
        updateObject();
        drawFrame();

        fps++;
        if (currentFrameTime - lastSecondTime >= 1.0)
        {
            snprintf(windowTitle, 256, "FPS: %d", fps);
            glfwSetWindowTitle(windowObject->getWindow(), windowTitle);
            fps = 0;
            lastSecondTime = currentFrameTime;
        }
    }

    vkDeviceWaitIdle(vulkanrenderer->getDevice());
    server_running = false;
    client_running = false;
    serverThread.join();
    clientThread.join();
}

void application::drawFrame()
{
	vulkanrenderer->renderer::drawFrame(windowObject->getWindow());
}
void application::updateColor(int index, glm::vec3 color)
{
    gameObjects[index].properties.color = color;
};
void application::updateColorAddition(int index, glm::vec3 color)
{
    gameObjects[index].properties.color = gameObjects[index].properties.color + color;
};

std::vector<GameObject> application::constructGameobjects()
{
    

    gameObjects.push_back(GameObject(
        { { {-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },
        { {0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },
        { {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} },
        { {-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} } },

        {  0, 1, 2, 2, 3, 0  },
        glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)), glm::vec3(1.0f,1.0f,1.0f)
        //glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
    ));
    
    int xCells = 1;
    int yCells = 1;
    float cellSize = 0.1f;
    float xOffset = -0.15f;
    float yOffset = 0.17f;
    float zOffset = 1;
    uint32_t indicesoffset = gameObjects[0].vertices.size();
    glm::vec3 color = getColor(RED);
    glm::mat4 transform(1.0f);

    glm::vec3 origin (-0.15f, 0.17f, 2.0f);
    Grid::creatSquare(gameObjects, origin, cellSize, indicesoffset, transform, color);
    origin = glm::vec3(- 0.28f, -0.15f, 2.0f);
    Grid::creatSquare(gameObjects, origin, cellSize, indicesoffset, transform, color);
    origin = glm::vec3(0.17f, 0.05f, 2.0f);
    Grid::creatSquare(gameObjects, origin, cellSize, indicesoffset, transform, color);
    origin = glm::vec3(0.05f, -0.28f, 2.0f);
    Grid::creatSquare(gameObjects, origin, cellSize, indicesoffset, transform, color);
    origin = glm::vec3(0.17f, 0.05f, 2.0f);
    Grid::creatSquare(gameObjects, origin, cellSize, indicesoffset, transform, color);


    float cellsize = 0.25f;
    //glm::vec3 origin(-1.25f,-1.25f, 1.0f);
    glm::vec3 origin2(-0.1f, 1.0f, 1.0f);
    
    glm::vec3 color2(0.0f, 0.0f, 1.0f);
    float width = 0.5f;
    float height = 1.0f;

    Grid::createRectangle(gameObjects, origin2, width, height, indicesoffset, transform, color2);

    bool test = Intersection::intersection(gameObjects[1], gameObjects[6]);
    glm::vec3 target(-0.1f, -1.2f, 1.0f);
    glm::vec3 target_color(1.0f, 0.0f, 0.0f);
    Grid::createRectangle(gameObjects, target, 0.2, 0.2, indicesoffset, transform, target_color);
    







    int a = 5;
    /*gameObjects.push_back(GameObject(
        { { {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
        { {0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} },
        { {0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
        { {-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} } },

        {4, 5, 6, 6, 7, 4},

        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f))
    ));*/

   /* gameObjects.push_back(GameObject(
        { { {-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
        { {0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} },
        { {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
        { {-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} } },

        { 8, 9, 10, 10, 11, 8 },

        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
    ));*/



    return gameObjects;
}

void application::initWindow()
{
    
    gameObjects = constructGameobjects();
    int objectCount = gameObjects.size();
	vulkanrenderer = std::make_unique<renderer>(camera, objectCount, gameObjects);
	windowObject = std::make_unique<window>(WIDTH, HEIGHT, vulkanrenderer.get());
    

	vulkanrenderer->initVulkan(std::move(windowObject));

}

void application::cleanup()
{
}

glm::vec3 application::moveToTarget(glm::vec3 origin, glm::vec3 target, float velocity)
{
    glm::vec3 direction = glm::normalize(target - origin);
    glm::vec3 displacement = direction * velocity;
    glm::vec3 newOrigin = origin + displacement;

    return newOrigin;
}

//void application::updateObject()
//{
//    float velocity = 0.001f;
//    glm::vec3 target(-0.1f, -1.2f, 1.0f);
//
//    glm::mat4 test = gameObjects[6].properties.transform;
//    glm::vec3 origin(test[0].x, test[0].r, test[0].s);
//
//    glm::vec3 new_pos = moveToTarget(origin,target,velocity);
//    
//    glm::mat4 new_pos_mat4(1.0f);
//  
//    new_pos_mat4[0][0] = new_pos.x; // Assign the x component of the vector to the first element of the first column
//    new_pos_mat4[0][1] = new_pos.y; // Assign the y component of the vector to the second element of the first column
//    new_pos_mat4[0][2] = new_pos.z;
//    new_pos_mat4[0][3] = 1.0f;
//    gameObjects[6].properties.transform = new_pos_mat4;
//};

void application::updateObject()
{
    if (!Intersection::intersection(gameObjects[6], gameObjects[1]))
    {

        float velocity = 0.00001f;
        glm::vec3 target(-0.1f, -1.2f, 1.0f);

        // Get the current position of the object
        glm::mat4 transform = gameObjects[6].properties.transform;
        glm::vec3 position(transform[3].x, transform[3].y, transform[3].z);

        // Calculate the direction from the current position to the target position
        glm::vec3 direction = glm::normalize(target - position);

        // Calculate the new position based on the direction and velocity
        glm::vec3 new_pos = position + direction * velocity;
        // Update the position of the object using glm::translate
        glm::mat4 new_transform = glm::translate(glm::mat4(1.0f), new_pos);
        gameObjects[6].properties.transform = new_transform;
    }
    else
    {
    }
}