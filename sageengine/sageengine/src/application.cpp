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

        //updateColor(1, glm::vec3(1.0f,1.0f,1.0f));
        updateColorAddition(1, glm::vec3(0.0001f, 0.0001f, 0.0001f));
        updateColorAddition(3, glm::vec3(0.0001f, 0.0001f, 0.0001f));
        updateColorAddition(4, glm::vec3(0.0001f, 0.0001f, 0.0001f));
        glfwPollEvents();
        updateTest();
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

    gameObjects.push_back(GameObject(
        { { {-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },
        { {0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },
        { {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} },
        { {-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} } },

        {  0, 1, 2, 2, 3, 0  },
        glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)), glm::vec3(1.0f,1.0f,1.0f)
        //glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
    ));
    uint32_t offSet = gameObjects[0].vertices.size();
    
    int xCells = 1;
    int yCells = 1;
    float cellSize = 0.05f;

    glm::vec3 color = glm::vec3(0.0f, 1.0f, 1.0f);
    glm::vec3 position1(-0.10f, 0.22f, 1.0f);
    glm::mat4 transform1(1.0f);
    transform1[3] = glm::vec4(position1, 1.0f);

    gameObjects.push_back(ShapeTool::creatSquare(cellSize, offSet,transform1,color));
 
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 position2(-0.22f, -0.10f, 1.0f);
    glm::mat4 transform2(1.0f);
    transform2[3] = glm::vec4(position2, 1.0f);
    gameObjects.push_back(ShapeTool::creatSquare(cellSize,offSet,transform2,color));

    color = glm::vec3(1.0f, 0.0f, 1.0f);
    glm::vec3 position3(0.22f, 0.10f, 1.0f);
    glm::mat4 transform3(1.0f);
    transform3[3] = glm::vec4(position3, 1.0f);
    gameObjects.push_back(ShapeTool::creatSquare(cellSize,offSet,transform3,color));

    color = glm::vec3(1.0f, 1.0f, 0.0f);
    glm::vec3 position4(0.10f, -0.22f, 1.0f);
    glm::mat4 transform4(1.0f);
    transform4[3] = glm::vec4(position4, 1.0f);
    gameObjects.push_back(ShapeTool::creatSquare(cellSize,offSet,transform4,color));

    glm::vec3 newPosition(0.0f, 1.0f, 1.0f);
    glm::mat4 transform(1.0f);
    transform[3] = glm::vec4(newPosition, 1.0f);
    gameObjects.push_back(ShapeTool::creatSquare(0.2f, offSet, transform, glm::vec3(1.0f, 0.0f, 0.0f)));

   

    bool test = 1;



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

void application::updateTest()
{
    // Check for intersection with another object
    if (Intersection::intersectSquares(gameObjects[5], gameObjects[1])) {
        return; // Don't update if there's an intersection
    }

    // Set the target position
    glm::vec3 target(-0.1f, -1.2f, 1.0f);

    // Get the current position of the object
    glm::vec3 position = glm::vec3(gameObjects[5].properties.transform[3]);

    // Calculate the direction from the current position to the target position
    glm::vec3 direction = glm::normalize(target - position);

    // Set the velocity
    float velocity = 0.00005f;

    // Calculate the new position based on the direction and velocity
    glm::vec3 new_pos = position + direction * velocity;

    // Update the position of the object using glm::translate
    gameObjects[5].properties.transform = glm::translate(glm::mat4(1.0f), new_pos);
}