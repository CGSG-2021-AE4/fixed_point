#ifndef __fixed_point_fixed_point_h_
#define __fixed_point_fixed_point_h_

#include <cstdint>
#include <concepts>

#include "meta.h"

// Shift has uint8 type because I do not expect it hight then 32
template<typename value_t, uint8_t FractionalShift> requires std::is_integral_v<value_t>
  class fixed_point
  {
  private:
    value_t Value;

    static constexpr uint8_t Shift = FractionalShift; // For outer usage
    static constexpr value_t Mask = MaskFromShift<value_t, uint8_t, Shift>();
    static constexpr value_t FractionSize = Mask + 1; // Size of fraction part (for casting from float point)
    static constexpr value_t SignBitMask = 1 << (sizeof(value_t) * 8 - 1);

    // Constructor from raw value
    explicit constexpr fixed_point( value_t NewValue ) noexcept :
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

    // Copy/move constructors
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
      constexpr explicit operator T() {
        return T(Value) / FractionSize;
      }

    // Operators

    // "+"

    constexpr fixed_point operator+( fixed_point Other ) const noexcept {
      return fixed_point(Value + Other.Value);
    }
    
    constexpr fixed_point & operator+=( fixed_point Other ) noexcept {
      Value += Other.Value;
      return *this;
    }
    
    // "-"

    constexpr fixed_point operator-( fixed_point Other ) const noexcept {
      return fixed_point(Value - Other.Value);
    }
    
    constexpr fixed_point & operator-=( fixed_point Other ) noexcept {
      Value -= Other.Value;
      return *this;
    }
    
    // "*"

    // With int type because this case is simple
    template<typename other_t> requires std::is_integral_v<other_t>
      constexpr fixed_point operator*( other_t Other ) const noexcept {
        return Value * Other;
      }

    constexpr fixed_point operator*( fixed_point Other ) const noexcept {
      // Simple way "(Value * Other.Value) >> Shift" can overflow value_t so up to "Shift" higher bits could be lost
      // Here every component is less then out value so there is no overflow
      // But now it is slow because(if at debug dissambly is the same as at release) cpp does not store Value and Other.Value at registers and get them from memory several times

      value_t out = Value * (Other.Value >> Shift) + (Value >> Shift) * (Other.Value & Mask) + (((Value & Mask) * (Other.Value & Mask)) >> Shift);
      if constexpr (std::is_signed_v<value_t>) // Sign check
        out |= (Value & SignBitMask) ^ (Other.Value & SignBitMask);
      return out;

      // Too big error rate
      //return (Value * Other.Value) >> Shift;
      //return Value * (Other.Value >> Shift) + ((Value * (Other.Value & Mask)) >> Shift);
    }
    
    constexpr fixed_point operator*=( fixed_point Other ) const noexcept {
      //Value = Value * (Other.Value >> Shift) + (Value >> Shift) * (Other.Value & Mask) + (((Value & Mask) * (Other.Value & Mask)) >> Shift);
      return *this;
    }
    

  };

#endif // __fixed_point_fixed_point_h_