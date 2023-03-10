#include "pch.h"
#include "application.h"
#define PI 3.14159265;

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

        //updateColor(1, glm::vec3(1.0f,1.0f,1.0f));
        updateColorAddition(1, glm::vec3(0.0001f, 0.0001f, 0.0001f));
        updateColorAddition(3, glm::vec3(0.0001f, 0.0001f, 0.0001f));
        updateColorAddition(4, glm::vec3(0.0001f, 0.0001f, 0.0001f));
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
    std::vector<GameObject> gameObjects;

    gameObjects.push_back(GameObject(
        { { { {-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },
        { {0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },
        { {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} },
        { {-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} } },

        {  0, 1, 2, 2, 3, 0  } },
        glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)), glm::vec3(1.0f,1.0f,1.0f),

        "../../../textures/crossroadtexture1.jpg"
        //glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
    ));
    
    int xCells = 1;
    int yCells = 1;
    float cellSize = 0.1f;
    float xOffset = -0.15f;
    float yOffset = 0.17f;
    float zOffset = 1;
    indexOffset += gameObjects[0].mesh.vertices.size();
    glm::vec3 color = glm::vec3(0.0f, 1.0f, 1.0f);
    gameObjects.push_back(ShapeTool::generatePlane(xCells, yCells, cellSize, xOffset, yOffset, zOffset, indexOffset,color));
    indexOffset += gameObjects[1].mesh.vertices.size();
    xOffset = -0.28f;
    yOffset = -0.15f;
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    gameObjects.push_back(ShapeTool::generatePlane(xCells, yCells, cellSize, xOffset, yOffset, zOffset, indexOffset, color));
    indexOffset += gameObjects[2].mesh.vertices.size();
    xOffset = 0.17f;
    yOffset = 0.05f;
    color = glm::vec3(1.0f, 0.0f, 1.0f);
    gameObjects.push_back(ShapeTool::generatePlane(xCells, yCells, cellSize, xOffset, yOffset, zOffset, indexOffset, color));
    indexOffset += gameObjects[3].mesh.vertices.size();
    xOffset = 0.05f;
    yOffset = -0.28f;
    color = glm::vec3(1.0f, 1.0f, 0.0f);
    gameObjects.push_back(ShapeTool::generatePlane(xCells, yCells, cellSize, xOffset, yOffset, zOffset, indexOffset, color));
    indexOffset += gameObjects[4].mesh.vertices.size();


    glm::vec4 gridStart = glm::vec4(gameObjects[0].mesh.vertices[0].pos, 1.0f) * gameObjects[0].properties.transform;
    glm::vec4 gridEnd = glm::vec4(gameObjects[0].mesh.vertices[2].pos, 1.0f) * gameObjects[0].properties.transform;
    float cellCount = 1;
    gameObjects.push_back(ShapeTool::generateGrid(gridStart, gridEnd, cellCount, indexOffset));

    return gameObjects;
}

void application::initWindow()
{
    gameObjects = constructGameobjects();
    int objectCount = gameObjects.size();
    camera.setPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	vulkanrenderer = std::make_unique<renderer>(camera, objectCount, gameObjects);
	windowObject = std::make_unique<window>(WIDTH, HEIGHT, vulkanrenderer.get());
    

	vulkanrenderer->initVulkan(std::move(windowObject));

}

void application::cleanup()
{
}

