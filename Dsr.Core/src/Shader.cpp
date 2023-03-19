#include "Shader.h"

namespace dsr
{
	std::shared_ptr<Shader> Shader::Load(const std::string& path, const ShaderType& type)
	{
		std::string fileContent;
		std::ifstream fileStream(path);

		std::ostringstream stringStream;
		stringStream << fileStream.rdbuf();
		fileContent = stringStream.str();

		return GenerateGL(fileContent, type);
	}

	std::shared_ptr<Shader> Shader::GenerateGL(const std::string& src, const ShaderType& type)
	{
		unsigned int shaderId = glCreateShader(ConvertShaderType(type));

		if (!shaderId)
			throw std::runtime_error("glCreateShader failed.");

		Shader* ptr = new Shader(src, type, shaderId);
		return std::shared_ptr<Shader>(ptr);
	}

	void Shader::Compile()
	{
		const char* src = m_code.c_str();
		glShaderSource(m_shaderId, 1, &src, NULL);
		glCompileShader(m_shaderId);

		m_compiled = true;
	}

	ShaderCompileStatus Shader::GetCompileStatus() const
	{
		constexpr int bufferSize = 512;

		int success;
		char infoLog[bufferSize] = "";
		glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &success);
		glGetShaderInfoLog(m_shaderId, bufferSize, NULL, infoLog);

		ShaderCompileStatus compileStatus;
		compileStatus.Success = success;
		compileStatus.InfoLog = infoLog;

		return compileStatus;
	}

	Shader::~Shader()
	{
		glDeleteShader(m_shaderId);
		m_shaderId = 0;
	}

	unsigned int Shader::ConvertShaderType(const ShaderType& type)
	{
		switch (type)
		{
		case Vertex:
			return GL_VERTEX_SHADER;
		case Fragment:
			return GL_FRAGMENT_SHADER;
		default:
		{
			std::string errorMessage = "Shadertype: "
				+ std::to_string(type) + "is not supported.";

			throw dsr::NotSupportedException(errorMessage);
		}
		}
	}
}
