#pragma once

#include <glad/glad.h>
#include "InvalidOperationException.h"
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

		static std::shared_ptr<Shader> GenerateGL(
			const std::string& src,
			const ShaderType& type
		);
		
		unsigned int GetShaderId() const { return m_shaderId; };
		const bool& IsCompiled() const { return m_compiled; };

		void Compile();
		ShaderCompileStatus GetCompileStatus() const;


		Shader() = delete;
		Shader(const Shader& other) = delete;
		Shader& operator=(const Shader& other) = delete;

		~Shader();
	private:
		Shader(
			const std::string& code,
			const ShaderType& type, 
			const unsigned int& shaderId) :
			m_code(code),
			m_type(type),
			m_shaderId(shaderId) {};

		static unsigned int ConvertShaderType(const ShaderType& type);

		std::string m_code;
		const ShaderType m_type;
		unsigned int m_shaderId;

		bool m_compiled = false;
	};
}
