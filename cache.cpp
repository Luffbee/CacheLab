#include "cache.h"
#include <cassert>

using namespace cache;

LRU::LRU(uint s, uint e) {
  q.reserve(1U<<s);
  for (uint i = 0; i < (1U<<s); ++i) {
    q.emplace_back(1U<<e);
  }
}

void LRU::access(Addr sid, uint k) {
  q[sid].mv_back(k);
}

uint LRU::get_room(Addr sid) {
  uint k = q[sid].front();
  q[sid].mv_back(k);
  return k;
}

LRU::FixQueue::FixQueue(uint sz): node(sz) {
  head = 0, tail = sz-1;
  if (1 < sz) {
    node[0].nxt = &node[1];
    node[sz-1].pre = &node[sz-2];
  }
  for (uint i = 1; i+1 < sz; ++i) {
    node[i].nxt = &node[i+1];
    node[i].pre = &node[i-1];
  }
}

uint LRU::FixQueue::front() {
  return head;
}

void LRU::FixQueue::mv_back(uint x) {
  if (tail == x) return;
  auto & o = node[x];
  if (o.pre) o.pre->nxt = o.nxt;
  if (o.nxt) o.nxt->pre = o.pre;
  if (head == x) head = o.nxt - &node[0];
  node[tail].nxt = &o;
  o.pre = &node[tail];
  o.nxt = NULL;
  tail = x;
}

Cache::Cache(uint _s, uint _e, uint _b, Addr sz):
  s(_s), e(_e), b(_b),
  mem(sz), line(1U<<s), scheduler(s, e) {
  assert(s + b <= 8*sizeof(Addr));
  t = 8*sizeof(Addr) - s - b;
  for (auto & s : line) {
    s.reserve(1U<<e);
    for (uint i = 0; i < (uint)(1U<<e); ++i)
      s.emplace_back(b);
  }
}

Addr Cache::get_set(Addr x) {
  return (x << t) >> (t + b);
}

Addr Cache::get_tag(Addr x) {
  return x >> (s + b);
}

Addr Cache::get_off(Addr x) {
  return x & ((uint)(1U<<b) - 1);
}

Byte Cache::read(Addr x) {
  Addr sid = get_set(x);
  Addr tag = get_tag(x);
  Addr off = get_off(x);
  auto & set = line[sid];

  uint k = find(set, tag);
  
  if (k < set.size()) {
    monitor.hit();
    access(sid, k);
    return set[k].block[off];
  } else {
    monitor.miss();
    k = load(sid, x - off);
    assert(set[k].dirty == 0);
    return set[k].block[off];
  }
}

void Cache::write(Addr x, Byte v) {
  Addr sid = get_set(x);
  Addr tag = get_tag(x);
  Addr off = get_off(x);
  auto & set = line[sid];

  uint k = find(set, tag);

  if (k < set.size()) {
    monitor.hit();
    access(sid, k);
    if (!set[k].dirty) {
      monitor.dirty();
      set[k].dirty = 1;
    }
    set[k].block[off] = v;
  } else {
    monitor.miss();
    k = load(sid, x - off);
    monitor.dirty();
    set[k].dirty = 1;
    set[k].block[off] = v;
  }
}

void Cache::show() {
  monitor.show();
}

uint Cache::find(vector<Line> & set, Addr tag) {
  uint k;
  for (k = 0; k < set.size(); k++) {
    if (set[k].valid && set[k].tag == tag) break;
  }
  return k;
}

uint Cache::load(Addr sid, Addr x) {
  uint k = scheduler.get_room(sid);
  auto & li = line[sid][k];
  if (li.valid && li.dirty) {
    write_back(sid, k);
    li.dirty = 0;
    monitor.undirty();
    monitor.evict();
  } else if (li.valid) {
    monitor.evict();
  } else {
    li.valid = 1;
    li.dirty = 0;
  }
  mem.memcpy(&li.block[0], x, 1U<<b);
  li.tag = get_tag(x);
  return k;
}

void Cache::write_back(Addr sid, Addr k) {
  auto & li = line[sid][k];
  Addr x = (li.tag << (s+b)) | (sid << b);
  mem.memcpy(x, &li.block[0], 1U<<b);
}

void Cache::access(Addr sid, uint k) {
  scheduler.access(sid, k);
}
