struct RenderObject
{
	struct RenderProps
	{
		glm::mat4 instances[30];
		alignas(16) glm::vec3 color[30];
	};

	Mesh mesh;
	RenderProps renderprops;
	char* texture;
	int instanceCount = 0;
};
