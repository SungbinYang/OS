#include <stdio.h>

int main() {
  int fd;
  fd = open("./test.txt", O_RDONLY);
  close(fd);
}
