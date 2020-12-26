#pragma once
#include <stdint.h>
#include <memory>


namespace SemperEngine
{
	using i8  = ::int8_t;
	using i16 = ::int16_t;
	using i32 = ::int32_t;
	using i64 = ::int64_t;

	using u8  = ::uint8_t;
	using u16 = ::uint16_t;
	using u32 = ::uint32_t;
	using u64 = ::uint64_t;

	using c8  = char;
	using c16 = char16_t;
	using c32 = char32_t;


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