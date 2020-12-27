#pragma once

// Precompiled Headers
#include "pch.h"

// ImGui
#include "../imgui/imgui.h"

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Core 
#include "SemperEngine/Core/EngineApplication.h"
#include "SemperEngine/Core/Types.h"
#include "SemperEngine/Core/Input.h"
#include "SemperEngine/Core/Assert.h"

// Log
#include "SemperEngine/Log/Log.h"

// Renderer 
#include "SemperEngine/Renderer/Renderer.h"
#include "SemperEngine/Renderer/Batcher2D.h"

#include "SemperEngine/Renderer/VertexArray.h"
#include "SemperEngine/Renderer/VertexBuffer.h"
#include "SemperEngine/Renderer/IndexBuffer.h"
#include "SemperEngine/Renderer/Texture.h"
#include "SemperEngine/Renderer/Shader.h"

// Camera
#include "SemperEngine/Renderer/Camera/Camera.h"
// #include "SemperEngine/Renderer/Camera/EditorCamera.h"
#include "SemperEngine/Renderer/Camera/OrthographicCamera.h"
#include "SemperEngine/Renderer/Camera/OrthographicCameraController.h"

// Utils
#include "SemperEngine/Utils/Transform.h"