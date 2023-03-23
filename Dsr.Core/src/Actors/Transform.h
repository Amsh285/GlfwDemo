#pragma once



namespace dsr
{
	namespace actors
	{
		class Transform
		{
		public:
			inline glm::vec3 GetPosition() const { return m_Position; }
			inline glm::vec3 GetScale() const { return m_Scale; }
			inline glm::vec3 GetRotation() const { return m_Rotation; }

			void SetPosition(const glm::vec3& position) { m_Position = position; }
			void SetScale(const glm::vec3& scale) { m_Scale = scale; }
			void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }

			Transform();
		private:
			glm::vec3 m_Position;
			glm::vec3 m_Scale;
			glm::vec3 m_Rotation;
		};
	}
}
