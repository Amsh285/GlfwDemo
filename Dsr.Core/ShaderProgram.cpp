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
		if (m_disposed)
			throw new InvalidOperationException("Cannot attach Shader to disposed Shaderprogram.");

		if (!shader->IsCompiled())
			throw new InvalidOperationException("Cannot attach uncompiled Shader.");

		glAttachShader(m_programId, shader->GetShaderId());
	}

	void ShaderProgram::Link() const
	{
		if (m_disposed)
			throw new InvalidOperationException("Cannot Link disposed Shaderprogram.");

		glLinkProgram(m_programId);
	}

	ShaderLinkStatus ShaderProgram::GetLinkStatus() const
	{
		if (m_disposed)
			throw InvalidOperationException("GetLinkStatus Error: ShaderProgram is disposed.");;

		constexpr int bufferSize = 512;

		int success;
		char infoLog[bufferSize];
		glGetShaderiv(m_programId, GL_LINK_STATUS, &success);
		glGetShaderInfoLog(m_programId, bufferSize, NULL, infoLog);

		ShaderLinkStatus linkStatus;
		linkStatus.Success = success;
		linkStatus.InfoLog = infoLog;

		return linkStatus;
	}

	void ShaderProgram::Use() const
	{
		if (m_disposed)
			throw new InvalidOperationException("Cannot Use disposed Shaderprogram.");

		glUseProgram(m_programId);
	}

	void ShaderProgram::Dispose()
	{
		if (!m_disposed)
		{
			glDeleteProgram(m_programId);
			m_programId = 0;
			m_disposed = true;
		}
	}

	ShaderProgram::~ShaderProgram()
	{
		Dispose();
	}
}
