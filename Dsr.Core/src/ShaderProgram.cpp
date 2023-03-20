
#include "dsrpch.h"
#include "ShaderProgram.h"

namespace dsr
{
	std::shared_ptr<ShaderProgram> ShaderProgram::GenerateGL()
	{
		unsigned int programId;
		programId = glCreateProgram();

		if (!programId)
			throw std::runtime_error("glCreateProgram failed.");

		ShaderProgram* ptr = new ShaderProgram(programId);
		return std::shared_ptr<ShaderProgram>(ptr);
	}

	void ShaderProgram::Attach(const std::shared_ptr<Shader>& shader) const
	{
		if (!shader->IsCompiled())
			throw new InvalidOperationException("Cannot attach uncompiled Shader.");

		glAttachShader(m_programId, shader->GetShaderId());
	}

	void ShaderProgram::Link() const
	{
		glLinkProgram(m_programId);
	}

	ShaderLinkStatus ShaderProgram::GetLinkStatus() const
	{
		constexpr int bufferSize = 512;

		int success;
		char infoLog[bufferSize] = "";
		glGetShaderiv(m_programId, GL_LINK_STATUS, &success);
		glGetShaderInfoLog(m_programId, bufferSize, NULL, infoLog);

		ShaderLinkStatus linkStatus;
		linkStatus.Success = success;
		linkStatus.InfoLog = infoLog;

		return linkStatus;
	}

	void ShaderProgram::Use() const
	{
		glUseProgram(m_programId);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_programId);
		m_programId = 0;
	}
}
