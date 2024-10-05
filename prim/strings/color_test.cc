#include "prim/strings/color.h"

#include "gtest/gtest.h"

namespace prim::color {
namespace {

TEST(Colors, All) {
  EXPECT_EQ(Red("red"), "\033[1;31mred\033[0m");
  EXPECT_EQ(Green("green"), "\033[1;32mgreen\033[0m");
  EXPECT_EQ(Yellow("yellow"), "\033[1;33myellow\033[0m");
  EXPECT_EQ(Blue("blue"), "\033[1;34mblue\033[0m");
  EXPECT_EQ(Magenta("magenta"), "\033[1;35mmagenta\033[0m");
  EXPECT_EQ(Cyan("cyan"), "\033[1;36mcyan\033[0m");
  EXPECT_EQ(White("white"), "\033[1;37mwhite\033[0m");
}

}  // namespace
}  // namespace prim::color
