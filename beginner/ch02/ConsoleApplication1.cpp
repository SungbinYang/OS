#include <iostream>
#include <Windows.h>
#include <process.h>

int g_data;

bool g_bFlag = true;

void threadFunction01(void* pArgs) {
  std::cout << "threadFunction01 - Begin\n";

  while (g_bFlag) {
    g_data = 1000;
  }
  
  std::cout << "threadFunction01 - End\n";
}

void threadFunction02(void* pArgs) {
  std::cout << "threadFunction02 - Begin\n";

  while (g_bFlag) {
    g_data = 2000;
  }

  std::cout << "threadFunction02 - End\n";
}

void threadFunction03(void* pArgs) {
  for (int i = 0; i < 10; ++i) {
    std::cout << "threadFunction03() g_data: " << g_data << std::endl;
    Sleep(0);
  }
}

int main() {
  std::cout << "Hello World! - Begin\n";

  g_bFlag = true;

  ::_beginthread(threadFunction01, 0, nullptr);
  ::_beginthread(threadFunction02, 0, nullptr);
  ::_beginthread(threadFunction03, 0, nullptr);

  // 호출자 쓰레드가 대기상태로 전환
  ::Sleep(100); // 우연에 맡기는 코드

  g_bFlag = false;

  std::cout << "Hello World! - End\n";
}