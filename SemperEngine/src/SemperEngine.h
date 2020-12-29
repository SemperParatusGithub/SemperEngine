#pragma once
#include "Precompiled.h"

/* ----------------------------- Third Party ----------------------------- */
	#include "../imgui/imgui.h"

	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
/* ----------------------------------------------------------------------- */

/* --------------------------------- Core -------------------------------- */
	#include "SemperEngine/Core/Assert.h"
	#include "SemperEngine/Core/EngineApplication.h"
	#include "SemperEngine/Core/Types.h"
	#include "SemperEngine/Core/Input.h"
/* ----------------------------------------------------------------------- */

/* --------------------------------- Log --------------------------------- */
	#include "SemperEngine/Log/Log.h"
/* ----------------------------------------------------------------------- */

/* ------------------------------ Graphics ------------------------------- */
	#include "SemperEngine/Graphics/Sprite.h"
	#include "SemperEngine/Graphics/Transform.h"
	#include "SemperEngine/Graphics/Renderable2D.h"
	#include "SemperEngine/Graphics/ShaderManager.h"

	#include "SemperEngine/Graphics/Renderers/Renderer.h"
	#include "SemperEngine/Graphics/Renderers/Batcher2D.h"

/* ------------------------------ Backend -------------------------------- */
	#include "SemperEngine/Graphics/Backend/API/VertexArray.h"
	#include "SemperEngine/Graphics/Backend/API/VertexBuffer.h"
	#include "SemperEngine/Graphics/Backend/API/IndexBuffer.h"
	#include "SemperEngine/Graphics/Backend/API/Texture.h"
	#include "SemperEngine/Graphics/Backend/API/Shader.h"

/* ------------------------------ Camera --------------------------------- */
	#include "SemperEngine/Graphics/Camera/Camera.h"
	#include "SemperEngine/Graphics/Camera/EditorCamera.h"
	#include "SemperEngine/Graphics/Camera/OrthographicCamera.h"
	#include "SemperEngine/Graphics/Camera/OrthographicCameraController.h"
/* ----------------------------------------------------------------------- */