#ifndef __fixed_point_fixed_point_h_
#define __fixed_point_fixed_point_h_

#include <cstdint>
#include <concepts>

#include "meta.h"


// Shift has uint8 type because I do not expect it hight then 32
template<typename value_t, uint8_t Shift> requires std::is_integral_v<value_t>
  class fixed_point
  {
  private:
    value_t Value;

    // Fraction part mask
    static constexpr value_t Mask = MaskFromShift<value_t, uint8_t, Shift>();
    static constexpr value_t FractionSize = Mask + 1; // Size of fraction part (for casting from float point)


    // Constructor from raw value
    constexpr inline fixed_point( value_t NewValue ) noexcept :
      Value(NewValue) {
    }

  public:

    // Constructor from integer number
    template<typename T> requires std::is_integral_v<T>
      constexpr fixed_point(T IntValue) noexcept :
        Value(IntValue << Shift) {
      }

    // Constructor from float point number
    template<typename T> requires std::is_floating_point_v<T>
      constexpr fixed_point(T FloatValue) noexcept :
        Value(value_t(FloatValue * FractionSize)) {
      }

    // Copy/move constructor
    constexpr fixed_point( const fixed_point & ) = default;
    constexpr fixed_point( fixed_point && ) = default;
    constexpr fixed_point& operator=( const fixed_point & ) = default;
    constexpr fixed_point& operator=( fixed_point && ) = default;
    
    // Debug function
    constexpr value_t GetIntegerPart() const noexcept {
      return Value >> Shift;
    }
    
    // Debug function
    constexpr value_t GetFractionPart() const noexcept {
      return Value & Mask;
    }

    // Explicit conversion to integer number
    template<typename T> requires std::is_integral_v<T>
      constexpr explicit operator T() {
        return Value >> Shift;
      }
    
    // Explicit conversion to float point number
    template<typename T> requires std::is_floating_point_v<T>
      constexpr operator T() {
        return T(Value) / FractionSize;
      }

    // Operators

    constexpr inline fixed_point<value_t, Shift> operator+( fixed_point<value_t, Shift> Other ) const noexcept {
      return fixed_point<value_t, Shift>(Value + Other.Value);
    }
    
    constexpr auto operator-( const fixed_point<value_t, Shift> &Other ) const noexcept {
      return fixed_point<value_t, Shift>(Value - Other.Value);
    }

  };

#endif // __fixed_point_fixed_point_h_