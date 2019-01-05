#ifndef CACHE
#define CACHE 1

#include <vector>
#include <unordered_map>
#include "memory.h"
#include "monitor.h"

namespace cache {

  using std::vector;
  using std::unordered_map;
  using memory::Addr;
  using memory::Byte;
  using memory::Memory;
  using monitor::Monitor;
  using uint = unsigned int;

  struct Line {
    Line(uint b): block(1<<b) {};
    uint valid : 1;
    uint dirty : 1;
    Addr tag;
    vector<Byte> block;
  };

  class LRU {
    public:
      LRU(uint s, uint e);
      void access(Addr sid, uint k);
      uint get_room(Addr sid);
    private:
      struct Node {
        Node * pre = NULL;
        Node * nxt = NULL;
      };
      struct FixQueue {
        vector<Node> node;
        uint head, tail;

        FixQueue(uint sz);
        uint front();
        void mv_back(uint x);
      };
      vector<FixQueue> q;
  };

  class Cache {
    public:
      Cache(uint s, uint e, uint b, Addr sz);
      Byte read(Addr x);
      void write(Addr x, Byte v);
      void show();
    private:
      uint s, e, b, t;
      Memory mem;
      vector<vector<Line>> line;
      LRU scheduler;
      Monitor monitor;

      Addr get_set(Addr x);
      Addr get_tag(Addr x);
      Addr get_off(Addr x);

      uint find(vector<Line> & set, Addr tag);
      uint load(Addr sid, Addr x);
      void write_back(Addr sid, uint k);
      void access(Addr sid, uint k);
  };

}
#endif
