#pragma once

#include <common/types.h>

#define ENUM_CLASS_FLAGS(TEnum) \
	inline TEnum& operator|=(TEnum& a, TEnum b) { return a = (TEnum)(std::underlying_type_t<TEnum>(a) | std::underlying_type_t<TEnum>(b)); } \
	inline TEnum& operator&=(TEnum& a, TEnum b) { return a = (TEnum)(std::underlying_type_t<TEnum>(a) & std::underlying_type_t<TEnum>(b)); } \
	inline TEnum& operator^=(TEnum& a, TEnum b) { return a = (TEnum)(std::underlying_type_t<TEnum>(a) ^ std::underlying_type_t<TEnum>(b)); } \
	inline TEnum  operator| (TEnum  a, TEnum b) { return (TEnum)(std::underlying_type_t<TEnum>(a) | std::underlying_type_t<TEnum>(b)); } \
	inline TEnum  operator& (TEnum  a, TEnum b) { return (TEnum)(std::underlying_type_t<TEnum>(a) & std::underlying_type_t<TEnum>(b)); } \
	inline TEnum  operator^ (TEnum  a, TEnum b) { return (TEnum)(std::underlying_type_t<TEnum>(a) ^ std::underlying_type_t<TEnum>(b)); } \
	inline TEnum  operator! (TEnum  a) { return (TEnum)!std::underlying_type_t<TEnum>(a); } \
	inline TEnum  operator~ (TEnum  a) { return (TEnum)~std::underlying_type_t<TEnum>(a); }

template<typename TEnum>
bool hasFlag(TEnum flags, TEnum contains) {
	return (std::underlying_type_t<TEnum>(flags) & std::underlying_type_t<TEnum>(contains)) == std::underlying_type_t<TEnum>(contains);
}
