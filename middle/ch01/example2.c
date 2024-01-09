#include <stdio.h>
#include <unistd.h>

int main() {
  int pid;
  pid = fork();

  if (pid == 0) {
    execlp("InternetBrowser", "0", NULL);
    exit(0)
  } else {
    wait(NULL);
    printf("인터넷 브라우저 닫힘");
    exit(0);
  }
}