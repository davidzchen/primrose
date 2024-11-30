#include "prim/numeric/int24.h"

#include <array>
#include <cstdint>

#include "gtest/gtest.h"

namespace prim {
namespace {

TEST(UInt24, Construction) {
  EXPECT_EQ(UInt24(), 0);
  EXPECT_EQ(UInt24(24), 24);
  EXPECT_EQ(UInt24(0xFFFFFFFF), 0xFFFFFF);  // Extra bits truncated.
  EXPECT_EQ(UInt24({0xAA, 0xBB, 0xCC}), 0xCCBBAA);
}

TEST(UInt24, Arithmetic) {
  // Addition
  EXPECT_EQ(UInt24(0) + 1, 0 + 1);
  EXPECT_EQ(UInt24(1) + 1, 1 + 1);
  EXPECT_EQ(UInt24(UINT24_MAX) + 1, 0);  // Overflow rolls over.

  // Subtraction
  EXPECT_EQ(UInt24(1) - 0, 1 - 0);
  EXPECT_EQ(UInt24(1) - 1, 1 - 1);
  EXPECT_EQ(UInt24(0) - 1, UINT24_MAX);  // Underflow rolls over.

  // Multiplication
  EXPECT_EQ(UInt24(1) * 0, 1 * 0);
  EXPECT_EQ(UInt24(2) * 2, 2 * 2);
  EXPECT_EQ(UInt24(UINT24_MAX) * 2, (UINT24_MAX * 2) & UINT24_MAX);

  // Division
  EXPECT_EQ(UInt24(0) / 1, 0 / 1);
  EXPECT_EQ(UInt24(4) / 2, 4 / 2);
  EXPECT_EQ(UInt24(1) / 2, 1 / 2);

  // Modulus
  EXPECT_EQ(UInt24(2) % 2, 2 % 2);
  EXPECT_EQ(UInt24(3) % 2, 3 % 2);

  // Negation (Two's Complement)
  EXPECT_EQ(-UInt24(0), -0);
  EXPECT_EQ(-UInt24(1), -1);
  EXPECT_EQ(-UInt24(UINT24_MAX), (-UINT24_MAX) & UINT24_MAX);
}

TEST(UInt24, ArithmeticAssignment) {
  UInt24 a = 0;
  a += 24;
  EXPECT_EQ(a, 24);
  a -= 23;
  EXPECT_EQ(a, 1);
  a *= 24;
  EXPECT_EQ(a, 24);
  a /= 2;
  EXPECT_EQ(a, 12);

  // Overflow/underflow
  UInt24 b = UINT24_MAX;
  b += 1;
  EXPECT_EQ(b, 0);
  b -= 1;
  EXPECT_EQ(b, UINT24_MAX);
}

TEST(UInt24, IncrementDecrement) {
  UInt24 a = 0;
  EXPECT_EQ(++a, 1);
  EXPECT_EQ(a, 1);
  EXPECT_EQ(a++, 1);
  EXPECT_EQ(a, 2);

  UInt24 b = 2;
  EXPECT_EQ(--b, 1);
  EXPECT_EQ(b, 1);
  EXPECT_EQ(b--, 1);
  EXPECT_EQ(b, 0);

  UInt24 c = UINT24_MAX;
  EXPECT_EQ(++c, 0);
  EXPECT_EQ(c, 0);
  EXPECT_EQ(c--, 0);
  EXPECT_EQ(c, UINT24_MAX);
}

TEST(UInt24, Bitwise) {
  // Bitwise AND
  EXPECT_EQ(UInt24(0x0) & UInt24(0x0), 0x0 & 0x0);
  EXPECT_EQ(UInt24(0x24) & UInt24(0xF0), 0x24 & 0xF0);

  // Bitwise OR
  EXPECT_EQ(UInt24(0x0) | UInt24(0x0), 0x0 | 0x0);
  EXPECT_EQ(UInt24(0x24) | UInt24(0xF0), 0x24 | 0xF0);

  // Bitwise XOR
  EXPECT_EQ(UInt24(0x0) ^ UInt24(0x0), 0x0 ^ 0x0);
  EXPECT_EQ(UInt24(0x24) ^ UInt24(0xF0), 0x24 ^ 0xF0);

  // Left Shift
  EXPECT_EQ(UInt24(0x1) << 2, 1 << 2);
  EXPECT_EQ(UInt24(UINT24_MAX) << 1, (UINT24_MAX << 1) & UINT24_MAX);

  // Right Shift
  EXPECT_EQ(UInt24(0xFF) >> 2, 0xFF >> 2);
  EXPECT_EQ(UInt24(UINT24_MAX) >> 2, UINT24_MAX >> 2);

  // Complement
  EXPECT_EQ(~UInt24(0xFF), ~0xFF);
  EXPECT_EQ(~UInt24(UINT24_MAX), (~UINT24_MAX) & UINT24_MAX);
}

TEST(UInt24, BitwiseAssignment) {
  UInt24 a = 0xF;
  a &= 0xC;
  EXPECT_EQ(a, 0xF & 0xC);

  UInt24 b = 0xF;
  b |= 0xC;
  EXPECT_EQ(b, 0xF | 0xC);

  UInt24 c = 0xF;
  c ^= 0xC;
  EXPECT_EQ(c, 0xF ^ 0xC);

  UInt24 d = 0xF;
  d <<= 0xC;
  EXPECT_EQ(d, 0xF << 0xC);

  UInt24 e = UINT24_MAX;
  e <<= 1;
  EXPECT_EQ(e, (UINT24_MAX << 1) & UINT24_MAX);

  UInt24 f = 0xF;
  f >>= 0xC;
  EXPECT_EQ(f, 0xF >> 0xC);
}

TEST(UInt24, Comparison) {
  EXPECT_TRUE(UInt24(24) == UInt24(24));
  EXPECT_TRUE(UInt24(24) != UInt24(23));

  EXPECT_TRUE(UInt24(24) > UInt24(23));
  EXPECT_TRUE(UInt24(23) < UInt24(24));

  EXPECT_TRUE(UInt24(24) >= UInt24(23));
  EXPECT_TRUE(UInt24(24) >= UInt24(24));

  EXPECT_TRUE(UInt24(23) <= UInt24(24));
  EXPECT_TRUE(UInt24(24) <= UInt24(24));
}

TEST(UInt24, SwapEndian) {
  UInt24 a = 0xAABBCC;
  a.SwapEndian();
  EXPECT_EQ(a, 0xCCBBAA);
}

TEST(UInt24, Data) {
  UInt24 a = 0xAABBCC;
  const std::array<uint8_t, 3>& data = a.data();
  UInt24 b(data);
  EXPECT_EQ(b, a);
}

}  // namespace
}  // namespace prim
