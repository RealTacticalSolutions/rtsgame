class Vertex
{
public:
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();

	bool Vertex::operator==(const Vertex& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}
private:

};