#include "Precompiled.h"
#include <GLFW/glfw3.h>

#include "SemperEngine/Core/Input.h"
#include "SemperEngine/Core/EngineApplication.h"


namespace SemperEngine
{
	bool Input::IsKeyPressed(KeyCode key)
	{
		GLFWwindow *window = static_cast<GLFWwindow *>(EngineApplication::Instance().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, static_cast<U32>(key));
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		GLFWwindow *window = static_cast<GLFWwindow *>(EngineApplication::Instance().GetWindow().GetNativeWindow());

		int state = glfwGetMouseButton(window, static_cast<U32>(button));
		return state == GLFW_PRESS;
	}

	Vec2 Input::GetMousePosition()
	{
		GLFWwindow *window = static_cast<GLFWwindow *>(EngineApplication::Instance().GetWindow().GetNativeWindow());

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return glm::vec2 { static_cast<float>(xPos), static_cast<float>(yPos) };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}