
#include "dsrpch.h"
#include "ShaderProgram.h"

namespace dsr
{
	namespace shading
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

		bool ShaderProgram::SetUniform(const std::string& name, const glm::mat4& value) const
		{
			int location = glGetUniformLocation(m_programId, name.c_str());

			if (location == -1)
				return false;

			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
			return true;
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
}
