#include "pch.h"
#include "application.h"

void application::mainLoop()
{
    double lastFrameTime = glfwGetTime();
    double lastSecondTime = lastFrameTime;
    int fps = 0;
    char windowTitle[256];
    Input input = Input(windowObject.get()->getWindow());

    while (!windowObject->shouldClose())
    {
        double currentFrameTime = glfwGetTime();
        double delta = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        //updateColorAddition(0, glm::vec3(0.0001f, 0.0001f, 0.0001f));
        glfwPollEvents();
        drawFrame();

        glm::vec2 cursorPos = input.getCursorPos();
        bool spacePressed = input.keyPressed(GLFW_KEY_SPACE);
        bool test = input.keyDown(GLFW_KEY_SPACE);

        input.updateInput();

        if (test) {
            scene.removeObject(0);
            int width = 0, height = 0;
            
            glfwGetFramebufferSize(windowObject.get()->getWindow(), &width, &height);
            glm::vec3 worldpos = GameMath::windowToWorldPos(cursorPos, glm::vec2(width, height), camera);
           // std::cout << "cursor X: " << cursorPos.x << "  cursor Y: " << cursorPos.y << std::endl;
            //std::cout << "world X: " << worldpos.x << "  world Y: " << worldpos.y << "  world Z: " << worldpos.z << std::endl;
            //scene.addObject();
        }

        fps++;
        if (currentFrameTime - lastSecondTime >= 1.0)
        {                   
            snprintf(windowTitle, 256, "FPS: %d", fps);
            glfwSetWindowTitle(windowObject->getWindow(), windowTitle);
            fps = 0;
            lastSecondTime = currentFrameTime;
        }
    }
    vkDeviceWaitIdle(scene.renderer->getDevice());
}

void application::drawFrame()
{
	scene.renderer->renderer::drawFrame(windowObject->getWindow());
}
void application::updateColor(int index, glm::vec3 color)
{
    scene.gameObjects[index].properties.color = color;
};
void application::updateColorAddition(int index, glm::vec3 color)
{
    scene.gameObjects[index].properties.color = scene.gameObjects[index].properties.color + color;
};

void application::constructGameobjects()
{
    scene.blueprintObject(ShapeTool::createSquare(0.5f), "../../../textures/1.jpg");

   /* glm::vec4 gridStart = glm::vec4(scene.gameObjects[0].mesh.vertices[0].pos, 1.0f) * scene.gameObjects[0].properties.transform;
    glm::vec4 gridEnd = glm::vec4(scene.gameObjects[0].mesh.vertices[2].pos, 1.0f) * scene.gameObjects[0].properties.transform;
    float cellCount = 1;

    scene.blueprintObject(ShapeTool::generateGrid(gridStart, gridEnd, cellCount));*/
}

void application::initWindow()
{
    constructGameobjects();
    start();
    int objectCount = scene.bluePrints.size();
    camera.setPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	vulkanrenderer = std::make_unique<renderer>(camera, objectCount, scene.renderObjects, scene.gameObjects);
	windowObject = std::make_unique<window>(WIDTH, HEIGHT, vulkanrenderer.get());

	vulkanrenderer->initVulkan(std::move(windowObject));
    scene.renderer = std::move(vulkanrenderer);
}

void application::start()
{
    scene.instantiateObject(scene.bluePrints[0], glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

    scene.instantiateObject(scene.bluePrints[0], glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 1.1f)), glm::vec3(1.0f, 1.0f, 1.0f));

    scene.instantiateObject(scene.bluePrints[0], glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.1f)), glm::vec3(1.0f, 1.0f, 1.0f));
}

void application::cleanup()
{
}

/*void application::updateTest()
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
    
}*/

