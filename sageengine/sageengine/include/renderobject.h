struct RenderObject
{
	struct RenderProps
	{
		glm::mat4 instances[30];
		alignas(16) glm::vec3 color;
	};

	Mesh mesh;
	RenderProps renderprops;
	
};
