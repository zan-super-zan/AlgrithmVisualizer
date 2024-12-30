#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_Projection = glm::ortho(left, right, bottom, top, zNear, zFar);
	m_View = glm::mat4(1.0f);

	m_ViewProjection = m_Projection * m_View;
}

void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_Projection = glm::ortho(left, right, bottom, top, zNear, zFar);
	m_ViewProjection = m_Projection * m_View;
}

void OrthographicCamera::SetPosition(const glm::vec3 position)
{
	m_Position = position;
	recalculateViewMatrix();
}

void OrthographicCamera::SetRotation(float rotation)
{
	m_Rotation = rotation;
	recalculateViewMatrix();
}

void OrthographicCamera::recalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

	m_View = glm::inverse(transform);

	m_ViewProjection = m_Projection * m_View;
}
