#ifndef __print_h_
#define __print_h_

#include <iostream>

using byte = unsigned char;

// Print function

// Simple colored print function
template<typename ...args>
  constexpr void Print( byte R, byte G, byte B, const char *Format, args ...Args ) {
    std::print("\x1b[38;2;{};{};{}m{}\x1b[38;2;255;255;255m", R, G, B, Format, std::forward<args>(Args)...);
  }

// The same function but color as template argument
template<byte R, byte G, byte B, typename ...args>
  constexpr void Print( const char *Format, args ...Args ) {
    std::print("\x1b[38;2;{};{};{}m{}\x1b[38;2;255;255;255m", R, G, B, Format, std::forward<args>(Args)...);
  }

// Printf function

// Simple colored printF function
template<typename ...args>
  constexpr void Printf( byte R, byte G, byte B, const char *Format, args ...Args ) {
    std::printf(std::format("\x1b[38;2;{};{};{}m{}\x1b[38;2;255;255;255m", R, G, B, Format), std::forward<args>(Args)...);
  }

// The same function but color as template argument
template<byte R, byte G, byte B, typename ...args>
  constexpr void Printf( const char *Format, args ...Args ) {
    std::printf(std::format("\x1b[38;2;{};{};{}m{}\x1b[38;2;255;255;255m", R, G, B, Format).c_str(), std::forward<args>(Args)...);
  }

#endif // __print_h_