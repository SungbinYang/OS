#include <iostream>
#include <Windows.h>
#include <process.h>

int g_data;
bool g_bFlag = true;
HANDLE g_hThreadExit01, g_hThreadExit02, g_hThreadExit03;

void threadFunction01(void* pArgs) {
  std::cout << "threadFunction01 - Begin\n";

  while (g_bFlag) {
    g_data = 1000;
  }
  
  std::cout << "threadFunction01 - End\n";
  ::SetEvent(g_hThreadExit01);
}

void threadFunction02(void* pArgs) {
  std::cout << "threadFunction02 - Begin\n";

  while (g_bFlag) {
    g_data = 2000;
  }

  std::cout << "threadFunction02 - End\n";
  ::SetEvent(g_hThreadExit02);
}

void threadFunction03(void* pArgs) {
  for (int i = 0; i < 10; ++i) {
    std::cout << "threadFunction03() g_data: " << g_data << std::endl;
    Sleep(0);
  }

  ::SetEvent(g_hThreadExit03);
}

int main() {
  std::cout << "Hello World! - Begin\n";

  g_bFlag = true;

  g_hThreadExit01 = ::CreateEventA(nullptr, true, false, "T_THREAD_01");
  g_hThreadExit02 = ::CreateEventA(nullptr, true, false, "T_THREAD_02");
  g_hThreadExit03 = ::CreateEventA(nullptr, true, false, "T_THREAD_03");

  ::_beginthread(threadFunction01, 0, nullptr);
  ::_beginthread(threadFunction02, 0, nullptr);

  ::Sleep(10);

  ::_beginthread(threadFunction03, 0, nullptr);

  // 호출자 쓰레드가 대기상태로 전환
  // ::Sleep(100); // 우연에 맡기는 코드

  ::WaitForSingleObject(g_hThreadExit03, INFINITE);

  g_bFlag = false;

  // T1, T2의 종료 이벤트를 대기
  ::WaitForSingleObject(g_hThreadExit01, INFINITE);
  ::WaitForSingleObject(g_hThreadExit02, INFINITE);

  ::CloseHandle(g_hThreadExit01);
  ::CloseHandle(g_hThreadExit02);
  ::CloseHandle(g_hThreadExit03);

  std::cout << "Hello World! - End\n";
}