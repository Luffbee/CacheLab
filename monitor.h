#ifndef MONITOR
#define MONITOR 1

namespace monitor {
  class Monitor {
    public:
      void show();
      void hit();
      void miss();
      void evict();
      void dirty();
      void undirty();
    private:
      unsigned int hit_cnt = 0;
      unsigned int miss_cnt = 0;
      unsigned int evict_cnt = 0;
      unsigned int dirty_cnt = 0;
  };
}
#endif
