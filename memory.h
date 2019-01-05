#ifndef MEMORY
#define MEMORY 1
#include <vector>
#include <cassert>
#include <cstdint>
namespace memory {

  using std::vector;
  using Addr = uint32_t;
  using Byte = uint8_t;

  class Memory {
    public:
      Memory(Addr size): data(size) {};
      Byte & operator[] (Addr x) { return data[x]; }
      // copy from memory
      void memcpy(Byte * dst, Addr src, size_t n);
      // copy to memory
      void memcpy(Addr dst, Byte * src, size_t n);
    private:
      vector<Byte> data;
  };
}
#endif
