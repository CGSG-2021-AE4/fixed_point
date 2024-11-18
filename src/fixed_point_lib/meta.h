#ifndef __fixed_point_meta_h_
#define __fixed_point_meta_h_

#include <cstdint>
#include <bitset>
#include <concepts>

template<class type, class ...options>
  concept AnyOf = (std::same_as<std::remove_cvref_t<type>, options> || ...);

template<class value_t>
  concept CheckValueT = std::is_integral_v<value_t> && sizeof(value_t) <= 32; // No support for types bigger than 32

template<typename T, T Value>
  struct get_value {
    enum { value = Value };
  };

template<typename T, T Value>
  struct compare_0 {
    enum { value = Value };
  };

// Does not compile with Shift as function argument
template<typename value_t, typename shift_t, shift_t Shift>
  constexpr value_t MaskFromShift() {
    static_assert(Shift < sizeof(value_t) * 8);
    return (value_t(1) << Shift) - 1;
  }

template<typename in_t> requires CheckValueT<in_t>
  struct double_size_t {
    //using type = std::conditional_t<sizeof(in_t) == 32, uint32_t, int64_t>; // 8 to 16
    using type = std::conditional_t<sizeof(in_t) == 8,
                 std::conditional_t<sizeof(in_t) == 16,
                 std::conditional_t<std::is_signed_v<in_t>, int16_t, uint16_t>, // 8 to 16
                 std::conditional_t<std::is_signed_v<in_t>, int32_t, uint32_t>>, // 16 to 32
                 std::conditional_t<std::is_signed_v<in_t>, int64_t, uint64_t>>;  // 32 to 64
  };

#endif // __fixed_point_meta_h_