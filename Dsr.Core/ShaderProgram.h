#pragma once

#include <memory>
#include <stdexcept>

#include "InvalidOperationException.h"
#include "glad/glad.h"
#include "Shader.h"

namespace dsr
{
	struct ShaderLinkStatus
	{
		bool Success;
		std::string InfoLog;
	};

	class ShaderProgram
	{
	public:
		static std::shared_ptr<ShaderProgram> GenerateGL();

		void Attach(const std::shared_ptr<Shader>& shader) const;
		void Link() const;
		ShaderLinkStatus GetLinkStatus() const;

		void Use() const;
		void Dispose();

		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram& other) = delete;
		ShaderProgram& operator=(const ShaderProgram& other) = delete;

		~ShaderProgram();
	private:
		ShaderProgram(const unsigned int& programId)
			: m_programId(programId) {};

		unsigned int m_programId;
		bool m_disposed = false;
	};
}
