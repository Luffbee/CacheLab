#include <cstring>
#include "memory.h"

using namespace memory;

void Memory::memcpy(Byte * dst, Addr src, size_t n) {
  assert(src+n <= data.size());
  std::memcpy(dst, &data[src], n);
}

void Memory::memcpy(Addr dst, Byte * src, size_t n) {
  assert(dst+n <= data.size());
  std::memcpy(&data[dst], src, n);
}
