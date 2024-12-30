#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include <unordered_map>
#include <iostream>
#include <string>

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;
	~Shader();

	bool LoadFromFile(const std::string& vertexPath, const std::string fragmentPath);
	bool LoadFromSource(const std::string& vertexSrc, const std::string& fragmentSrc);

	void Use() const;
	static void Unbind();

	void SetInteger(const std::string& name, int32_t value);
	void SetVec2(const std::string& name, glm::vec2 value);
	void SetVec3(const std::string& name, const glm::vec3& value);
	void SetVec4(const std::string& name, const glm::vec4& value);
	void SetMat4(const std::string& name, const glm::mat4& mat);

	uint32_t GetId()const { return m_ShaderId; }

private:
	uint32_t m_ShaderId{ 0 };
	std::unordered_map<std::string, int32_t> m_UniformLocationCache;

	uint32_t compileShader(uint32_t type, const std::string& source);
	bool linkProgram(uint32_t vertexShader, uint32_t fragmentShader);
	int32_t getUniformLocation(const std::string& name);
};