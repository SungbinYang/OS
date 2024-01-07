#include <iostream>

int g_data = 20;

int main() {
  int a = 16;
  int b = 32;
  int c = 64;

  printf("%p: %d\n", &a, a);
  printf("%p: %d\n", &b, b);
  printf("%p: %d\n", &c, c);

  *((int *)0x0041A008) = 32;
  printf("%d\n", g_data);

  int arList[3] = {16, 32, 64};
  printf("%p: %d\n", arList, arList[2]);
}