#pragma once
#include "SemperEngine/Core/Defines.h"
#include <glm/glm.hpp>

namespace SemperEngine
{
    namespace RenderCommands
    {
        enum class SamplerWrapping
        {
            Repeat = 0,
            MirroredRepeat,
            Clamp
        };
        enum class SamplerFiltering
        {
            Nearest = 0,
            Linear,
            NearestMipmapNearest,
            NearestMipmapLinear,
            LinearMipmapNearest,
            LinearMipmapLinear
        };

        enum class Primitve
        {
            Lines = 0,
            Triangles, 
            Points
        };

        enum class BlendFactor
        {
            Zero,
            One,
            SrcColor,
            OneMinusSrcColor,
            SrcAlpha,
            OneMinusSrcAlpha,
            DstColor,
            OneMinusDstColor,
            DstAlpha,
            OneMinusDstAlpha,
            SrcAlphaSaturated
        };

        enum class ClearMask
        {
            ColorBuffer,
            DepthBuffer,
            StencilBuffer
        };

        struct InitData
        {
            bool depthTestEnabled;
            bool blendingEnabled;
            BlendFactor sFactor, dFactor;
        };
        struct ViewportData
        {
            float x, y;
            float width, height;
        };
        struct ClearData
        {
            glm::vec4 clearColor;
            ClearMask mask;
        };
    }
    typedef uint32_t RendererID;
}