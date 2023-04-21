#pragma once



class renderer
{
private:
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	

	Camera& camera;

	const int MAX_FRAMES_IN_FLIGHT = 2;
	int objectCount;

	uint32_t currentFrame = 0;

	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"

	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
		VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
		VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
		VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME,
		VK_KHR_RAY_QUERY_EXTENSION_NAME,
		VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME
	};

	std::vector<RenderObject>& renderObjects;
	std::vector<GameObject>& gameObjects;
	std::vector<Mesh> meshes;
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;

	const int num_rows = 10; // number of rows in the grid
	const int num_cols = 10; // number of columns in the grid
	const float spacing = 0.1f; // spacing between grid points


	std::vector<Vertex> GenerateGridVertices(uint32_t xCells, uint32_t yCells, float cellSize);
	std::vector<uint16_t> GenerateGridIndices(uint32_t xCells, uint32_t yCells);

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{

		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}
	
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsAndComputeFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsAndComputeFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;

	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;
	
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;

	VkQueue computeQueue;
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkPipelineLayout computePipelineLayout;
	VkPipeline computePipeline;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkCommandBuffer> computeCommandBuffers;

	VkDescriptorPool descriptorPool;

	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorSetLayout computeDescriptorSetLayout;

	std::vector<VkDescriptorSet> descriptorSets;
	std::vector<VkDescriptorSet> computeDescriptorSets;

	//buffermanagers
	std::vector<Buffermanager> uniformBufferManagers;
	std::vector<Buffermanager> vertexBuffers;
	std::vector<Buffermanager> indexBuffers;

	Buffermanager transformBufferManager = {
		0,
		VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	};

	std::vector<Buffermanager> computeShaderBuffers;
	

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> computeFinishedSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> computeInFlightFences;

	VkImage textureImage;
	VkDeviceMemory textureImageMemory;

	std::vector<VkImage> textureImages;
	std::vector<VkDeviceMemory> textureImagesMemory;

	std::vector<VkImageView> textureImageViews;
	std::vector<VkSampler> textureSamplers;

	VkImageView textureImageView;
	VkSampler textureSampler;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	std::vector<VkAccelerationStructureBuildGeometryInfoKHR> accelerationStructureBuildGeometryInfos;

	std::vector<VkAccelerationStructureBuildRangeInfoKHR*> accelerationStructureBuildRangeInfos;

	std::vector<VkAccelerationStructureBuildSizesInfoKHR> bottomLevelAccelerationStructureBuildSizesInfos;
	VkAccelerationStructureBuildSizesInfoKHR topLevelAccelerationStructureBuildSizesInfo;

	std::vector<Buffermanager> bottomLevelAccelerationStructureBufferManagers;
	Buffermanager topLevelAccelerationStructureBufferManager;

	std::vector<AccelerationStructure> bottomLevelAccelerationStructures;
	AccelerationStructure topLevelAccelerationStructure;

	std::vector<VkAccelerationStructureGeometryKHR> bottomLevelAccelerationStructureGeometry;
	VkAccelerationStructureGeometryKHR topLevelAccelerationStructureGeometry;
	std::vector<uint32_t> maxPrimitveCounts;
	

	void cleanupVulkan();
	void cleanupSwapChain();
	void cleanupAccelerationStructures();

	void recreateSwapChain(GLFWwindow* window);
	void createInstance();
	void createSwapChain(GLFWwindow* window);
	void createImageViews();
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	void createRenderPass();
	void createDescriptorSetLayout();
	void createGraphicsPipeline();
	void createComputePipeline();
	void createFramebuffers();
	void createDepthResources();
	void createCommandPool();
	void createTextureImages();
	void createTextureImageViews();
	void createTextureSampler();
	void createBottomLevelAccelerationStructureGeometry(int index);
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void createAccelerationStructures();
	void createBottomLevelAccelerationStructure(int index);
	void createTopLevelAccelerationStructureGeometry();
	void createTopLevelAccelerationStructure(int index);
	uint64_t getBufferDeviceAddress(VkBuffer buffer);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	//Buffer creation functions
	Buffermanager createVertexbuffer(Mesh mesh);
	Buffermanager createIndexBuffer(Mesh mesh);
	Buffermanager createScratchBuffer(VkDeviceSize size);
	void createAccelerationStructureBuffer(AccelerationStructure& accelerationStructure, VkAccelerationStructureBuildSizesInfoKHR buildSizeInfo);
	void createTopLevelAccelerationStructureBuffer(std::vector<VkAccelerationStructureInstanceKHR> instances);
	void createTransformBuffer();
	void createUniformBuffers();
	void createComputeShaderBuffers();

	void createDescriptorPool();
	void createDescriptorSets();
	void createComputeDescriptorSetLayout();
	void createComputeDescriptorSets();
	void createBuffer(Buffermanager& bufferManager);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void createCommandBuffers();
	void createComputeCommandBuffers();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	void recordComputeCommandBuffer(VkCommandBuffer commandBuffer);
	void createSyncObjects();
	void updateUniformBuffer(uint32_t currentImage);
	bool checkValidationLayerSupport();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void setupDebugMessenger();
	void createSurface(GLFWwindow* window);
	void pickPhysicalDevice();
	void createLogicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool hasStencilComponent(VkFormat format);
	void updateTransformBuffer();

	VkCommandBuffer beginNewCommandBuffer();
	void flushCommandBuffer(VkCommandBuffer& commandBuffer);

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	std::vector<const char*> getRequiredExtensions();
	std::vector<char> readFile(const std::string& filename);
	
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat();

	VkDeviceAddress getAccelerationStructureDeviceAddressEXT(int index);
	void cmdBuildAccelerationStructuresEXT(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);
	VkResult createAccelerationStructureEXT(VkDevice device, const VkAccelerationStructureCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureKHR* pAccelerationStructure);
	void getAccelerationStructureBuildSizesEXT(VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo);
	void destroyAccelerationStructureEXT(VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator);
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);


	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

public:

	renderer(Camera& mainCamera, int objectCount, std::vector<RenderObject>& renderObjects, std::vector<GameObject>& gameObjects) : camera(mainCamera), objectCount(objectCount), renderObjects(renderObjects), gameObjects(gameObjects)
	{
		
	}

	~renderer()
	{
		cleanupVulkan();
		std::cout << "cleanupVulkan" << std::endl;
	}

	bool framebufferResized = false;


	void initVulkan(std::unique_ptr<window>& windowObject);
	void drawFrame(GLFWwindow* window);

	void createObject(RenderObject renderObject);
	void instantiateObject();
	void destroyObject();

	VkDevice getDevice();
};