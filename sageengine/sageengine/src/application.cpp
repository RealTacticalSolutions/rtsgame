#include "pch.h"
#include "application.h"

void application::mainLoop()
{
    double lastFrameTime = glfwGetTime();
    double lastSecondTime = lastFrameTime;
    int fps = 0;
    char windowTitle[256];

    while (!windowObject->shouldClose())
    {
        double currentFrameTime = glfwGetTime();
        double delta = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        glfwPollEvents();
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
}

void application::drawFrame()
{
	vulkanrenderer->renderer::drawFrame(windowObject->getWindow());
}

std::vector<GameObject> application::constructGameobjects()
{
    std::vector<GameObject> gameObjects;

    gameObjects.push_back(GameObject(
        { { {-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },
        { {0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },
        { {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} },
        { {-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} } },

        {  0, 1, 2, 2, 3, 0  },

        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
    ));
    int xCells = 2;
    int yCells = 2;
    float cellSize = 1.0f;
    int xOffset = 0;
    int yOffset = 0;
    int zOffset = 0;
    uint32_t indicesoffset = gameObjects[0].vertices.size();
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
    gameObjects.push_back(ShapeTool::generateGrid(xCells, yCells, cellSize, xOffset, yOffset, zOffset, indicesoffset,color));
    indicesoffset += gameObjects[1].vertices.size();
    xOffset = 0;
    yOffset = -3;
    zOffset = 0;
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    gameObjects.push_back(ShapeTool::generateGrid(xCells, yCells, cellSize, xOffset, yOffset, zOffset, indicesoffset, color));

    //gameObjects.push_back(GameObject(
    //    { { {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
    //    { {0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} },
    //    { {0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
    //    { {-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} } },

    //    {4, 5, 6, 6, 7, 4},

    //    glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f))
    //));

    //gameObjects.push_back(GameObject(
    //    { { {-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
    //    { {0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} },
    //    { {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
    //    { {-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} } },

    //    { 8, 9, 10, 10, 11, 8 },

    //    glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
    //));



    return gameObjects;
}

void application::initWindow()
{
    
    std::vector gameObjects = constructGameobjects();
    int objectCount = gameObjects.size();
	vulkanrenderer = std::make_unique<renderer>(camera, objectCount, gameObjects);
	windowObject = std::make_unique<window>(WIDTH, HEIGHT, vulkanrenderer.get());
    

	vulkanrenderer->initVulkan(std::move(windowObject));

}

void application::cleanup()
{
}