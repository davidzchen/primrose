#ifndef PRIM_STRINGS_COLOR_H_
#define PRIM_STRINGS_COLOR_H_

#include <string>

#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

namespace prim::color {

constexpr char kRedEscape[] = "\033[1;31m";
constexpr char kGreenEscape[] = "\033[1;32m";
constexpr char kYellowEscape[] = "\033[1;33m";
constexpr char kBlueEscape[] = "\033[1;34m";
constexpr char kMagentaEscape[] = "\033[1;35m";
constexpr char kCyanEscape[] = "\033[1;36m";
constexpr char kWhiteEscape[] = "\033[1;37m";
constexpr char kResetEscape[] = "\033[0m";

inline auto Red(absl::string_view message) -> std::string {
  return absl::StrCat(kRedEscape, message, kResetEscape);
}

inline auto Green(absl::string_view message) -> std::string {
  return absl::StrCat(kGreenEscape, message, kResetEscape);
}

inline auto Yellow(absl::string_view message) -> std::string {
  return absl::StrCat(kYellowEscape, message, kResetEscape);
}

inline auto Blue(absl::string_view message) -> std::string {
  return absl::StrCat(kBlueEscape, message, kResetEscape);
}

inline auto Magenta(absl::string_view message) -> std::string {
  return absl::StrCat(kMagentaEscape, message, kResetEscape);
}

inline auto Cyan(absl::string_view message) -> std::string {
  return absl::StrCat(kCyanEscape, message, kResetEscape);
}

inline auto White(absl::string_view message) -> std::string {
  return absl::StrCat(kWhiteEscape, message, kResetEscape);
}

}  // namespace prim::color

#endif  // PRIM_STRINGS_COLOR_H_
