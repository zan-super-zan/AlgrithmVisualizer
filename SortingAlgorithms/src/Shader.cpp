#include "Shader.h"

#include "../glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include "GLCheck.h"

#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	if (!LoadFromFile(vertexPath, fragmentPath))
		std::cout << "ERROR::SHADER::Failed to load shader." << std::endl;
}

Shader::Shader(Shader&& other) noexcept
	: m_ShaderId(other.m_ShaderId), m_UniformLocationCache(std::move(other.m_UniformLocationCache))
{
	other.m_ShaderId = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	if (this != &other)
	{
		GLCheck(glDeleteProgram(m_ShaderId));
		m_ShaderId = other.m_ShaderId;
		m_UniformLocationCache = std::move(other.m_UniformLocationCache);

		other.m_ShaderId = 0;
	}
	return *this;
}

Shader::~Shader()
{
	if (m_ShaderId)
		GLCheck(glDeleteProgram(m_ShaderId));
}

bool Shader::LoadFromFile(const std::string& vertexPath, const std::string fragmentPath)
{
	std::ifstream vFile(vertexPath), fFile(fragmentPath);
	if (!vFile.is_open() || !fFile.is_open())
	{
		std::cerr << "ERROR::FILE_STREAM::Could not open shader files." << std::endl;
		return false;
	}

	std::stringstream vStream, fStream;
	vStream << vFile.rdbuf();
	fStream << fFile.rdbuf();

	return LoadFromSource(vStream.str(), fStream.str());
}

bool Shader::LoadFromSource(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	uint32_t vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
	if (!vertexShader)
		return false;

	uint32_t fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);
	if (!fragmentShader)
	{
		GLCheck(glDeleteShader(vertexShader));
		return false;
	}

	bool result = linkProgram(vertexShader, fragmentShader);

	GLCheck(glDeleteShader(vertexShader));
	GLCheck(glDeleteShader(fragmentShader));

	return result;
}

void Shader::Use() const
{
	GLCheck(glUseProgram(m_ShaderId));
}

void Shader::Unbind()
{
	GLCheck(glUseProgram(0));
}

void Shader::SetInteger(const std::string& name, int32_t value)
{
	Use();
	GLCheck(glUniform1i(getUniformLocation(name), value));
}

void Shader::SetVec2(const std::string& name, glm::vec2 value)
{
	Use();
	GLCheck(glUniform2f(getUniformLocation(name), value.x, value.y));
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value)
{
	Use();
	GLCheck(glUniform3f(getUniformLocation(name), value.x, value.y, value.z));
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value)
{
	Use();
	GLCheck(glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat)
{
	Use();
	GLCheck(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
}

uint32_t Shader::compileShader(uint32_t type, const std::string& source)
{
	uint32_t shader = glCreateShader(type);

	const char* src = source.c_str();
	GLCheck(glShaderSource(shader, 1, &src, nullptr));
	GLCheck(glCompileShader(shader));

	int32_t success{ 0 };
	GLCheck(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		int32_t length{ 0 };
		std::string errorLog(length, ' ');
		GLCheck(glGetShaderInfoLog(shader, length, &length, &errorLog[0]));
	}
	return shader;
}

bool Shader::linkProgram(uint32_t vertexShader, uint32_t fragmentShader)
{
	if (m_ShaderId)
	{
		GLCheck(glDeleteProgram(m_ShaderId));
		m_ShaderId = 0;
	}
	m_ShaderId = glCreateProgram();
	GLCheck(glAttachShader(m_ShaderId, vertexShader));
	GLCheck(glAttachShader(m_ShaderId, fragmentShader));
	GLCheck(glLinkProgram(m_ShaderId));

	int32_t success{ 0 };
	GLCheck(glGetProgramiv(m_ShaderId, GL_LINK_STATUS, &success));
	if (!success)
	{
		int32_t length{ 0 };
		GLCheck(glGetProgramiv(m_ShaderId, GL_INFO_LOG_LENGTH, &length));
		std::string errorLog(length, ' ');
		GLCheck(glGetProgramInfoLog(m_ShaderId, length, &length, &errorLog[0]));
		std::cerr << "ERROR::SHADER::LINK::Failed to link program." << std::endl;
		GLCheck(glDeleteProgram(m_ShaderId));
		m_ShaderId = 0;
		return false;
	}
	return true;
}

int32_t Shader::getUniformLocation(const std::string& name) 
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int32_t location = glGetUniformLocation(m_ShaderId, name.c_str());
	if (location == -1)
		std::cerr << "ERROR::UNIFORM::LOCATION::Uniform location doesn't exist.\n";
	m_UniformLocationCache[name] = location;
	return location;
}
