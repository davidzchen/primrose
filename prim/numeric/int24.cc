#include "prim/numeric/int24.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>

namespace prim {

UInt24::UInt24(uint32_t value) {
  value &= UINT24_MAX;
  data_[0] = value & 0xFF;
  data_[1] = (value >> 8) & 0xFF;
  data_[2] = (value >> 16) & 0xFF;
}

auto UInt24::ToUInt32() const -> uint32_t {
  return (static_cast<uint32_t>(data_[2]) << 16) |
         (static_cast<uint32_t>(data_[1]) << 8) |
         static_cast<uint32_t>(data_[0]);
}

auto UInt24::operator+(const UInt24& rhs) const -> UInt24 {
  return UInt24((this->ToUInt32() + rhs.ToUInt32()) & UINT24_MAX);
}

auto UInt24::operator-(const UInt24& rhs) const -> UInt24 {
  return UInt24((this->ToUInt32() - rhs.ToUInt32()) & UINT24_MAX);
}

auto UInt24::operator*(const UInt24& rhs) const -> UInt24 {
  // Casting to size_t to resolve implicit widening conversion due to
  // multiplication warning.
  size_t value = static_cast<size_t>(this->ToUInt32()) * rhs.ToUInt32();
  return UInt24(static_cast<uint32_t>(value & UINT24_MAX));
}

auto UInt24::operator/(const UInt24& rhs) const -> UInt24 {
  return UInt24((this->ToUInt32() / rhs.ToUInt32()) & UINT24_MAX);
}

auto UInt24::operator%(const UInt24& rhs) const -> UInt24 {
  return UInt24(this->ToUInt32() % rhs.ToUInt32());
}

auto UInt24::operator-() const -> UInt24 {
  // Two's complement.
  return UInt24((-static_cast<int32_t>(this->ToUInt32())) & UINT24_MAX);
}

auto UInt24::operator+=(const UInt24& rhs) -> UInt24& {
  *this = *this + rhs;
  return *this;
}

auto UInt24::operator-=(const UInt24& rhs) -> UInt24& {
  *this = *this - rhs;
  return *this;
}

auto UInt24::operator*=(const UInt24& rhs) -> UInt24& {
  *this = *this * rhs;
  return *this;
}

auto UInt24::operator/=(const UInt24& rhs) -> UInt24& {
  *this = *this / rhs;
  return *this;
}

auto UInt24::operator%=(const UInt24& rhs) -> UInt24& {
  *this = *this % rhs;
  return *this;
}

auto UInt24::operator++() -> UInt24& {
  *this = *this + UInt24(1);
  return *this;
}

auto UInt24::operator++(int) -> UInt24 {
  UInt24 temp = *this;
  ++(*this);
  return temp;
}

auto UInt24::operator--() -> UInt24& {
  *this = *this - UInt24(1);
  return *this;
}

auto UInt24::operator--(int) -> UInt24 {
  UInt24 temp = *this;
  --(*this);
  return temp;
}

auto UInt24::operator&(const UInt24& rhs) const -> UInt24 {
  return UInt24(this->ToUInt32() & rhs.ToUInt32());
}

auto UInt24::operator|(const UInt24& rhs) const -> UInt24 {
  return UInt24(this->ToUInt32() | rhs.ToUInt32());
}

auto UInt24::operator^(const UInt24& rhs) const -> UInt24 {
  return UInt24(this->ToUInt32() ^ rhs.ToUInt32());
}

auto UInt24::operator<<(uint32_t rhs) const -> UInt24 {
  return UInt24((this->ToUInt32() << rhs) & UINT24_MAX);
}

auto UInt24::operator>>(uint32_t rhs) const -> UInt24 {
  return UInt24(this->ToUInt32() >> rhs);
}

auto UInt24::operator~() const -> UInt24 {
  return UInt24(~this->ToUInt32() & UINT24_MAX);
}

auto UInt24::operator&=(const UInt24& rhs) -> UInt24& {
  *this = *this & rhs;
  return *this;
}

auto UInt24::operator|=(const UInt24& rhs) -> UInt24& {
  *this = *this | rhs;
  return *this;
}

auto UInt24::operator^=(const UInt24& rhs) -> UInt24& {
  *this = *this ^ rhs;
  return *this;
}

auto UInt24::operator<<=(uint32_t rhs) -> UInt24& {
  *this = *this << rhs;
  return *this;
}

auto UInt24::operator>>=(uint32_t rhs) -> UInt24& {
  *this = *this >> rhs;
  return *this;
}

auto UInt24::operator==(const UInt24& rhs) const -> bool {
  return this->ToUInt32() == rhs.ToUInt32();
}

auto UInt24::operator!=(const UInt24& rhs) const -> bool {
  return !(*this == rhs);
}

auto UInt24::operator<(const UInt24& rhs) const -> bool {
  return this->ToUInt32() < rhs.ToUInt32();
}

auto UInt24::operator<=(const UInt24& rhs) const -> bool {
  return this->ToUInt32() <= rhs.ToUInt32();
}

auto UInt24::operator>(const UInt24& rhs) const -> bool {
  return this->ToUInt32() > rhs.ToUInt32();
}

auto UInt24::operator>=(const UInt24& rhs) const -> bool {
  return this->ToUInt32() >= rhs.ToUInt32();
}

auto UInt24::SwapEndian() -> void { std::swap(data_[0], data_[2]); }

}  // namespace prim
