#pragma once
#include <stdint.h>
#include <memory>
#include <glm/glm.hpp>


namespace SemperEngine
{
	// Primitives 
	using I8  = ::int8_t;
	using I16 = ::int16_t;
	using I32 = ::int32_t;
	using I64 = ::int64_t;

	using U8  = ::uint8_t;
	using U16 = ::uint16_t;
	using U32 = ::uint32_t;
	using U64 = ::uint64_t;

	using c8  = char;
	using c16 = char16_t;
	using c32 = char32_t;

	// Vector types
	using Vec2 = glm::vec2;
	using Vec3 = glm::vec3;
	using Vec4 = glm::vec4;

	using Vec2i = glm::ivec2;
	using Vec3i = glm::ivec3;
	using Vec4i = glm::ivec4;	
	
	using Vec2f = glm::fvec2;
	using Vec3f = glm::fvec3;
	using Vec4f = glm::fvec4;

	// Matrix types
	using Mat2 = glm::mat2;
	using Mat3 = glm::mat3;
	using Mat4 = glm::mat4;

	using Mat2x3 = glm::mat2x3;
	using Mat2x4 = glm::mat2x4;

	using Mat3x2 = glm::mat3x2;
	using Mat3x4 = glm::mat3x4;

	using Mat4x2 = glm::mat4x2;
	using Mat4x3 = glm::mat4x3;


	// Pointers and References
	template<typename Type>
	using ConstRef = const Type &;

	template<typename Type>
	using UniquePtr = std::unique_ptr<Type>;
	template<typename Type, typename ... Args>
	constexpr UniquePtr<Type> MakeUnique(Args && ... args)
	{
		return std::make_unique<Type>(std::forward<Args>(args)...);
	}
	
	template<typename Type>
	using SharedPtr = std::shared_ptr<Type>;
	template<typename Type, typename ... Args>
	constexpr SharedPtr<Type> MakeShared(Args && ... args)
	{
		return std::make_shared<Type>(std::forward<Args>(args)...);
	}
}