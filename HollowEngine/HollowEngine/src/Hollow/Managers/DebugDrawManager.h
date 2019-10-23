#pragma once

namespace Hollow
{
	class HOLLOW_API DebugDrawManager
	{
		SINGLETON(DebugDrawManager)
	public:
		void Init();
		void CleanUp();

		void DebugDirectionLine(glm::vec3 startPos, glm::vec3 endPos, glm::vec3 color = COLOR_GREEN);
		void DebugLine(glm::vec3 startPos, glm::vec3 endPos, glm::vec3 color = COLOR_GREEN);
		void DebugCircle(glm::vec3 position, glm::vec2 scale, glm::vec3 color = COLOR_GREEN);
		void DebugQuad(glm::vec3 position = glm::vec3(1.0f), glm::vec2 scale = glm::vec2(1.0f), glm::vec3 color = COLOR_GREEN);
		void DebugAxes(glm::vec3 position, glm::vec3 scale);
		void DebugSphere(glm::vec3 position = glm::vec3(1.0f), glm::vec3 scale = glm::vec3(1.0f), glm::vec3 color = COLOR_GREEN);
		void DebugCube(glm::vec3 position = glm::vec3(1.0f), glm::vec3 scale = glm::vec3(1.0f), glm::vec3 color = COLOR_GREEN);
	};
}