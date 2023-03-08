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

Mesh generateLine(uint16_t indexoffset, float linewidth, float length, glm::vec3 position, float rotationDeg, glm::vec3 rotationAxis, glm::vec3 color) {
    int i = indexoffset;

    Mesh mesh = {{ 
            {   {0.0f, 0.0f, 0.01f}, color, {0.5f, 0.0f} },
            {   {linewidth, 0.0f, 0.01f}, color, {0.5f, 0.0f} },
            {   {linewidth, length, 0.01f}, color, {0.5f, 0.0f} },
            {   {0.0f, length, 0.01f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.0f} },
        },

        {(uint16_t)(i), (uint16_t)(i + 1), (uint16_t)(i + 2), (uint16_t)(i), (uint16_t)(i + 2), (uint16_t)(i + 3)}
    };

    for (int i = 0; i < 4; i++) {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::rotate(transform, -glm::radians(rotationDeg), rotationAxis);
        mesh.vertices[i].pos = transform  * glm::vec4(mesh.vertices[i].pos, 1.0f);
    }

    return mesh;
}

GameObject generateGrid(glm::vec4 startingpos, glm::vec4 endpos, float cellSize, uint16_t indexOffset) {
    Mesh grid;
    size_t cellCountX = 10;
    size_t cellCountY = 10;

    float xLength = endpos.x - startingpos.x;
    float yLength = endpos.y - startingpos.y;

    for (size_t x = 0; x <= cellCountX; x++)
    {
        Mesh temp = generateLine(indexOffset, 0.01, yLength, glm::vec3(startingpos.x + (xLength / cellCountX) * x, startingpos.y, 0.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.1f,1.0f,0.1f));
        grid.vertices.insert(grid.vertices.end(), temp.vertices.begin(), temp.vertices.end());
        grid.indices.insert(grid.indices.end(), temp.indices.begin(), temp.indices.end());
        indexOffset += 4;
    }

    for (size_t y = 0; y <= cellCountY; y++)
    {
        Mesh temp = generateLine(indexOffset, 0.01, xLength, glm::vec3(startingpos.x, startingpos.y + (yLength / cellCountY) * y, 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.1f, 1.0f, 0.1f));
        grid.vertices.insert(grid.vertices.end(), temp.vertices.begin(), temp.vertices.end());
        grid.indices.insert(grid.indices.end(), temp.indices.begin(), temp.indices.end());
        indexOffset += 4;
    }

    return GameObject(grid, glm::mat4(1.0f), glm::vec3(1.0f));
}

std::vector<GameObject> application::constructGameobjects()
{
    std::vector<GameObject> gameObjects;

    gameObjects.push_back(GameObject(
        { { { {-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },
        { {0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },
        { {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} },
        { {-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} } },

        {  0, 1, 2, 2, 3, 0  } },
        glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)), glm::vec3(1.0f,1.0f,1.0f)
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
    gameObjects.push_back(ShapeTool::generateGrid(xCells, yCells, cellSize, xOffset, yOffset, zOffset, indexOffset,color));
    indexOffset += gameObjects[1].mesh.vertices.size();
    xOffset = -0.28f;
    yOffset = -0.15f;
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    gameObjects.push_back(ShapeTool::generateGrid(xCells, yCells, cellSize, xOffset, yOffset, zOffset, indexOffset, color));
    indexOffset += gameObjects[2].mesh.vertices.size();
    xOffset = 0.17f;
    yOffset = 0.05f;
    color = glm::vec3(1.0f, 0.0f, 1.0f);
    gameObjects.push_back(ShapeTool::generateGrid(xCells, yCells, cellSize, xOffset, yOffset, zOffset, indexOffset, color));
    indexOffset += gameObjects[3].mesh.vertices.size();
    xOffset = 0.05f;
    yOffset = -0.28f;
    color = glm::vec3(1.0f, 1.0f, 0.0f);
    gameObjects.push_back(ShapeTool::generateGrid(xCells, yCells, cellSize, xOffset, yOffset, zOffset, indexOffset, color));
    indexOffset += gameObjects[4].mesh.vertices.size();


    glm::vec4 gridStart = glm::vec4(gameObjects[0].mesh.vertices[0].pos, 1.0f) * gameObjects[0].properties.transform;
    glm::vec4 gridEnd = glm::vec4(gameObjects[0].mesh.vertices[2].pos, 1.0f) * gameObjects[0].properties.transform;
    float cellCount = 1;
    gameObjects.push_back(generateGrid(gridStart, gridEnd, cellCount, indexOffset));


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
    camera.setPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	vulkanrenderer = std::make_unique<renderer>(camera, objectCount, gameObjects);
	windowObject = std::make_unique<window>(WIDTH, HEIGHT, vulkanrenderer.get());
    

	vulkanrenderer->initVulkan(std::move(windowObject));

}

void application::cleanup()
{
}

