#include <iostream>
#include "heap.h"
#include "Donut.h"
#include "hash.h"
using namespace std;
unsigned cyclic_hash16(string key);

int main(){
Heap<Donut> T;
HashTable<Donut> G(10, cyclic_hash16);
G.dump();
cout << cyclic_hash16("cinnamon") << endl;

G.insert(Donut("glazed", 5, "super donut"));
cout << cyclic_hash16("glazed") % 10 << endl;
G.dump();

return 0;
}


unsigned cyclic_hash16(string key) {
  unsigned usize = 16;
  unsigned s = 5; // shift by 5
  unsigned h = 0;
  for (auto c : key) {
    h = (( h << s ) | ( h >> (usize - s) ));
    h += c;
    h = h & 0xffff;
  }
  return h;
}
