#pragma once

#include <memory>
#include <string>

namespace dsr
{
	enum ShaderType
	{
		Vertex,
		Fragment
	};

	class Shader
	{
	public:

		Shader() = delete;
	private:
		Shader(const std::string& code, const ShaderType& type)
			: m_code(code), m_type(type) {};

		std::string m_code;
		ShaderType m_type;
	};
}
