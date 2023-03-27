#include "pch.h"
#include "application.h"


#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

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
            int width = 0, height = 0;
            glfwGetFramebufferSize(windowObject.get()->getWindow(), &width, &height);
            glm::vec3 worldpos = GameMath::windowToWorldPos(cursorPos, glm::vec2(width, height), camera);
            glm::mat4 test = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
            scene.instantiateObject(scene.bluePrints[0], glm::translate(test, worldpos), glm::vec3(1.0f));
            
            
           
            
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

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
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
    scene.renderObjects.reserve(10);

    scene.blueprintObject(ShapeTool::createSquare(0.5f), "../../../textures/1.jpg");

    scene.blueprintObject(ShapeTool::createSquare(0.1f));

    scene.blueprintObject(loadModel("../../../models/room.obj"), "../../../textures/room.png");

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
    //scene.instantiateObject(scene.bluePrints[0], glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

    //scene.instantiateObject(scene.bluePrints[0], glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 1.1f)), glm::vec3(1.0f, 1.0f, 1.0f));

   // scene.instantiateObject(scene.bluePrints[0], glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.1f)), glm::vec3(1.0f, 1.0f, 1.0f));

    //scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), glm::vec3(0.4f, 0.4f, 1.2f)), glm::vec3(1.5f, 0.5f, 0.5f));

    scene.instantiateObject(scene.bluePrints[2], glm::mat4(1.0f), glm::vec3(1.0f));
}

void application::cleanup()
{
}

Mesh application::loadModel(char* path) {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path)) {
        throw std::runtime_error(warn + err);
    }

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = { 1.0f, 1.0f, 1.0f };

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }

            indices.push_back(uniqueVertices[vertex]);
        }
    }

    return Mesh({
        vertices, indices
    });
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

