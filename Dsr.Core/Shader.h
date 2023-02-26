#pragma once

#include <fstream>
#include <memory>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include "NotSupportedException.h"
#include "SpdLoggerFactory.h"

namespace dsr
{
	enum ShaderType
	{
		Vertex,
		Fragment
	};

	struct ShaderCompileStatus
	{
		bool Success;
		std::string InfoLog;
	};

	class Shader
	{
	public:
		static std::shared_ptr<Shader> Load(
			const std::string& path,
			const ShaderType& type
		);
		
		const unsigned int& GetShaderId() const { return m_shaderId; };

		void Compile() const;
		ShaderCompileStatus GetCompileStatus();

		Shader() = delete;
	private:
		Shader(
			const std::string& code,
			const ShaderType& type, 
			const unsigned int& shaderId) :
			m_code(code),
			m_type(type),
			m_shaderId(shaderId) {};

		static unsigned int ConvertShaderType(const ShaderType& type);

		const std::string m_code;
		const ShaderType m_type;
		const unsigned int m_shaderId;
	};
}
