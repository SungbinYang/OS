#include <stdio.h>

typedef enum
{
  false,
  true
} boolean;

extern boolean lock = false;

extern int balance;

void main() {
  while (lock == true);
  lock = true;
  balance = balance + 10; // 임계구역
  lock = false;
}