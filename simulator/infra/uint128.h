/**
 * types.h - 128 bit type declaration
 *
 * @author Pavel Kryukov
 */

#ifndef UINT128_TYPES_H
#define UINT128_TYPES_H

// Please do not include this file everywhere to reduce compilation speed

#include <infra/macro.h>
#include <infra/types.h>

#include <boost/multiprecision/cpp_int.hpp>

using int128  = boost::multiprecision::int128_t;
using uint128 = boost::multiprecision::uint128_t;

using int256  = boost::multiprecision::int256_t;
using uint256 = boost::multiprecision::uint256_t;

template<> inline constexpr bool is_wide_integer_v<int128> = true;
template<> inline constexpr bool is_wide_integer_v<uint128> = true;
template<> inline constexpr bool is_wide_integer_v<int256> = true;
template<> inline constexpr bool is_wide_integer_v<uint256> = true;

template<> inline constexpr bool is_wide_signed_integer_v<int128> = true;
template<> inline constexpr bool is_wide_signed_integer_v<int256> = true;

template<> struct unsigned_integer<128> { using type = uint128; };
template<> struct signed_integer<128>   { using type = int128; };
template<> struct unsigned_integer<256> { using type = uint256; };
template<> struct signed_integer<256>   { using type = int256; };
template<> inline constexpr size_t bitwidth<uint128> = 128U;
template<> inline constexpr size_t bitwidth<int128> = 128U;
template<> inline constexpr size_t bitwidth<uint256> = 256U;
template<> inline constexpr size_t bitwidth<int256> = 256U;

inline int128 signify( uint128 value)
{
    const uint128 no_sign = value & ~msb_set<uint128>();
    const int128 abs = int128{ no_sign};
    return value != no_sign ? -abs : abs;
}

#endif // #ifndef COMMON_TYPES_H
