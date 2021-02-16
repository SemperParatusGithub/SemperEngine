#pragma once
#include "Precompiled.h"

/* ----------------------------- Third Party ----------------------------- */
	#include "../imgui/imgui.h"

	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
/* ----------------------------------------------------------------------- */

/* --------------------------------- Core -------------------------------- */
	#include "SemperEngine/Core/Assert.h"
	#include "SemperEngine/Core/Defines.h"
	#include "SemperEngine/Core/EngineApplication.h"
	#include "SemperEngine/Core/Input.h"
	#include "SemperEngine/Core/LayerStack.h"
	#include "SemperEngine/Core/Platforms.h"
	#include "SemperEngine/Core/Types.h"
	#include "SemperEngine/Core/Window/Window.h"
/* ----------------------------------------------------------------------- */

/* ------------------------------- Events -------------------------------- */
	#include "SemperEngine/Events/ApplicationEvent.h"
	#include "SemperEngine/Events/Event.h"
	#include "SemperEngine/Events/EventDispatcher.h"
	#include "SemperEngine/Events/KeyEvent.h"
	#include "SemperEngine/Events/MouseEvent.h"
/* ----------------------------------------------------------------------- */


/* ------------------------------ Graphics ------------------------------- */
	#include "SemperEngine/Graphics/Sprite.h"
	#include "SemperEngine/Graphics/Transform.h"
	#include "SemperEngine/Graphics/ShaderManager.h"

/* ------------------------------ Backend -------------------------------- */
	#include "SemperEngine/Graphics/Backend/API/Backend.h"
	#include "SemperEngine/Graphics/Backend/API/Framebuffer.h"
	#include "SemperEngine/Graphics/Backend/API/IndexBuffer.h"
	#include "SemperEngine/Graphics/Backend/API/RenderContext.h"
	#include "SemperEngine/Graphics/Backend/API/Shader.h"
	#include "SemperEngine/Graphics/Backend/API/Texture.h"
	#include "SemperEngine/Graphics/Backend/API/VertexArray.h"
	#include "SemperEngine/Graphics/Backend/API/VertexBuffer.h"
	#include "SemperEngine/Graphics/Backend/API/VertexBufferElement.h"

/* ------------------------------ Camera --------------------------------- */
	#include "SemperEngine/Graphics/Camera/Camera.h"
	#include "SemperEngine/Graphics/Camera/EditorCamera.h"
	#include "SemperEngine/Graphics/Camera/OrthographicCamera.h"
	#include "SemperEngine/Graphics/Camera/OrthographicCameraController.h"
	#include "SemperEngine/Graphics/Camera/SceneCamera.h"

/* ------------------------------- ImGui --------------------------------- */
	#include "SemperEngine/Graphics/ImGui/ImGuiLayer.h"

/* ----------------------------- Renderers ------------------------------- */
	#include "SemperEngine/Graphics/Renderers/Renderer.h"
	#include "SemperEngine/Graphics/Renderers/Batcher2D.h"
/* ----------------------------------------------------------------------- */

/* --------------------------------- Log --------------------------------- */
#include "SemperEngine/Log/Log.h"
/* ----------------------------------------------------------------------- */

/* -------------------------------- Scene -------------------------------- */
	#include "SemperEngine/Scene/Components.h"
	#include "SemperEngine/Scene/Entity.h"
	#include "SemperEngine/Scene/Scene.h"
	#include "SemperEngine/Scene/UUID.h"
/* ----------------------------------------------------------------------- */

/* --------------------------------- Util -------------------------------- */
	#include "SemperEngine/Util/CereaLOverloads.h"
	#include "SemperEngine/Util/Filesystem.h"
	#include "SemperEngine/Util/Math.h"
/* ----------------------------------------------------------------------- */