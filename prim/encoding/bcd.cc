#include "prim/encoding/bcd.h"

#include <algorithm>
#include <cstdint>
#include <vector>

namespace prim {

uint32_t FromBCD(const std::vector<unsigned char>& bytes) {
  return FromBCD(absl::MakeConstSpan(bytes));
}

uint32_t FromBCD(const absl::Span<const unsigned char>& bytes) {
  uint32_t sum = 0;
  uint32_t weight = 1;
  for (int i = bytes.size() - 1; i >= 0; --i) {
    unsigned char bcd = bytes[i];
    sum += (bcd & 0xF) * weight;
    weight *= 10;
    sum += (bcd >> 4) * weight;
    weight *= 10;
  }
  return sum;
}

std::vector<unsigned char> ToBCD(uint32_t n) {
  std::vector<unsigned char> bytes;
  uint32_t dec = n;
  while (dec > 0) {
    unsigned char lower = static_cast<unsigned char>(dec % 10);
    dec /= 10;
    unsigned char upper = static_cast<unsigned char>(dec % 10);
    dec /= 10;
    bytes.push_back(lower | (upper << 4));
  }
  std::reverse(bytes.begin(), bytes.end());
  return bytes;
}

}  // namespace prim
