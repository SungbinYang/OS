#include <stdio.h>

int main() {
  int fd;
  fd = open("./test.txt", O_RDONLY);
  lseek(fd, 10, SEEK_CUR); // 현재 위치에서 10번 앞으로 이동
  close(fd);
}
