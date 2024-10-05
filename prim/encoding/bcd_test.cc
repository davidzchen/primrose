#include "prim/encoding/bcd.h"

#include <cstdint>
#include <vector>

#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

namespace prim {
namespace {

TEST(FromBCD, Zero) {
  std::vector<unsigned char> bcd0;
  EXPECT_THAT(FromBCD(bcd0), ::testing::Eq(0));

  std::vector<unsigned char> bcd1 = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  EXPECT_THAT(FromBCD(bcd1), ::testing::Eq(0));
}

TEST(FromBCD, Valid) {
  std::vector<unsigned char> bcd0 = {0x00, 0x31, 0x75};
  EXPECT_THAT(FromBCD(bcd0), ::testing::Eq(3175));

  std::vector<unsigned char> bcd1 = {0x00, 0x30, 0x00};
  EXPECT_THAT(FromBCD(bcd1), ::testing::Eq(3000));
}

TEST(ToBCD, Valid) {
  uint32_t i0 = 0;
  std::vector<unsigned char> want0 = {};
  EXPECT_THAT(ToBCD(i0), ::testing::Eq(want0));

  uint32_t i1 = 3175;
  std::vector<unsigned char> want1 = {0x31, 0x75};
  EXPECT_THAT(ToBCD(i1), ::testing::Eq(want1));

  uint32_t i2 = 3000;
  std::vector<unsigned char> want2 = {0x30, 0x00};
  EXPECT_THAT(ToBCD(i2), ::testing::Eq(want2));

  uint32_t i3 = 0xFFFFFFFF;
  std::vector<unsigned char> want3 = {0x42, 0x94, 0x96, 0x72, 0x95};
  EXPECT_THAT(ToBCD(i3), ::testing::Eq(want3));
}

}  // namespace
}  // namespace prim
