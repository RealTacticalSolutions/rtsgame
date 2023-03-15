#include "pch.h"
#include "application.h"
#include "CROSSROAD/pchroads.h"
#include "color.h"
#include "CROSSROAD/crossroadlevel.h"

void application::mainLoop()
{
 
    CrossRoadLevel level(message, gameObjects);

    level.init();

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
        
        glfwPollEvents();

        level.mainLoop();
        updateTest();
        updateWayPoints();
        drawFrame();

        glm::vec2 cursorPos = input.getCursorPos();
        bool spacePressed = input.keyPressed(GLFW_KEY_SPACE);
        bool test = input.keyDown(GLFW_KEY_SPACE);

        input.updateInput();

        if (test) {
            std::cout << "X: " << cursorPos.x << "  Y: " << cursorPos.y << std::endl;
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

    vkDeviceWaitIdle(vulkanrenderer->getDevice());
    level.cleanup();
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
        { { { {-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },
        { {0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },
        { {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} },
        { {-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} } },

        {  0, 1, 2, 2, 3, 0  } },
        glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)), glm::vec3(1.0f,1.0f,1.0f),

        "../../../textures/crossroadtexture1.jpg"
        //glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
    ));
    uint32_t offSet = gameObjects[0].mesh.vertices.size();
    
    int xCells = 1;
    int yCells = 1;

    float cellSize = 0.05f;

    glm::vec3 color = glm::vec3(1.0f,0.0f,0.0f);
    glm::vec3 position1(-0.10f, 0.22f, 1.0f);
    glm::mat4 transform1(1.0f);
    transform1[3] = glm::vec4(position1, 1.0f);

    gameObjects.push_back(ShapeTool::createSquare(cellSize, offSet,transform1,color));
 

    glm::vec3 position2(-0.22f, -0.10f, 1.0f);
    glm::mat4 transform2(1.0f);
    transform2[3] = glm::vec4(position2, 1.0f);
    gameObjects.push_back(ShapeTool::createSquare(cellSize,offSet,transform2,color));

    glm::vec3 position3(0.22f, 0.10f, 1.0f);
    glm::mat4 transform3(1.0f);
    transform3[3] = glm::vec4(position3, 1.0f);
    gameObjects.push_back(ShapeTool::createSquare(cellSize,offSet,transform3,color));

    glm::vec3 position4(0.10f, -0.22f, 1.0f);
    glm::mat4 transform4(1.0f);
    transform4[3] = glm::vec4(position4, 1.0f);
    gameObjects.push_back(ShapeTool::createSquare(cellSize,offSet,transform4,color));


    glm::vec3 newPosition(0.0f, 1.0f, 1.0f);
    glm::mat4 transform(1.0f);
    transform[3] = glm::vec4(newPosition, 1.0f);
    gameObjects.push_back(ShapeTool::createSquare(0.2f, offSet, transform, glm::vec3(1.0f, 0.0f, 0.0f)));

    glm::vec3 newPosition5(0.0f, -1.0f, 1.0f);
    glm::mat4 transform5(1.0f);
    transform5[3] = glm::vec4(newPosition5, 1.0f);
    WayPoints waypoints ({ glm::vec3(newPosition5) ,glm::vec3(0.0f,1.0f,1.0f), glm::vec3(1.5f,1.0f,1.0f) });
    gameObjects.push_back(ShapeTool::createSquare(0.2f, offSet, transform5, glm::vec3(1.0f, 0.0f, 0.0f)));
    gameObjects.back().waypoints = waypoints;

    glm::vec3 newPosition6(0.0f, -1.5f, 1.0f);
    glm::mat4 transform6(1.0f);
    transform6[3] = glm::vec4(newPosition6, 1.0f);
    WayPoints waypoints2({ glm::vec3(newPosition6) ,glm::vec3(0.0f,0.0f,1.0f), glm::vec3(1.5f,0.0f,1.0f) });
    gameObjects.push_back(ShapeTool::createSquare(0.2f, offSet, transform6, glm::vec3(1.0f, 1.0f, 0.0f)));
    gameObjects.back().waypoints = waypoints2;

   
    bool test = 1;


    glm::vec4 gridStart = glm::vec4(gameObjects[0].mesh.vertices[0].pos, 1.0f) * gameObjects[0].properties.transform;
    glm::vec4 gridEnd = glm::vec4(gameObjects[0].mesh.vertices[2].pos, 1.0f) * gameObjects[0].properties.transform;
    float cellCount = 1;
    gameObjects.push_back(ShapeTool::generateGrid(gridStart, gridEnd, cellCount, offSet));

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

void application::updateTest()
{
    // Check for intersection with another object
    if ((Intersection::intersectSquares(gameObjects[5], gameObjects[1])) && gameObjects[1].properties.color == getColor(RED)) 
    {
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

    if (approxEqual(position, target, 0.15f))
    {
        gameObjects[5].properties.transform = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,1.0f,1.0f));
    }
    else
    { 
    // Update the position of the object using glm::translate
    gameObjects[5].properties.transform = glm::translate(glm::mat4(1.0f), new_pos);
    }

}
    

bool application::approxEqual(glm::vec3 a, glm::vec3 b, float epsilon)
{
    return glm::all(glm::lessThanEqual(glm::abs(a - b), glm::vec3(epsilon)));
}

void application::updateWayPoints()
{
    for (size_t i = 0; i < gameObjects.size(); i++)
    {
        int waypointsize = gameObjects[i].waypoints.getSize() -1;
        if (!(waypointsize <= 0)) 
        {
            // Check for intersection with another object
            if ((Intersection::intersectSquares(gameObjects[i], gameObjects[4])) && gameObjects[4].properties.color == getColor(RED))
            {
                return; // Don't update if there's an intersection
            }
            int currentwaypoint = gameObjects[i].waypoints.getCurrentWayPoint();
            int nextwaypoint = -1;
            if (currentwaypoint == waypointsize)
            {
                nextwaypoint = currentwaypoint;
            }
            else
            {
                nextwaypoint = (currentwaypoint+1);
            }

            // Set the target position
            glm::vec3 target = gameObjects[i].waypoints.getWayPoint(nextwaypoint);

            // Get the current position of the object
            glm::vec3 position = glm::vec3(gameObjects[i].properties.transform[3]);

            // Calculate the direction from the current position to the target position
            glm::vec3 direction = glm::normalize(target - position);

            // Set the velocity
            float velocity = 0.00005f;

            // Calculate the new position based on the direction and velocity
            glm::vec3 new_pos = position + direction * velocity;
            if (approxEqual(position, target, 0.15f))
            {
                if (currentwaypoint == waypointsize)
                {
                    gameObjects[i].waypoints.setCurrentWayPoint(0);
                    gameObjects[i].properties.transform = glm::translate(glm::mat4(1.0f), gameObjects[i].waypoints.getWayPoint(0));
                }
                else
                {

                    gameObjects[i].waypoints.setCurrentWayPoint(nextwaypoint);
                    gameObjects[i].properties.color = glm::vec3(0.0f, 1.0f, 0.0f);
                }
            }
            else
            {
                // Update the position of the object using glm::translate
                gameObjects[i].properties.transform = glm::translate(glm::mat4(1.0f), new_pos);
            }
        }
    }
}