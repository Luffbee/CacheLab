#include <iostream>

using namespace std;

void write(int x, int v) {
  cout << "W " << hex << x << ' ' << v << endl << dec;
}

void read(int x) {
  cout << "R " << hex << x << endl << dec;
}

void show() {
  cout << "S" << endl;
}

int main() {
  freopen("copyshift_naive.in", "w", stdout);
  cout << "1 0 2 128" << endl;
  // A direct-mapped cache with 2 sets, which each can hold up to 4 bytes.
  // Variable location:
  // A: [0, 7]
  // B: [8, 15]
  // temp: [16, 23]
  
  // Init A
  for (int i = 0; i < 8; ++i) {
    write(i, i+66);
  }
  show();

  // clear cache
  read(16);
  read(20);
  show();
  
  // Start
  for (int i = 0; i < 7; ++i) {
    read(i);
    write(i+9, i+66);
  }
  read(7);
  write(8, 7+66);
  show();

  // Check B
  for (int i = 0; i < 8; ++i) {
    read(i+8);
  }
  show();
}
