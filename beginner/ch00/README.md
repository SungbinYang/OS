> 이 포스트는 [널널한 개발자](https://www.inflearn.com/course/%EA%B3%B0%EC%B1%85-%EC%89%BD%EA%B2%8C-%EB%B0%B0%EC%9A%B0%EB%8A%94-%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C/dashboard)님의 강의를 듣고 작성한 글입니다.

## 컴퓨터가 3층집인 건 알죠?

운영체제는 S/W다. 일종의 platform이다. 가상화기술은 H/W를 S/W로 구현한 것이 가상화 기술이다.

운영체제는 MS Word와 같은 S/W다. 단, 차이는 user application 단의 process들을 support 한다. 즉, application process들이 잘 작동하도록 도와주는 것이다. 또 하나 다른 점은 H/W를 제어 및 관리한다. 대부분 범용 OS가 멀티 태스킹 즉, 멀티 프로세싱 시스템이다. 그리고 나쁜 프로세스들을 감지하여 나쁜 짓을 하지 못하게 막는 역할도 한다.

### H/W 용어 정리

운영체제를 이해하려면 알정수준의 하드웨어 이해가 필요하다. 그래서 먼저 가장 핵심적인 용어정리를 해보려고 한다.

Interrupt란 무엇일까? 한마디로 '벨 소리'이다.  내가 공부를 하는 중인데 현관 벨 소리가 들리면 하던 일을 중단하고 현관으로 가봐야 한다. Interrupt는 이와 유사하다. 내가 CPU라고 가정하고 나를 방해하는 요소가 있는데 그게 바로 Interrupt이다.

그러면 Interrupt는 언제 발생할까? 컴퓨터와 주변기기가 I/O(통신)하는데 그때마다 Interrupt가 발생한다. Interrupt가 발생하면 컴퓨터는 잠깐 멈추고 wait상태가 되었다가 다시 Interrupt가 오면 원래 하던 일을 진행한다. 일단 이렇게 알아두자.

### printf 함수 호출하는 과정

우리가 프로그래밍을 배웠다면 printf로 "Hello World!"를 찍어본 경험이 있을 것이다. 그러면 이 과정이 어떻게 일어날까? 한번 알아보자.

1.  process 내에 App에서 printf 함수(API) 호출(call)
2.  API 내부에서는 장치라는 것을 추상화한 file이라는 인터페이스를 통해서 정보가 내려간다.  
    정보가 내려갈때 프로세스가 권한이 있는지 없는지 체크를 한다.
3.  정보가 내려가면 환경이 kernel 영역으로 바뀌는데 이때 어느 새로운 코드가 실행이 된다. 이때 이 진입점의 있는 코드를 System call이라고 한다. 즉, printf는 System call의 write명령이고 이것이 작동되며 구성요소가 작동된다.
4.  이때 Device Driver로 내려가기 전에 filter라는 것이 있는데 여기서 V3 같은 프로세스에게 이 명령이 바이러스가 있는지 없는지 검사를 한다. 이상이 없다면 Device Driver 쪽으로 내려간다.
5.  이후에 Device Driver를 제어하기 시작한다.
6.  Device Driver가 제어가 되면 interrupt를 요청한다. 이때 나오는 말이 Interrupt Request (IRQ)이다.
7.  IRQ는 고유번호를 가지는데 (장치마다 다르다.) 그 번호를 가지고 요청하기 되면 Interrupt가 발생하면서 CPU는 잠시 멈추고 해당 장치와 통신을 하게 된다.
8.  해당장치와 연결 후 수행할 명령을 외부장치에 실행한다. 예로 모니터에 hello라는 글자를 렌더링 한다.
9.  할 일을 끝내면 Device Driver는 Interrupt를 보내면서 할 일 다 했다고 위로 요청을 한다. (kernel 구성요소에게)
10. API에서 process로 리턴이 된다.

결론적으로 이 프로세스가 1~10까지의 일련의 과정이 끝나서 흐름이 넘어올 때까지 wait를 하면 이 모든 I/O는 blocking I/O가 되는 거고 wait 하지 않고 다른 일을 하면 non-blocking I/O가 된다. 즉 blocking이냐 non-blocking이냐라는 것은 API를 호출한 쪽에서 자신의 상태가 어떻게 가느냐 그 차이이다.
