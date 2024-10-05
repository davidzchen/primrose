// -----------------------------------------------------------------------------
// File: bcd.h
// -----------------------------------------------------------------------------
//
// This header contains the Binary-Coded Decimal conversion library.

#ifndef PRIM_ENCODING_BCD_H_
#define PRIM_ENCODING_BCD_H_

#include <cstdint>
#include <vector>

#include "absl/types/span.h"

namespace prim {

// Converts a binary-coded decimal represented in a series of bytes (two digits
// represented by each byte) into an 32-bit integer value.
//
// Note: If the number represented by the bytes exceed the size of a uint32,
// the conversion will silently overflow.
uint32_t FromBCD(const std::vector<unsigned char>& bytes);
uint32_t FromBCD(const absl::Span<const unsigned char>& bytes);

// Converts an unsigned 32-bit integer into its binary-coded-decimal
// representation.
std::vector<unsigned char> ToBCD(const uint32_t n);

}  // namespace prim

#endif  // PRIM_ENCODING_BCD_H_
