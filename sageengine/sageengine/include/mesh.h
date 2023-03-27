#pragma once

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	void* buffer;
};