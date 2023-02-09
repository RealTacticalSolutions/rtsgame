#pragma once

class renderer
{
private:
	VkInstance instance;


	void createInstance();
public:

	renderer()
	{
	}

	~renderer()
	{
		cleanupVulkan();
		std::cout << "cleanupVulkan" << std::endl;
	}
	void initVulkan();
	void cleanupVulkan();
};