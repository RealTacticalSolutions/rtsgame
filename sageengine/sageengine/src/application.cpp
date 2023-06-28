#include "pch.h"
#include "application.h"
#include "color.h"

#include <random>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

void application::mainLoop()
{
	// level(message, timer, scene.gameObjects, lights);

    float cameraSpeed = 2.0f;
    float sensitivity = 0.1f;
    glm::vec2 centerPos = glm::vec2(WIDTH, HEIGHT) / 2.0f;
    glm::vec2 lastCursorPos = centerPos;	
	

	double lastFrameTime = glfwGetTime();
	double lastSecondTime = lastFrameTime;
	int fps = 0;
	char windowTitle[256];
	Input input = Input(windowObject.get()->getWindow());
	//level.init();
	while (!windowObject->shouldClose())
	{
        checkLevel();
		double currentFrameTime = glfwGetTime();
		double delta = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;
		
		
		//updateColorAddition(0, glm::vec3(0.0001f, 0.0001f, 0.0001f));
		glfwPollEvents();

		//level.mainLoop();
		drawFrame();

		


		fps++;
		if (currentFrameTime - lastSecondTime >= 1.0)
		{
			snprintf(windowTitle, 256, "FPS: %d", fps);
			glfwSetWindowTitle(windowObject->getWindow(), windowTitle);
			fps = 0;
			lastSecondTime = currentFrameTime;
		}
	
	
		glm::vec2 cursorPos = input.getCursorPos();
        bool spacePressed = input.keyDown(GLFW_KEY_SPACE);
        bool ePressed = input.keyDown(GLFW_KEY_E);
        bool isRotating = input.mouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
        bool isLookingAt = input.mouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT);

        bool w = input.keyPressed(GLFW_KEY_W);
        bool a = input.keyPressed(GLFW_KEY_A);
        bool s = input.keyPressed(GLFW_KEY_S);
        bool d = input.keyPressed(GLFW_KEY_D);

        input.updateInput();
        //camera.rotateCamera(0.005f);

        // Move camera position using WASD keys
        if (w)
        {
            camera.moveForward(delta, cameraSpeed);
        }
        if (a)
        {
            camera.moveLeft(delta, cameraSpeed );
        }
        if (s)
        {
            camera.moveBackward(delta, cameraSpeed );
        }
        if (d)
        {
            camera.moveRight(delta, cameraSpeed );
        }

        if (spacePressed) {
            /*int width = 0, height = 0;
            glfwGetFramebufferSize(windowObject.get()->getWindow(), &width, &height);
            glm::vec3 worldpos = GameMath::windowToWorldPos(cursorPos, glm::vec2(width, height), camera);

            glm::vec3 direction = worldpos - camera.position;
            
            scene.renderer.get()->initRaycast(camera.position, direction);*/
            
        }

        if (ePressed) {
            glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, -0.5f, 0.0f));
            scene.instantiateObject(scene.bluePrints[2], matrix, glm::vec3(0.6f));
            scene.renderer.get()->addInstance(matrix);
        }

        glm::vec2 cursorDelta = cursorPos - lastCursorPos;
        lastCursorPos = cursorPos;

        if (isLookingAt)
        {
            camera.moveLookAt(cursorDelta, sensitivity);
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

	//level.cleanup();

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

void application::constructGameobjects()
{
	scene.renderObjects.reserve(10);


	scene.blueprintObject(ShapeTool::createRectangle(3.2f, 1.8f), "../../../textures/kruispunt.png");

	scene.blueprintObject(ShapeTool::createSquare(0.07f), "../../../textures/light.jpg");

	scene.blueprintObject(loadModel("../../../models/room.obj"), "../../../textures/room.png");

    scene.blueprintObject(ShapeTool::createSquare(0.10f), "../../../textures/1.jpg");


}

void application::initWindow()
{
    constructGameobjects();
    start();
    int objectCount = scene.bluePrints.size();
    camera.setPosition(glm::vec3(0.0f, 0.0f, 15.0f));
    camera.setLookPosition(glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f,1.0f,0.0f));
    //camera.rotateCamera(180.0f);
	vulkanrenderer = std::make_unique<renderer>(camera, objectCount, scene.renderObjects, scene.gameObjects);
	windowObject = std::make_unique<window>(WIDTH, HEIGHT, vulkanrenderer.get());

	vulkanrenderer->initVulkan(std::move(windowObject));
    scene.renderer = std::move(vulkanrenderer);

}

void application::start()
{
	//scene.instantiateObject(scene.bluePrints[0], glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

	//scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,2.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

}

void application::cleanup()
{
}

void application::checkLevel()
{
    int templevel = currentLevel;

    if (!(lastLevel == templevel))
    {
    
        lastLevel = templevel;

        loadLevel(templevel);
    }
}

void application::loadLevel(int level)
{
    scene.gameObjects.clear();
    if (level == 1)
    {
        Level1();
    }
    if (level == 2)
    {
        Level2();
    }
}

void application::Level1()
{
    scene.instantiateObject(scene.bluePrints[0], glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

}


void application::Level2()
{
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(7.0f, 7.0f, 7.0f));
    int rows = 5;
    int collums = 5;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t y = 0; y < collums; y++)
        {

            glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.6f + (y * 0.3f), -0.6f + (i * 0.3f), 0.0f));
            scene.instantiateObject(scene.bluePrints[3], scaleMatrix * translationMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        }
    }


        
        

        

        glm::mat4 translationMatrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f));
        scene.instantiateObject(scene.bluePrints[3], scaleMatrix * translationMatrix2, glm::vec3(1.0f, 1.0f, 1.0f));


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

            if (index.normal_index >= 0) {
                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };
            }
           
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

