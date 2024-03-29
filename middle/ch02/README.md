> 이 포스트는 [감자님 강의](https://www.inflearn.com/course/%EB%B9%84%EC%A0%84%EA%B3%B5%EC%9E%90-%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C/dashboard '인프런 강의')를 기반으로 작성되었습니다.

## CPU 스케줄링 개요

컴퓨터의 자원은 다음과 같다. CPU와 메모리 같은 필수장치와 하드디스크, 키보드, 마우스와 같은 주변장치가 있다. 이번시간부터 필수장치인 CPU에 대해 알아보자. 프로그램을 실행시키면 메모리에 프로세스가 생성되고 각 프로세스에는 1개 이상의 쓰레드가 존재한다. 프로세스들은 CPU를 할당/해제하는데 이를 CPU 스케줄링이라고 한다.

CPU 스케줄링에서 스케줄러(운영체제)가 고려해야 할 사항은 2가지이다. 첫째, "어떤 프로세스에게 CPU 리소스를 줘야하는가?"이다. 메모리에는 수많은 프로세스들이 있는데 여기서 "어떤 프로세스에게 CPU 사용권을 줘야 하는가?" 하는 문제이다. 한 프로세스에게만 계속 할당하면 다른 프로세스들이 불만을 제기할 것이다. 둘째, "CPU를 할당받은 프로세스가 얼마의 시간 동안 CPU를 사용해야 하는가?"이다. 오늘날은 시분할 처리방식으로 여러 프로세스에게 짧은 시간 동안 돌아가면서 CPU를 할당한다. 예를 들어 프로세스 A에게 1초 동안 CPU 이용권을 주고 1초가 지나면 CPU를 뺏어서 프로세스 B에게 1초 동안 CPU 이용권을 주는 방식이다. 지금 말한 이 2가지 고려사항이 컴퓨터 성능에 굉장히 큰 영향을 끼친다.

> CPU를 할당받아 실행하는 작업을 CPU Burst, 입출력 작업을 I/O Burst라고 한다.

> 이 포스트는 [감자님 강의](https://www.inflearn.com/course/%EB%B9%84%EC%A0%84%EA%B3%B5%EC%9E%90-%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C/dashboard '인프런 강의')를 기반으로 작성되었습니다.

## 다중 큐

이전에 배웠던 프로세스 상태를 다시 살펴보겠다. 프로세스가 생성되면 준비상태로 전환되고 준비상태에서 CPU를 기다리고 있는 프로세스들은 CPU 스케줄러에 의해 실행상태로 전환된다. 실행상태에 있는 프로세스는 CPU 할당시간이 다 되면 다시 준비상태로 전환되고 입출력 요청이 있다면 대기상태로, 작업이 완료되었다면 완료상태로 전환된다. 여기서 프로세스가 대기하고 있는 준비상태와 대기상태는 큐라는 자료구조로 관리된다. 큐 자료구조는 우리가 마트 계산대에 줄을 서는 것과 같이 먼저 온 사람이 가장 먼저 처리를 받고 나중에 온 사람은 나중에 처리를 받는 구조이다. 먼저 들어온 게 나중에 처리받고 나중에 들어온 게 먼저 처리받는 스택이랑 상반된 구조이다.

프로세스가 실행상태에서 준비상태로 돌아갈 때 운영체제는 해당 프로세스의 우선순위를 보고 그에 맞는 "준비 큐"에 넣는다. CPU 스케줄러는 "준비상태의 다중 큐"에 들어있는 프로세스들 중에 적당한 프로세스를 선택해서 실행상태로 전환시킨다. 프로세스가 실행상태에서 입출력 요청을 받아 대기상태로 오면 입출력 요청에 따라서 분류 된 큐에 들어가게 된다. 예를 들면, HDD 작업은 "HDD 큐"에 넣고 HDD 작업이 완료되어 인터럽트가 날아가면 HDD 큐를 뒤져서 다시 꺼내갑니다. 지금까지 큐에 프로세스가 들어간다고 했는데 정확히는 프로세스의 정보를 가지는 PCB가 들어가 있다.

정리를 해보겠다. 프로세스 정보를 담고 있는 PCB는 준비상태의 다중 큐에 들어가서 실행되기를 기다리고 있고 CPU 스케줄러에 의해 실행상태로 전환된다. 이 때 CPU 스케줄러는 준비상태의 다중 큐를 참조해서 어떤 프로세스를 실행시킬지 결정을 한다. 입출력 작업도 비슷하다. 실행 중인 프로세스에게 입출력 작업이 발생하면 해당 입출력 작업의 종류 별로 나뉜 큐에 들어가고 CPU 스케줄러는 이를 참조해서 스케줄링한다.

> 이 포스트는 [감자님 강의](https://www.inflearn.com/course/%EB%B9%84%EC%A0%84%EA%B3%B5%EC%9E%90-%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C/dashboard '인프런 강의')를 기반으로 작성되었습니다.

## 스케줄링 목표

스케줄링 목표는 여러가지가 존재한다. 첫째, **리소스 사용률**이다. CPU 사용률을 높이는 것을 목표로 할 수도 있고 I/O 디바이스의 사용률을 높이는 것을 목표로 할 수 있다. 둘째, **오버헤드 최소화**이다. 스케줄링을 하기 위한 계산이 너무 복잡하거나 컨텍스트 스위칭을 너무 자주 하면 배보다 배꼽이 더 커지는 상황이 나온다. 스케줄러는 이런 오버헤드를 최소화하는 것을 목표로 한다. 셋째, **공평성**이다. 모든 프로세스에게 공평하게 CPU가 할당되어야 한다. 특정 프로세스에게만 CPU가 계속 할당된다면 불공평할 것이다. 여기서 공평의 의미는 시스템에 따라 달라질 수 있다. 예를 들어 자율주행 자동차에 사용되는 운영체제를 생각해 보면 안전의 이유로 장애물을 인지하고 피하는 프로세스가 가장 중요할 것이다. 그에 비해 음악을 재생하거나 실내 온도 유지 기능은 상대적으로 덜 중요할 것이다. 이 운영체제는 장애물을 인지하고 피하는 프로세스에게 CPU가 많이 할당되는 것이 공평하다. 이와 같은 특수한 경우가 아니라면 모든 프로세스에게 CPU는 골고루 할당되어야 한다. 넷째 **처리량**이다. 같은 시간 내에 더 많은 처리를 할 수 있는 방법을 목표로 한다. 다섯째, **대기시간**이다. 작업을 요청하고 실제 작업이 이루어지기 전까지 대기하는 시간이 짧은 것을 목표로 한다. 여섯째, **응답시간**이다. 대화형 시스템에서 사용자의 요청이 얼마나 빨리 반응하는지가 중요하기 때문에 응답시간이 짧은 것을 목표로 한다.

지금 말한 목표들은 모두 최고의 수준으로 유지하기 힘들다. 그 이유는 목표 간에 서로 상반되는 상황이 있기 때문이다. 예를 들면 처리량을 높이기 위해서는 하나의 프로세스에 CPU를 오래 할당해야 한다. 반면, 응답시간을 줄이기 위해서 여러 프로세스에 골고루 CPU를 할당해야 하는데 이는 서로 상반되기 때문에 처리량과 응답시간의 목표를 같이 달성할 수 없다. 이 때는 사용자가 사용하는 시스템에 따라서 목표를 달리 설정해야 한다. 터치스크린과 같이 사용자에게 빠른 응답이 필요한 경우는 응답시간이 짧도록 초점을 맞추고, 과학계산 같은 경우는 처리량이 높도록 초점을 맞춰야 한다. 일반 사용자의 경우 특별한 목적이 없다면 어느 한쪽에 치우치지 않도록 밸런스를 유지하는 게 중요하다.

> 이 포스트는 [감자님 강의](https://www.inflearn.com/course/%EB%B9%84%EC%A0%84%EA%B3%B5%EC%9E%90-%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C/dashboard '인프런 강의')를 기반으로 작성되었습니다.

## FIFO

이번 포스트부터 여러 종류의 CPU 스케줄링 알고리즘을 알아보겠다. 운영체제 설계자들이 생각하는 스케줄링은 처음부터 대단하지 않았다. 우리가 쉽게 생각할 수 있는 것과 크게 다르지 않았다. 가장 먼저 알아볼 알고리즘은 FIFO 알고리즘으로 'First In First Out'의 약자이다. 먼저 들어온 작업이 먼저 나간다는 뜻으로 스케줄링 큐에 들어온 순서대로 CPU를 할당받는 방식이다. 이 방식은 먼저 들어온 프로세스가 완전히 끝나야만 다음 프로세스가 실행된다는 점을 가지고 있다.

마트의 계산대를 생각하면 이해가 쉽다. 카운터에 계산원이 있고 손님들은 장을 보고 카운터 앞에 줄을 선다. 계산원은 먼저 온 손님을 먼저 계산해주는데 이 방식을 FIFO라고 부른다. FIFO 알고리즘의 장점은 단순하고 직관적이라는 것이다. 반대로 단점은 한 프로세스가 완전히 끝나야 다음 프로세스가 시작되기 때문에 실행시간이 짧고 늦게 도착한 프로세스가 실행시간이 길고 빨리 도착한 프로세스의 작업을 기다려야 한다는 것이다. 또한 I/O 작업이 있다고 한다면 CPU는 I/O 작업이 끝날 때까지 쉬고 있기 때문에 CPU 사용률이 떨어진다.

FIFO 알고리즘의 단점을 마트의 예로 확인해보자. 첫 번째 단점으로 실행시간이 길고 일찍 도착한 프로세스와 실행시간이 짧고 늦게 도착한 프로세스의 예이다. 물건 100만 원을 산 손님이 계산대에 먼저 도착했다. 이어서 물건 1000원을 산 손님이 이후에 도착했다고 하자. 현실에서는 첫 손님의 계산시간이 길기 때문에 양해를 구하고 1000원의 물건들을 산 손님부터 계산을 할 수 있다. 하지만 FIFO 알고리즘은 예외 없이 도착한 순서로만 실행순서가 결정되기 때문에 1000원의 물건을 사서 빨리 계산을 마칠 수 있더라도 먼저 온 사람의 계산을 마쳐야 한다는 단점이 있다. 두 번째 단점을 마트의 예로 확인해 보자. 두 번째 단점은 I/O 작업이 있다면 I/O 작업이 끝날 때까지 CPU가 쉬게 되어서 CPU 사용률을 떨어트린다는 점이다. 여기서 I/O 작업은 손님이 지갑을 뒤지는 작업으로 CPU를 계산원이라고 비유하자. 계산원이 손님의 물건을 확인하고 돈을 받으려 한다. 손님은 지갑을 열어 돈을 꺼낸다.(I/O 작업) 동전도 섞여 있어서 시간이 5분 정도 걸렸다. 계산원은 다음 손님의 계산을 도와주지 못하고 기다리기만 해야 한다. 드디어 손님이 돈을 꺼내서 계산이 완료되었다. 이후 1000원의 물건을 산 다음 손님은 굉장히 오래 기다렸다.

스케줄링의 성능은 "평균 대기 시간"으로 평가한다. 평균 대기 시간은 프로세스 여러개 실행될 때 이 프로세스들 모두 실행되기까지 걸리는 대기시간의 평균이다.

| 프로세스       | 프로세스1 | 프로세스2 | 프로세스3 |
| -------------- | --------- | --------- | --------- |
| CPU Burst Time | 25초      | 5초       | 4초       |

위의 표처럼 각 프로세스의 CPU Burst Time이 주어졌다고 하자. 그러면 대기시간은 프로세스 1은 0초, 프로세스 2는 25초, 프로세스 3은 30초로 평균 대기 시간을 구하면 (0 + 25 + 30) / 3 = 18.3초가 나온다. 만약 짧은 순으로 대기시간을 구하면 프로세스 3은 0초, 프로세스 2는 4초, 프로세스 1은 9초로 평균 대기 시간을 구하면 4.3초가 나온다. 프로세스 실행순서만 바꿨는데 평균 대기 시간의 차이가 많이 난다. FIFO 알고리즘은 프로세스의 Burst Time에 따라 성능에 차이가 심하게 나기 때문에 현대 운영체제에서는 잘 사용하지 않고 일괄 처리 시스템에 많이 사용한다.

> 이 포스트는 [감자님 강의](https://www.inflearn.com/course/%EB%B9%84%EC%A0%84%EA%B3%B5%EC%9E%90-%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C/dashboard '인프런 강의')를 기반으로 작성되었습니다.

## SJF

이전 포스트에서 배운 FIFO는 작업의 순서에 따라 평균 대기 시간이 크게 달라질 수 있다고 했다. 운영체제를 연구하던 사람들은 여기서 아이디어를 얻었다. FIFO에서 Burst Time이 짧은 프로세스를 먼저 실행했을 때 평균 대기 시간이 짧아졌다. 그럼 Burst Time이 짧은 프로세스를 먼저 실행하는 알고리즘을 만들기로 하고 SJF라는 이름을 붙였다. 한글로 해석하면 "짧은 작업 먼저"라는 뜻이다. SJF는 이론적으로 FIFO보다 성능이 더 좋다. 하지만 실제로 구현하려고 하니 문제가 발생하였다.

문제는 크게 2가지였다. 첫번째 어떤 프로세스가 얼마나 실행될지 예측하기 힘들었다. 우리가 브라우저를 실행시키고 뮤직 플레이어를 실행시켰다고 하자. 노래를 틀고 브라우저에 날씨만 확인하고 브라우저를 종료시킬 수 있고 게임을 하느라 계속 켜둘 수 있다. 이처럼 프로세스의 종료시간은 예측하기 거의 불가능에 가깝다. 둘째 Burst Time이 긴 프로세스는 아주 오랫동안 실행되지 않을 수 있다는 것이다. SJF는 Burst Time이 짧은 프로세스가 먼저 실행되기 때문에 Burst Time이 긴 프로세스는 뒤로 계속 밀려난다. 만약 Burst Time이 짧은 프로세스가 중간에 계속 들어오면 Burst Time이 긴 프로세스는 앞에 모든 프로세스가 종료되기 전까지 기다려야 하기 때문에 굉장히 불공평하다고 느낄 것이다. 이러한 문제점 때문에 SJF 알고리즘은 사용을 못한다.

> 이 포스트는 [감자님 강의](https://www.inflearn.com/course/%EB%B9%84%EC%A0%84%EA%B3%B5%EC%9E%90-%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C/dashboard '인프런 강의')를 기반으로 작성되었습니다.

## RR

운영체제를 연구하는 사람들은 생각을 하였다. FIFO 알고리즘은 일괄처리 시스템에 적절해서 시분할 처리 시스템에는 사용하기 힘들고 SJf 알고리즘은 프로세스의 종료시간을 예측하기가 힘들다. 그래서 사람들은 고민하였다. 나온 결론은 가장 단순한 FIFO 알고리즘의 단점을 해결하기로 하였다. FIFO 알고리즘의 단점은 먼저 들어온 프로세스가 전부 끝나야 다음 프로세스가 실행된다는 점이었다. 이 문제를 해결하기 위해 한 프로세스에게 일정시간만큼 CPU를 할당하고 할당된 시간이 지나면 강제로 다른 프로세스에게 일정시간만큼 CPU를 할당한다. 강제로 뺏긴 프로세스는 큐의 가장 뒷부분으로 밀려난다. 이 알고리즘을 RR이라고 부른다. 프로세스에게 할당하는 일정시간은 "타임 슬라이스" 혹은 "타임 퀀텀"이라고 부른다.

그럼 RR 알고리즘의 성능을 살펴보자. 타임슬라이스가 10초인 시스템이라거 가정하고 평균 대기 시간을 구해보자.

| 프로세스   | p1   | p2  | p3   |
| ---------- | ---- | --- | ---- |
| Burst Time | 25초 | 4초 | 10초 |

위의 표대로 각 프로세스들의 Burst Time은 위와 같고 이 프로세스들은 동시에 큐에 들어왔고 실행순서는 p1 -> p2 -> p3라고 가정하자. p1은 큐에 들어오자마자 실행되기 때문에 대기시간은 0초이다. p1은 타임슬라이스 10초만큼 실행하고 시간을 초과해 p2에게 CPU를 뺏기고 p1의 남은 작업은 큐의 가장 뒤로 이동한다.

| 프로세스   | p2  | p3   | p1   |
| ---------- | --- | ---- | ---- |
| Burst Time | 4초 | 10초 | 15초 |

p2는 p1이 실행하는 10초를 기다렸기 때문에 대기시간은 10초이다. p2는 Burst Time이 4초이기 때문에 4초가 지나면 p3에게 양보하고 작업을 마친다.

| 프로세스   | p3   | p1   |
| ---------- | ---- | ---- |
| Burst Time | 10초 | 15초 |

p3는 p1과 p2의 실행이 완료될 때까지 14초를 기다렸다. p3의 대기시간은 14초이다. p3는 Burst Time인 10초 동안 실행하고 작업을 마친다.

| 프로세스   | p1   |
| ---------- | ---- |
| Burst Time | 15초 |

다음으로 p1이 다시 실행되는데 p1은 p2와 p3의 실행 완료까지 14초가 걸렸으니 대기시간은 14초이다. p1의 Burst Time이 15초로 타임 슬라이스보다 크기 때문에 타임 슬라이스 값인 10초만 실행한다.

| 프로세스   | p1  |
| ---------- | --- |
| Burst Time | 5초 |

그리고 Burst Time이 5초인 p1이 큐에 마지막으로 이동하는데 대기중인 프로세스가 없으므로 대기시간은 0초로 바로 실행된다. 이제 평균 대기 시간을 구하면 다음과 같다. (0 + 10 + 14 + 14 + 0) / 3 = 12.67초가 나온다. 이 프로세스들을 FIFO 알고리즘으로 해보면 18초가 나온다. 이 경우는 RR 알고리즘이 더 빠르다. 다른 상황에서는 FIFO 알고리즘과 RR 알고리즘의 평균대기시간이 비슷 할 수 있다. 평균대기시간이 비슷하다면 RR 알고리즘이 더 비효율적인 방식이다. RR 알고리즘은 컨텍스트 스위칭이 있기 때문에 컨텍스트 스위칭 시간이 더 추가되기 때문이다.

RR 알고리즘의 성능은 타임슬라이스의 값에 따라 크게 달라진다. 2가지 상황으로 알아보자. 먼저 타임슬라이스가 큰 경우부터 살펴보자. 이론적으로 타임슬라이스의 값이 무한대라고 가정하면 먼저 들어온 프로세스의 작업이 종료될 때까지 실행하니 FIFO 알고리즘이 되어버린다. 그러면 타임슬라이스를 조금 낮추어 5초 정도라고 한다면 어떻게 될까? 웹 브라우저와 뮤직 플레이어를 동시에 실행시켰다고 해보자. 타임슬라이스가 5초이면 웹 브라우저 5초 실행하고 뮤직플레이어 5초 실행하고... 이렇게 반복하면 사용자는 너무 끊긴다라는 불만을 토로할 것이다. 이제 타임슬라이스가 작은 경우를 보자. 타임슬라이스를 1ms로 아주 작은 값을 설정하면 웹 브라우저와 뮤직 플레이어가 동시에 동작하는 것처럼 보일 것이다. 하지만 타임슬라이스를 이렇게 너무 작게 하면 컨텍스트 스위칭이 너무 자주 발생하여 타임슬라이스에서 실행되는 프로세스의 처리량보다 컨텍스트 스위칭을 처리하는 양이 훨씬 커져서 배보다 배꼽이 더 큰 상황이 발생할 것이다. 이런 상황을 "오버헤드가 너무 크다"라고 말한다.

최적의 타임슬라이스를 결정하는 방법은 사용자가 느끼기에 여러 프로세스가 버벅거리지 않고 동시에 실행되는 것처럼 느겨지면서 오버헤드가 너무 크지 않는 값으로 찾아야 한다. 실제로 윈도우 운영체제는 타임슬라이스를 20ms로, 유닉스는 100ms로 설정한다.

> 이 포스트는 [감자님 강의](https://www.inflearn.com/course/%EB%B9%84%EC%A0%84%EA%B3%B5%EC%9E%90-%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C/dashboard '인프런 강의')를 기반으로 작성되었습니다.

## MLFQ

이번 포스트에서는 오늘날 운영체제에서 가장 일반적으로 쓰이는 CPU 스케줄링 기법인 MLFQ에 대해 알아보자. 먼저 어떻게 MLFQ가 탄생 했는지 알아보자. MLFQ는 RR의 업그레이드된 알고리즘이기 때문에 RR 알고리즘의 예로 알아보자.

프로세스 2개가 있다고 하자. 첫번째 프로세스를 p1, 두 번째 프로세스를 p2라고 하자. p1은 I/O 작업 없이 CPU 연산만 하는 프로세스이다. p2는 1초 CPU 연산을 하고 10초 동안 I/O작업을 한다. 여기서 p1은 대부분의 시간을 CPU 연산을 하기 때문에 CPU Bound Process라고 한다. 반면에 p2는 대부분의 시간을 I/O작업으로 보내고 CPU 연산은 조금 하기 때문에 I/O Bound Process라고 한다. CPU Bound Process가 가장 중요하게 생각하는 것은 CPU 사용률과 처리량이다. 반면 I/O Bound Process가 가장 중요하게 생각하는 것은 응답속도이다. 키보드나 마우스 입력을 했는데 반응이 늦으면 사용자가 많이 답답해할 것이다.

이제 이 2개의 프로세스를 가지고 2가지 상황에서 실행해보자. 첫 번째 상황은 타입슬라이스가 100초인 경우이다. 먼저 p2가 실행되었다고 하자. p2는 1초 실행되고 I/O 작업을 요청하고 기다릴 것이다. 이제 p1이 싱행되는데 타임슬라이스 크기인 100초만큼 실행하는데 p1이 실행하는 도중에 10초가 지났을 때 p2가 요청한 I/O 작업이 완료되고 인터럽트가 발생한다. 그럼 p2는 다시 큐에 들어가 CPU를 할당받을 준비를 한다. p1은 100초 실행되면 CPU를 뺏기고 큐에 있던 p2는 다시 1초 실행되고 I/O 작업을 요청하고 다시 기다린다. 이 과정이 모든 작업이 완료될 때까지 계속 반복된다.  이제 2번째 상황을 살펴보자. 2번째 상황은 타입슬라이스가 1초인 경우이다. p2가 1초 실행되고 I/O 작업을 요청한다. 이제 p1이 실행되는데 타임슬라이스 크기인 1초만큼 실행한다. 지금 p2는 I/O 작업이 끝나지 않아서 계속 기다리는 상황이다. 그렇가 때문에 p1은 종료되고 바로 큐에 들어가는데 큐가 비어있기 때문에 p1이 다시 바로 실행한다. 이렇게 p1이 10번 즉, 10초 동안 실행되면 p2의 I/O 작업이 끝나서 인터럽트가 발생하고 p2는 큐에 들어간다. 그럼 p2는 다시 1초 실행되고 다시 I/O 작업을 기다린다. 지금 설명한 데로 모든 작업이 완료될 때까지 계속 반복한다.

이제 2가지 상황을 비교해보자. 첫 번째 상황의 경우 CPU 사용률을 보면 CPU는 쉬지 않고 일하기 때문에 CPU 사용률은 100%이다. 하지만 I/O 사용률을 보면 p1이 실행되는 동안 p2의 I/O 작업이 완료된 시점부터 기다리는 시간이 발생하기 때문에 약 10% 정도밖에 안된다. 2번째 상황도 CPU 사용률은 100%이다. I/O 사용률은 p1의 타입슬라이스가 작기 때문에 p2가 첫 번째 상황처럼 기다리면 낭비되는 시간이 거의 없고 약 90%가 나온다. 타임슬라이스가 100초에서 1초로 작아질 때 p1과 p2의 입장에서 한쪽은 손해를 보고 한쪽은 이득을 취하는 구조가 나온다. CPU Bound Process인 p1은 100초였던 실행시간이 1초로 줄었지만 연속적으로 실행되기 때문에 손해가 없는 것처럼 보인다. 하지만 컨텍스트 스위칭을 하기 때문에 손해가 없는 것처럼 보인다. 하지만 컨텍스트 스위칭을 하기 때문에 오버헤드가 생겨서 손해를 본다. 반면 I/O Bound Process인 p2는 I/O 사용률이 굉장히 높아졌기 때문에 이득을 봤다. 운영체제를 연구하는 사람들은 손해를 보는 프로세스가 어떻게 하면 손해를 보지 않을지 고민을 하였고 바로 여기서 MLFQ가 탄생하였다.

MLFQ는 기본적으로 CPU 사용률과 I/O 사용률이 좋게 나오는 작은 크기의 타임슬라이스 선택을 한다. 그리고 p1과 같은 CPU Bound Process들에게는 타임슬라이스를 크게 주는 것이다. 그럼 운영체제 입장에서 CPU Bound Process와 I/O Bound Process를 어떻게 구분할까?

간단하다! CPU를 사용하는 프로세스가 실행하다가 스스로 CPU를 반납하면 CPU 사용률이 적은거니 I/O Bound Process일 확률이 높다. 반대로 CPU를 사용하는 프로세스가 타임슬라이스 크기를 오버해서 CPU 스케줄러에 의해 강제로 CPU를 뺏기는 상황이면 CPU 사용이 많은 거니 CPU Bound Process일 확률이 높다. 이러한 아이디어를 통해 우선순위를 가진 큐를 여러 개 준비한다. 우선순위가 높으면 타임슬라이스가 작고 우선순위가 낮을수록 타임슬라이스 값이 커진다. 만약 p1처럼 타임슬라이스 크기를 오버해서 CPU를 강제로 뺏긴다면 p1은 원래 있던 큐보다 낮은 큐로 이동한다. 그러면 다음번에 실행될 때 타임슬라이스가 조금 더 커지게 되고 여기서도 부족하면 다음에 더 큰 타임슬라이스를 할당한다. 최종적으로 타임슬라이스가 무한초에 가깝게 할당될 때 FIFO처럼 실행되어서 연속적으로 작업을 마칠 수 있다.
