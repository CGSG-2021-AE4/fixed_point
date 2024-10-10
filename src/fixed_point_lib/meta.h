#ifndef __fixed_point_meta_h_
#define __fixed_point_meta_h_

template<class type, class ...options>
  concept AnyOf = (std::same_as<std::remove_cvref_t<type>, options> || ...);

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


#endif // __fixed_point_meta_h_