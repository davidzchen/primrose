#ifndef PRIM_NUMERIC_INT24_H_
#define PRIM_NUMERIC_INT24_H_

#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace prim {

// Max value for a 24-bit unsigned integer (0xFFFFFF)
constexpr size_t UINT24_MAX = (1 << 24) - 1;  // NOLINT

class UInt24 {
 public:
  UInt24() : data_{0, 0, 0} {}

  // Intentionally mark this as NOLINT to allow implicit conversions.
  UInt24(uint32_t value);  // NOLINT

  // Constructs a UInt24 from raw data.
  explicit UInt24(std::array<uint8_t, 3> data) : data_(data) {}

  // Assignment operator.
  auto operator=(const UInt24& rhs) -> UInt24& = default;

  // Converts the 24-bit integer to a uint32_t.
  auto ToUInt32() const -> uint32_t;

  // Arithmetic operators.
  auto operator+(const UInt24& rhs) const -> UInt24;
  auto operator-(const UInt24& rhs) const -> UInt24;
  auto operator*(const UInt24& rhs) const -> UInt24;
  auto operator/(const UInt24& rhs) const -> UInt24;
  auto operator%(const UInt24& rhs) const -> UInt24;
  auto operator-() const -> UInt24;

  // Arithmetic assignment operators.
  auto operator+=(const UInt24& rhs) -> UInt24&;
  auto operator-=(const UInt24& rhs) -> UInt24&;
  auto operator*=(const UInt24& rhs) -> UInt24&;
  auto operator/=(const UInt24& rhs) -> UInt24&;
  auto operator%=(const UInt24& rhs) -> UInt24&;

  // Increment/Decrement
  auto operator++() -> UInt24&;    // Pre-increment
  auto operator++(int) -> UInt24;  // Post-increment
  auto operator--() -> UInt24&;    // Pre-decrement
  auto operator--(int) -> UInt24;  // Post-decrement

  // Bitwise operators.
  auto operator&(const UInt24& rhs) const -> UInt24;
  auto operator|(const UInt24& rhs) const -> UInt24;
  auto operator^(const UInt24& rhs) const -> UInt24;
  auto operator<<(uint32_t rhs) const -> UInt24;
  auto operator>>(uint32_t rhs) const -> UInt24;
  auto operator~() const -> UInt24;

  // Bitwise assignment operators.
  auto operator&=(const UInt24& rhs) -> UInt24&;
  auto operator|=(const UInt24& rhs) -> UInt24&;
  auto operator^=(const UInt24& rhs) -> UInt24&;
  auto operator<<=(uint32_t rhs) -> UInt24&;
  auto operator>>=(uint32_t rhs) -> UInt24&;

  // Comparison operators.
  auto operator==(const UInt24& rhs) const -> bool;
  auto operator!=(const UInt24& rhs) const -> bool;
  auto operator<(const UInt24& rhs) const -> bool;
  auto operator<=(const UInt24& rhs) const -> bool;
  auto operator>(const UInt24& rhs) const -> bool;
  auto operator>=(const UInt24& rhs) const -> bool;

  // Swaps the endianness of this value.
  auto SwapEndian() -> void;

  // For printing UInt24
  friend auto operator<<(std::ostream& os, const UInt24& value)
      -> std::ostream& {
    os << value.ToUInt32();
    return os;
  }

 private:
  std::array<uint8_t, 3> data_;
};

static_assert(sizeof(UInt24) == 3);

}  // namespace prim

#endif  // PRIM_NUMERIC_INT24_H_
