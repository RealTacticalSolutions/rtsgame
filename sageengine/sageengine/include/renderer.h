#pragma once

/***************************************************************************
								RENDERER CLASS
***************************************************************************/

/**
*	This class services as the layer that performs al Vulkan operations and holds all its resources
*/

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
	bool enableRaytracing = false;

	uint32_t currentFrame = 0;

	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	std::vector<char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
		VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME,
		VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
	};

	std::vector<char*> rayTracingExtensions = {
		VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
		VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME,
		VK_KHR_RAY_QUERY_EXTENSION_NAME,
	};

	std::vector<char*> enabledExtensions;

	std::vector<RenderObject>& renderObjects;
	std::vector<std::unique_ptr<GameObject>>& gameObjects;
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
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> computeFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value() && computeFamily.has_value();
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
	VkPipeline graphicsPipelineLINE;

	VkPipelineLayout computePipelineLayout;
	VkPipeline computePipeline;

	VkCommandPool commandPool;
	VkCommandPool computeCommandPool;
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
		VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	};

	std::vector<Buffermanager> computeShaderBuffers;
	

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> raycastFinishedSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> raycastInFlightFences;

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
	
	std::vector<RayCast> rayCasts;
	std::vector<VkAccelerationStructureInstanceKHR> instances;

	VkAccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfo{};

	GLFWwindow* currentWindow;

	/*
	 * @brief Cleans up Vulkan resources.
	 */
	void cleanupVulkan();

	/*
	 * @brief Cleans up the swap chain resources.
	 */
	void cleanupSwapChain();

	/*
	 * @brief Cleans up acceleration structures and its related ressources.
	 */
	void cleanupAccelerationStructures();

	/*
	 * @brief Recreates the swap chain.
	 *
	 * @param window The GLFW window.
	 */
	void recreateSwapChain(GLFWwindow* window);

	/*
	 * @brief Creates the Vulkan instance.
	 */
	void createInstance();

	/*
	 * @brief Creates a swap chain.
	 *
	 * @param window The GLFW window.
	 */
	void createSwapChain(GLFWwindow* window);

	/*
	 * @brief Creates image views for the swap chain images.
	 */
	void createImageViews();

	/*
	 * @brief Creates an image view for a Vulkan image.
	 *
	 * @param image       The Vulkan image.
	 * @param format      The format of the image.
	 * @param aspectFlags The image aspect flags.
	 * @return The created image view.
	 */
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

	/*
	 * @brief Creates a render pass.
	 */
	void createRenderPass();

	/*
	 * @brief Creates a descriptor set layout.
	 */
	void createDescriptorSetLayout();

	/*
	 * @brief Creates a graphics pipeline.
	 */
	void createGraphicsPipeline();

	/*
	 * @brief Creates a compute pipeline.
	 */
	void createComputePipeline();

	/*
	 * @brief Creates framebuffers for the swap chain images.
	 */
	void createFramebuffers();

	/*
	 * @brief Creates depth resources.
	 */
	void createDepthResources();

	/*
	 * @brief Creates a command pool.
	 */
	void createCommandPool();

	/*
	 * @brief Creates texture images.
	 */
	void createTextureImages();

	/*
	 * @brief Creates image views for the texture images.
	 */
	void createTextureImageViews();

	/*
	 * @brief Creates a texture sampler.
	 */
	void createTextureSampler();

	/*
	 * @brief Creates the description of the geometry for the bottom-level acceleration structure.
	 *
	 * @param index The index of the acceleration structure.
	 */
	void createBottomLevelAccelerationStructureGeometry(int index);

	/*
	 * @brief Creates a Vulkan image.
	 *
	 * @param width      The width of the image.
	 * @param height     The height of the image.
	 * @param format     The format of the image.
	 * @param tiling     The tiling mode of the image.
	 * @param usage      The image usage flags.
	 * @param properties The memory property flags for the image.
	 * @param image      The created Vulkan image.
	 * @param imageMemory The device memory for the image.
	 */
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

	/*
	 * @brief Creates the acceleration structures.
	 */
	void createAccelerationStructures();

	/*
	 * @brief Creates the bottom-level acceleration structure.
	 *
	 * @param index The index of the acceleration structure.
	 */
	void createBottomLevelAccelerationStructure(int index);

	/*
	 * @brief Creates the description of the geometry for the top-level acceleration structure.
	 */
	void createTopLevelAccelerationStructureGeometry();

	/*
	 * @brief Creates the top-level acceleration structure.
	 *
	 * @param index The index of the acceleration structure.
	 */
	void createTopLevelAccelerationStructure(int index);

	/*
	 * @brief Updates the top-level acceleration structure.
	 */
	void updateTopLevelAccelerationStructure();

	/*
	 * @brief Retrieves the device address of a buffer.
	 *
	 * @param buffer The Vulkan buffer.
	 * @return The device address of the buffer.
	 */
	uint64_t getBufferDeviceAddress(VkBuffer buffer);

	/*
	 * @brief Transitions the layout of an image.
	 *
	 * @param image      The Vulkan image.
	 * @param format     The format of the image.
	 * @param oldLayout  The oldlayout of the image.
	 * @param newLayout  The new layout of the image.
	 */
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

	/*
	 * @brief Copies a buffer to an image.
	 *
	 * @param buffer The source Vulkan buffer.
	 * @param image  The destination Vulkan image.
	 * @param width  The width of the image.
	 * @param height The height of the image.
	 */
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	/*
	 * @brief Begins a single time command buffer.
	 *
	 * @param commandPool The command pool.
	 * @return The allocated command buffer.
	 */
	VkCommandBuffer beginSingleTimeCommands(VkCommandPool& commandPool);

	/*
	 * @brief Ends a single time command buffer.
	 *
	 * @param commandBuffer The command buffer to end.
	 * @param queue         The Vulkan queue.
	 * @param pool          The command pool.
	 */
	void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkQueue& queue, VkCommandPool& pool);

	// Buffer creation functions

	/*
	 * @brief Creates a vertex buffer for a mesh.
	 *
	 * @param mesh The mesh to create the vertex buffer for.
	 * @return The buffer manager for the vertex buffer.
	 */
	Buffermanager createVertexbuffer(Mesh mesh);

	/*
	 * @brief Creates an index buffer for a mesh.
	 *
	 * @param mesh The mesh to create the index buffer for.
	 * @return The buffer manager for the index buffer.
	 */
	Buffermanager createIndexBuffer(Mesh mesh);

	/*
	 * @brief Creates a scratch buffer with a specified size.
	 *
	 * @param size The size of the scratch buffer.
	 * @return The buffer manager for the scratch buffer.
	 */
	Buffermanager createScratchBuffer(VkDeviceSize size);

	/*
	 * @brief Creates a buffer for the acceleration structure.
	 *
	 * @param accelerationStructure The acceleration structure.
	 * @param buildSizeInfo         The build size information for the acceleration structure.
	 */
	void createAccelerationStructureBuffer(AccelerationStructure& accelerationStructure, VkAccelerationStructureBuildSizesInfoKHR buildSizeInfo);

	/*
	 * @brief Creates a buffer for the top-level acceleration structure with a vector of instances.
	 *
	 * @param instances The vector of acceleration structure instances.
	 */
	void createTopLevelAccelerationStructureBuffer(std::vector<VkAccelerationStructureInstanceKHR> instances);

	/*
	 * @brief Creates a storage buffer for the transform data.
	 */
	void createTransformBuffer();

	/*
	 * @brief Creates uniform buffers.
	 */
	void createUniformBuffers();

	/*
	 * @brief Creates storage buffers for the compute shader.
	 */
	void createComputeShaderBuffers();

	/*
	 * @brief Creates a descriptor pool.
	 */
	void createDescriptorPool();

	/*
	 * @brief Creates descriptor sets.
	 */
	void createDescriptorSets();

	/*
	 * @brief Creates a descriptor set layout for the compute pipeline.
	 */
	void createComputeDescriptorSetLayout();

	/*
	 * @brief Creates descriptor sets for the compute pipeline.
	 */
	void createComputeDescriptorSets();

	/*
	 * @brief Creates a Vulkan buffer.
	 *
	 * @param bufferManager The buffer manager holding the Vkbuffer, its deviceadress etc..
	 */
	void createBuffer(Buffermanager& bufferManager);

	/*
	 * @brief Copies data from one buffer to another.
	 *
	 * @param srcBuffer The source Vulkan buffer.
	 * @param dstBuffer The destination Vulkan buffer.
	 * @param size      The size of the data to copy.
	 */
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	/*
	 * @brief Creates command buffers.
	 */
	void createCommandBuffers();

	/*
	 * @brief Creates compute command buffers.
	 */
	void createComputeCommandBuffers();
	/*
	 * @brief Records a command buffer for rendering.
	 *
	 * @param commandBuffer The command buffer to record.
	 * @param imageIndex    The index ofthe swap chain image.
	 * @param commandBuffer The command buffer to record.
	 * @param imageIndex    The index of the swap chain image.
	 */
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	/*
	 * @brief Records a command buffer for compute operations.
	 *
	 * @param commandBuffer The command buffer to record.
	 */
	void recordComputeCommandBuffer(VkCommandBuffer commandBuffer);

	/*
	 * @brief Creates synchronization objects.
	 */
	void createSyncObjects();

	/*
	 * @brief Updates the uniform buffer for a specified image.
	 *
	 * @param currentImage The index of the current swap chain image.
	 */
	void updateUniformBuffer(uint32_t currentImage);

	/*
	 * @brief Checks if the required validation layers are supported.
	 *
	 * @return True if the validation layers are supported, false otherwise.
	 */
	bool checkValidationLayerSupport();

	/*
	 * @brief Checks if the required device extensions are supported.
	 *
	 * @param device The physical device to check for extension support.
	 * @return True if the device extensions are supported, false otherwise.
	 */
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	/*
	 * @brief Sets up the debug messenger for Vulkan.
	 */
	void setupDebugMessenger();

	/*
	 * @brief Creates a Vulkan surface for the GLFW window.
	 *
	 * @param window The GLFW window.
	 */
	void createSurface(GLFWwindow* window);

	/*
	 * @brief Picks a suitable physical device (GPU) for Vulkan.
	 */
	void pickPhysicalDevice();

	/*
	 * @brief Creates the logical device for Vulkan.
	 */
	void createLogicalDevice();

	/*
	 * @brief Checks if a physical device (GPU) is suitable for Vulkan.
	 *
	 * @param device The physical device to check.
	 * @return True if the device is suitable, false otherwise.
	 */
	bool isDeviceSuitable(VkPhysicalDevice device);

	/*
	 * @brief Checks if a specified format has a stencil component.
	 *
	 * @param format The format to check.
	 * @return True if the format has a stencil component, false otherwise.
	 */
	bool hasStencilComponent(VkFormat format);

	/*
	 * @brief Updates the transform buffer.
	 */
	void updateTransformBuffer();

	/*
	 * @brief Finds a suitable memory type for a specified filter and properties.
	 *
	 * @param typeFilter   The memory type filter.
	 * @param properties   The memory properties.
	 * @return The index of the suitable memory type.
	 */
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	/*
	 * @brief Retrieves the required Vulkan extensions.
	 *
	 * @return A vector of the required Vulkan extensions.
	 */
	std::vector<const char*> getRequiredExtensions();

	/*
	 * @brief Reads a file and returns its contents as a vector of characters.
	 *
	 * @param filename The name of the file to read.
	 * @return The contents of the file as a vector of characters.
	 */
	std::vector<char> readFile(const std::string& filename);

	/*
	 * @brief Finds queue families that support required capabilities for a physical device.
	 *
	 * @param device The physical device to query.
	 * @return The queue family indices that support the required capabilities.
	 */
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	/*
	 * @brief Queries the swap chain support details for a physical device.
	 *
	 * @param device The physical device to query.
	 * @return The swap chain support details.
	 */
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	/*
	 * @brief Chooses the preferred surface format for the swap chain.
	 *
	 * @param availableFormats The available surface formats.
	 * @return The chosen surface format.
	 */
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	/*
	 * @brief Chooses the preferred present mode for the swap chain.
	 *
	 * @param availablePresentModes The availablepresent modes.
	 * @return The chosen present mode.
	 */
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

	/*
	 * @brief Chooses the extent for the swap chain.
	 *
	 * @param capabilities The capabilities of the swap chain.
	 * @param window       The GLFW window.
	 * @return The chosen extent for the swap chain.
	 */
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);

	/*
	 * @brief Creates a Vulkan shader module from shader code.
	 *
	 * @param code The code of the shader.
	 * @return The created shader module.
	 */
	VkShaderModule createShaderModule(const std::vector<char>& code);

	/*
	 * @brief Finds a supported format from a list of candidates with specified tiling and features.
	 *
	 * @param candidates The list of candidate formats.
	 * @param tiling     The tiling mode of the format.
	 * @param features   The required format features.
	 * @return The supported format.
	 */
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	/*
	 * @brief Finds a supported depth format.
	 *
	 * @return The supported depth format.
	 */
	VkFormat findDepthFormat();

	/*
	 * @brief Retrieves the device address of an acceleration structure.
	 *
	 * @param index The index of the acceleration structure.
	 * @return The device address of the acceleration structure.
	 */
	VkDeviceAddress getAccelerationStructureDeviceAddressEXT(int index);

	/*
	 * @brief Builds the acceleration structures (using a Vulkan extension function).
	 *
	 * @param commandBuffer The command buffer for building the acceleration structures.
	 * @param infoCount     The number of build geometries.
	 * @param pInfos        The build geometries information.
	 * @param ppBuildRangeInfos The build range information.
	 */
	void cmdBuildAccelerationStructuresEXT(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);

	/*
	 * @brief Creates an acceleration structure (using a Vulkan extension function).
	 *
	 * @param device          The logical device.
	 * @param pCreateInfo    The creation information for the acceleration structure.
	 * @param pAllocator     The allocation callbacks.
	 * @param pAccelerationStructure  The created acceleration structure.
	 * @return The result of the acceleration structure creation.
	 */
	VkResult createAccelerationStructureEXT(VkDevice device, const VkAccelerationStructureCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureKHR* pAccelerationStructure);

	/*
	 * @brief Retrieves the build sizes for acceleration structures (using a Vulkan extension function).
	 *
	 * @param device       The logical device.
	 * @param buildType    The build type.
	 * @param pBuildInfo   The build geometry information.
	 * @param pMaxPrimitiveCounts   The maximum number of primitives.
	 * @param pSizeInfo    The build sizes information.
	 */
	void getAccelerationStructureBuildSizesEXT(VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo);

	/*
	 * @brief Destroys an acceleration structure (using a Vulkan extension function).
	 *
	 * @param accelerationStructure The acceleration structure to destroy.
	 * @param pAllocator            The allocation callbacks.
	 */
	void destroyAccelerationStructureEXT(VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator);
	/*
	 * @brief Creates a debug utils messenger (using a Vulkan extension function).
	 *
	 * @param instance     The Vulkan instance.
	 * @param pCreateInfo  The creation information for the debug messenger.
	 * @param pAllocator   The allocation callbacks.
	 * @param pDebugMessenger  The created debug messenger.
	 * @returnThe result of the debug messenger creation.
	 */
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

	/*
	 * @brief Destroys a debug utils messenger (using a Vulkan extension function).
	 *
	 * @param instance         The Vulkan instance.
	 * @param debugMessenger   The debug messenger to destroy.
	 * @param pAllocator       The allocation callbacks.
	 */
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	/*
	 * @brief fiils in the debug messenger create info.
	 *
	 * @param createInfo The create info for the debug messenger.
	 */
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	/*
	 * @brief Initializes ImGui for Vulkan integration.
	 *
	 * @param window The GLFW window.
	 */
	void initImgui(GLFWwindow* window);

	/*
	 * @brief Updates ImGui for rendering.
	 *
	 * @param window        The GLFW window.
	 * @param commandBuffer The command buffer for rendering ImGui.
	 */
	void updateImGui(GLFWwindow* window, VkCommandBuffer commandBuffer);

	/*
	 * @brief Builds ImGui.
	 */
	void buildImgui();


	int imGuiDescriptorSetCount = 1;
