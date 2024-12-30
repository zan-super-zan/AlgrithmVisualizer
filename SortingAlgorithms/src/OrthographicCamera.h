#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

class OrthographicCamera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);

	void SetProjectionMatrix(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);

	const glm::vec3& GetPosition()const { return m_Position; }
	void SetPosition(const glm::vec3 position);

	float GetRotation()const { return m_Rotation; }
	void SetRotation(float rotation);

	const glm::mat4& GetProjectionMatrix()const { return m_Projection; }
	const glm::mat4& GetViewMatrix()const { return m_View; }
	const glm::mat4& GetViewProjectionMatrix()const { return m_ViewProjection; }

private:
	void recalculateViewMatrix();
private:
	glm::mat4 m_Projection{ 1.0 };
	glm::mat4 m_View{ 1.0f };
	glm::mat4 m_ViewProjection{ 1.0f };

	glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
	float m_Rotation{ 0.0f };

};

