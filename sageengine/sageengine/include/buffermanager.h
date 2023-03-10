#pragma once

struct Buffermanager {

	VkDeviceSize bufferSize;
	VkBufferUsageFlags bufferUsageFlags;
	VkMemoryPropertyFlags memoryPropertyFlags;
	void* handle;

	VkBuffer buffer;
	VkDeviceMemory bufferMemory;
};