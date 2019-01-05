#include "cache.h"
#include <iostream>
#include <string>

int main() {
  // Input format:
  // First line: "s e b sz".
  // Then 4 types of operations (spaces must NOT be ignored):
  //   Read:    "R <addr>".
  //   Write:   "W <addr> <val>".
  //   Show:    "S".
  //   Comment: "// <...>".
  // Which "<addr>" is a 32 bits address in 16 base;
  //       "<val>" is a byte value in 16 base;
  //       "<...>" is any string without '\n'.
  // Input should end with EOF.
  using cache::uint;
  using cache::Addr;
  using cache::Byte;
  using std::cin;
  using std::cout;
  using std::endl;
  using cache::Cache;
  uint s, e, b, v;
  Addr sz, x;
  cin >> s >> e >> b >> sz;
  Cache mem(s, e, b, sz);
  std::string op;
  while (cin >> op) {
    cout << "operation: <" << op << ">" << endl;
    if (op == "R") {
      cin >> std::hex >> x >> std::dec;
      cout << "Read result: " << std::hex << std::showbase << +mem.read(x) << endl << std::dec;
    } else if (op == "W") {
      cin >> std::hex >> x >> v >> std::dec;
      mem.write(x, (Byte)v);
    } else if (op == "S") {
      mem.show();
    } else if (op == "//") {
      char c; c = cin.get();
      while (c != '\n') c = cin.get();
    } else {
      std::cerr << "Invalid operation code: " << op << std::endl;
      exit(1);
    }
  }
}
