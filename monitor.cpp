#include "monitor.h"
#include <iostream>

using namespace monitor;

void Monitor::show() {
  using std::cout;
  using std::endl;
  cout << "----------------------------" << endl;
  cout << "hit:        " << hit_cnt << endl;
  cout << "miss:       " << miss_cnt << endl;
  cout << "eviction:   " << evict_cnt << endl;
  cout << "dirty:      " << dirty_cnt << endl;
  cout << "----------------------------" << endl;
}

void Monitor::hit() {
  hit_cnt++;
}

void Monitor::miss() {
  miss_cnt++;
}

void Monitor::evict() {
  evict_cnt++;
}

void Monitor::dirty() {
  dirty_cnt++;
}

void Monitor::undirty() {
  dirty_cnt--;
}
