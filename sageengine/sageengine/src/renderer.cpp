#include "pch.h"
#include "renderer.h"

#define VK_CHECK(result)                                \
if(result != VK_SUCCESS)                                \
{                                                       \
    std::cout <<"Error Code:" << result << std::endl;   \
    __debugbreak();                                     \
}                                                       \

void renderer::initVulkan()
{
    createInstance();
}

void renderer::cleanupVulkan()
{
    vkDestroyInstance(instance, nullptr);
}

void renderer::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    VK_CHECK((vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS));
}