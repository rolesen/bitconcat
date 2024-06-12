#pragma once

#include <cstdint>
#include <type_traits>

//bitwise shift together into new type (and avoid implicit type promotions)
template<class R>
struct bitconcat {
template<class T1, class... Args>
    constexpr R operator()(T1 t1, Args... arg) const {
        static_assert(std::is_unsigned_v<T1>);
        static_assert((std::is_unsigned_v<Args> && ...));
        static_assert((sizeof(Args) + ...) + sizeof(T1) <= sizeof(R), "result size of bitshift is higher than supported by return type (unsafe/possible loss of data)");
        R result{t1};
        (((result <<= (sizeof(arg) * 8)) |= arg), ...);//fold expression comma operator trick
        return result;
    }
};

constexpr bitconcat<uint64_t> bitconcat_u64;
constexpr bitconcat<uint32_t> bitconcat_u32;
constexpr bitconcat<uint16_t> bitconcat_u16;


//same as bitconcat, but using individual bits/bools
template<class R>
struct bitconcat_bits {
template<class... Args>
    constexpr R operator()(bool t1, Args... arg) const {
        static_assert((sizeof...(Args)) + 1 <= 8*sizeof(R), "result size of bitshift is higher than supported by return type (unsafe/possible loss of data)");
        R result{t1};
        (((result <<= 1) |= (arg ? true : false)), ...);
        return result;
    }
};

constexpr bitconcat_bits<uint64_t> bitconcat_bits_u64;
constexpr bitconcat_bits<uint32_t> bitconcat_bits_u32;
constexpr bitconcat_bits<uint16_t> bitconcat_bits_u16;
constexpr bitconcat_bits<uint8_t > bitconcat_bits_u8;
