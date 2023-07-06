class Vertex
{
public:
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;
	glm::vec3 normal;

	/*
	 * @brief Retrieves the binding description for the vertex input.
	 *
	 * @return The binding description for the vertex input.
	 */
	static VkVertexInputBindingDescription getBindingDescription();

	/*
	 * @brief Retrieves the attribute descriptions for the vertex input.
	 *
	 * @return The attribute descriptions for the vertex input.
	 */
	static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions();

	/*
	 * @brief Overloads the equals operator on Vertex to check if the vertex is equal to another vertex.
	 *
	 * @param other The other vertex to compare.
	 * @return True if the vertices are equal, false otherwise.
	 */
	bool Vertex::operator==(const Vertex& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}
private:

};