public:

	renderer(Camera& mainCamera, int objectCount, std::vector<RenderObject>& renderObjects, std::vector<std::unique_ptr<GameObject>>& gameObjects) : camera(mainCamera), objectCount(objectCount), renderObjects(renderObjects), gameObjects(gameObjects)
	{
		
	}

	~renderer()
	{
		cleanupVulkan();
		std::cout << "cleanupVulkan" << std::endl;
	}

	bool framebufferResized = false;


	/*
	* @brief Initializes Vulkan with a specified window object.
	*
	* @param windowObject The window object to use for Vulkan initialization.
	*/
	void initVulkan(std::unique_ptr<window>& windowObject);

	/*
	 * @brief Draws a frame using Vulkan.
	 *
	 * @param window The GLFW window.
	 */
	void drawFrame(GLFWwindow* window);

	/*
	 * @brief Creates a render object.
	 *
	 * @param renderObject The render object to create.
	 */
	void createObject(RenderObject renderObject);

	/*
	 * @brief Initializes a raycast with a specified origin and direction.
	 *
	 * @param origin    The origin of the ray.
	 * @param direction The direction of the ray.
	 * @return The result of the raycast.
	 */
	RayResult initRaycast(glm::vec3 origin, glm::vec3 direction);

	/*
	 * @brief Adds an instance to the renderer with a specified transform matrix.
	 *
	 * @param transform The transform matrix of the instance.
	 */
	void addInstance(glm::mat4 transform);

	/*
	 * @brief Deletes an instance from the renderer.
	 */
	void deleteInstance();

	/*
	 * @brief Retrieves the Vulkan device.
	 *
	 * @return The Vulkan device.
	 */
	VkDevice getDevice();
};