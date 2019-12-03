#include <iostream>
#include "heap.h"
#include "Donut.h"

using namespace std;

int main(){
Heap<Donut> T;
T.insert(Donut("glazed", 5, "super donut"));
T.insert(Donut("sprinkle", 8, "shack of donuts"));
T.insert(Donut("glazed", 12, "mega donut"));
T.insert(Donut("boston cream", 3, "donut joint"));
T.insert(Donut("bonston cream", 10, "mega donut"));
T.insert(Donut("cinnamon", 3, "shack of donuts"));
T.insert(Donut("sprinkle", 7, "donut world"));

T.insert(Donut("sprinkle", 15, "super donut"));

T.dump();

T.removeTop();

T.dump();

T.removeTop();
T.dump();
T.removeTop();
T.dump();
T.removeTop();
T.dump();
T.removeTop();
T.dump();
return 0;
}

