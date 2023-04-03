class RenderObject
{
private:

public:
	struct RenderProps
	{
		glm::mat4 instances[30];
		glm::vec4 color[30];
	};

	Mesh mesh;
	RenderProps renderprops;
	char* texture;
	int instanceCount = 0;

	void addInstance(glm::mat4 transform, glm::vec4 color) {
		renderprops.instances[instanceCount] = transform;
		renderprops.color[instanceCount] = color;
		instanceCount += 1;
	}
};
