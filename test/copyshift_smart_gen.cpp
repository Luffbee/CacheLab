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
  freopen("copyshift_smart.in", "w", stdout);
  cout << "1 0 2 128" << endl;
  // A direct-mapped cache with 2 sets, which each can hold up to 4 bytes.
  // Variable location:
  // A: [0, 7]
  // B: [8, 15]
  // temp: [16, 23]
  int A = 0;
  int B = 8;
  int tmp = 16;
  
  // Init A
  for (int i = 0; i < 8; ++i) {
    write(i, i+66);
  }
  show();
  
  // clear cache
  read(24);
  read(28);
  show();

  // Start
  read(A+5);
  write(tmp+1, 5+66);
  read(A+6);
  write(tmp+2, 6+66);

  read(A+4);
  write(B+5, 4+66);

  read(tmp+1);
  write(B+6, 5+66);
  read(tmp+2);
  write(B+7, 6+66);
  
  read(A+3);
  write(B+4, 3+66);

  read(A+1);
  write(tmp+5, 1+66);
  read(A+2);
  write(tmp+6, 2+66);

  read(A+0);
  write(B+1, 0+66);

  read(tmp+5);
  write(B+2, 1+66);
  read(tmp+6);
  write(B+3, 2+66);

  read(A+7);
  write(B+0, 7+66);

  show();

  // Check B
  for (int i = 0; i < 8; ++i) {
    read(i+8);
  }
  show();
}
