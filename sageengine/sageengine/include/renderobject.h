struct RenderObject
{
	struct RenderProps
	{
		glm::mat4 instances[30];
		glm::vec4 color[30];
	};

	Mesh mesh;
	RenderProps renderprops;
	char* texture;
	int instanceCount = 0;
};
