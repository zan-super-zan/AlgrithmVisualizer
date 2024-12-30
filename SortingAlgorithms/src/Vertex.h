#pragma once
#include "../glm/glm.hpp"


struct Vertex
{
	Vertex(){ }
	Vertex(const glm::vec3& position) : Position(position){ }
	Vertex(const glm::vec3& position, const glm::vec3& color) : Position(position), Color(color) {}
	Vertex(const glm::vec3& position, const glm::vec3& color, glm::vec2 texCoords) : Position(position), Color(color), TexCoords(texCoords) {}

public:
	glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 Color{ 0.0f, 0.0f, 0.0f };
	glm::vec2 TexCoords{ 0.0f, 0.0f };
};
