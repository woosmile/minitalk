# minitalk

- Client 프로그램으로 Server 프로그램에 문자열을 전송하는 과제
- Server 프로그램은 Client 프로그램으로부터 문자를 계속 받을 수 있는 상태여야 함 (문자열을 한번 수신받고 종료되는 것이 아니라 계속해서 대기상태로 있어야 함)

## 학습 내용

- 비트 연산 및 쉬프트 연산자에 대한 개념
- signal.h 에 있는 함수의 사용방법, 시그널이 처리되는 과정
- 시그널의 종류
  ![Untitled](https://github.com/user-attachments/assets/399517f0-f296-4a03-baad-ecb80e4c67f7)
  
## 함수 설명 (Mandatory Part : Client)

### int	main(int ac, char *av[])

- PID의 예외처리로 100이하, 99999이상 PID는 유효하지 않은 것으로 간주 (100 이하는 시스템에서 사용 중이고 99999이상 PID는 존재하지 않기 때문)

### void	send_bit(pid_t pid, char *str)

- 문자 1개씩 전송하므로 char 기준 1바이트 즉, 8비트 단위로 전송함
- 쉬프트 연산자와 비트 연산을 활용하여 8비트 중 맨 앞의 비트(MSB)부터 차례대로 전송
- 비트를 우측 쉬프트 시킨 후 & 1 연산을 통해 비트를 마스킹함 (쉬프트 연산의 결과 값이 0이면 0 그대로, 1이면 1 그대로 처리됨)
- 마스킹 된 비트의 결과에 따라서 kill(PID, SIGNAL) 함수를 통해 SIGUSR1, SIGUSR2 시그널을 보냄
- SIGUSR1 = 0, SIGUSR2= 1 의미하도록 지정함
- 비트 전송 간격을 150us 정도의 딜레이를 주어서 서버에서 처리할 시간을 충분히 부여함 (서버에서 아직 처리가 완료되지 않았는데 클라이언트에서 빠른 속도로 비트를 보내면 문자 전송에 문제가 됨)

## 함수 설명 (Mandatory : Server)

### int	main(void)

- server 실행 시 getpid 함수를 통해 PID 확인 및 출력
- signal(처리할 시그널, 불러올 함수) 함수를 통해 SIGUSR1, SIGUSR2 신호가 들어오면 특정 함수를 실행함
- pause를 통해 신호 대기

### void	process_signal(int signo)

- SIGUSR1(1), SIGUSR2(0) 신호가 들어올때 마다 비트 연산 진행
- LSB 부터 비트를 하나씩 변수에 저장함. 이 때 변수는 서버 프로그램이 종료될 때 까지 값을 기억하고 있어야 하므로 static으로 선언 (비트의 자리를 의미하는 인덱스 변수도 마찬가지)
- OR 연산을 통해 SIGUSR1인 경우 | 1, SIGUSR2인 경우 | 0 로 비트 마스킹
- 인덱스가 8이 되었다는 것은 문자 하나의 전송이 끝났으므로 비트 8개가 저장된 char 변수를 %c로 출력하고 word, idx를 0으로 초기화하여 다음 문자를 받을 준비

## Bonus Part

- 유니코드 문자열에 대한 개념 설명이 추가됨
    
    <aside>
    💡 [https://jeongdowon.medium.com/unicode와-utf-8-간단히-이해하기-b6aa3f7edf96](https://jeongdowon.medium.com/unicode%EC%99%80-utf-8-%EA%B0%84%EB%8B%A8%ED%9E%88-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0-b6aa3f7edf96)
    
    </aside>
    
- server에서 client로 전송을 잘 받았다는 신호를 전달 해야함.
- 따라서 server에서 client의 pid를 얻는 과정이 추가 됨
- sigaction 구조체의 사용
    
    <aside>
    💡 https://www.joinc.co.kr/w/man/2/sigaction
    
    </aside>
    
    <aside>
    💡 [https://badayak.com/entry/C언어-시그널-처리-함수-sigaction](https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%B2%98%EB%A6%AC-%ED%95%A8%EC%88%98-sigaction)
    
    </aside>
    

![Screen Shot 2023-03-02 at 6.24.38 PM.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/8a259bce-44da-4663-ac39-b39be4550907/Screen_Shot_2023-03-02_at_6.24.38_PM.png)

- sa_handler, sa_sigaction : 시그널 처리 핸들러
- sa_flags : 시그널 처리 과정을 어떻게 변화시킬 것인지 결정하는 변수
    
    ![Screen Shot 2023-03-02 at 5.55.31 PM.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/c14cacea-2ef5-48dd-9f77-f5979b00ab60/Screen_Shot_2023-03-02_at_5.55.31_PM.png)
    
- server에서 client의 pid를 알기 위해서는 sa_sigaction 포인터 함수의 siginfo_t 구조체를 사용해야 함. (sa_flags를 SA_SIGINFO로 지정해야 sa_handler 대신 sa_sigaction를 사용할 수 있음)
- sa_sigaction 포인터 함수의 매개변수
    - int signo : 시그널 핸들러를 호출하는 시그널
    - siginfo_t *siginfo : 시그널을 발생한 측의 정보
        
        ![Screen Shot 2023-03-09 at 1.28.05 PM.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/07a07f4f-65a2-44a1-98e2-685ba3220238/Screen_Shot_2023-03-09_at_1.28.05_PM.png)
        
    - void *context : 시그널을 받는 측의 내부 상태
- **시그널 핸들러 함수는 sa_sigaction 포인터 함수의 매개변수와 동일해야 함 (이로 인해서 sigaction 구조체를 매개변수로 추가할 수 없기에 전역변수로 선언해야 함)**
- sa_mask : 시그널 핸들러가 동작 중일 때 차단할 시그널 집합
- sigemptyset 함수를 통해 sa_mask 구조체 변수의 시그널들을 모두 비움 (시그널 블로킹 안함)
- 위와 같이 설정한 sigaction 구조체를 적용시키기 위해 sigaction 함수를 호출함
    
    ![Screen Shot 2023-03-02 at 6.28.07 PM.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/dbc54e9e-d425-469b-a875-83b692c39ae7/Screen_Shot_2023-03-02_at_6.28.07_PM.png)
    
    - int signum : 수신받은 시그널
    - *act : 시그널 발생 시 시그널 처리와 관련되어 설정한 sigaction 구조체
    - *oldact : 이전에 설정한 sigaction 구조체
- SIGUSR1 : Bit 1 / Connection Start
- SIGUSR2 : Bit 0 / Connection End

## 함수 설명 (Bonus : Common)

### void	initial_signal_handler(t_sig *sig, pid_t pid, char *str, void (*func)(int, siginfo_t *, void *))

- sigaction 구조체를 설정하고 signal handler를 지정하는 함수
- t_sig 구조체는 안에 pid, str, 그리고 sigaction 구조체를 의미하는 sigact 구조체를 가지고 있음
- sigaction 함수를 통해 SIGUSR1, SIGUSR2 신호가 들어왔을 시 설정한 sigaction 구조체를 불러오게 함

## 함수 설명 (Bonus : Client)

### int	main(int ac, char *av[])

- sigaction 구조체를 설정하고 서버로부터 시그널을 받으면 호출되는 함수로 connection_start를 지정함
- 연결 확인을 위해 서버에 SIGUSR1을 kill 함수로 보낸 후 서버의 응답을 pause()로 대기
- 위 과정에서 서버에서 응답이 없을 경우 while(1) 문으로 2초간 SIGUSR1 신호를 보내는 로직을 추가함 (다중 클라이언트 사용 시, 앞선 클라이언트의 문자열을 처리하고 있으면 현재 클라이언트의 신호를 무시하게 되지만 이렇게 추가하면 앞선 클라이언트의 처리가 끝난 후 대기상태에 있던 클라이언트의 처리가 이루어짐)

### void	send_bit(pid_t pid, char *str)

- 비트를 보내는 과정은 동일함
- 다만 마지막 문자를 보낸 다음에 0을 의미하는 00000000 비트를 보내서 전송할 문자가 더이상 없다는 것을 추가로 전달함 (서버에서 수신 완료에 대한 처리를 하기 위해)

### void	connection_start(int signo, siginfo_t *siginfo, void *context)

- 서버로부터 SIGUSR1을 수신받으면 이 함수가 불러와짐
- server와의 연결에 성공했다는 문자열을 출력
- 다음에 실행될 함수로 connection_end를 지정
- 연결에 성공했으니 send_bit 함수를 호출함
- pause로 수신 성공 시그널 대기

### void	connection_end(int signo, siginfo_t *siginfo, void *context)

- 수신에 성공했다는 의미를 가지는 SIGUSR2가 들어오면 실행되는 함수
- SIGUSR2가 정상적으로 수신되었는지 확인하고 해당 메세지를 출력

## 함수 설명 (Bonus : Server)

### int	main(void)

- sigaction 구조체 설정 및 신호가 들어오면 불러와질 함수로 connecion_start를 지정

### void	connection_start(int signo, siginfo_t *siginfo, void *context)

- SIGUSR1이 수신되면 클라이언트와의 연결이 성공했다는 메세지를 출력함
- siginfo 구조체를 통해 클라이언트 pid 출력
- SIGUSR1 신호를 클라이언트로 보냄
- 다음 신호를 통해 불러와질 함수로 process_bit_signal를 지정함

### void	process_bit_signal(int signo, siginfo_t *siginfo, void *context);

- 클라이언트의 문자열을 처리하고 있는 중에 다른 클라이언트에서 시그널을 보내오면 siginfo_t 구조체에서 pid값을 대조하여 다르면 무시하는 조건문을 추가함 (문자열 출력 깨짐 방지)
- 전송받은 문자의 최종 값이 0이면 문자열 전송이 끝났다는 것으로 간주함
- 문자열 전송이 끝나서 클라이언트에 0에 해당하는 신호가 수신되면 connection_end 함수 호출

### void	connection_end(void)

- 비트를 다 전달받았으면 호출됨
- 다음에 불러와질 함수로 connection_start를 지정함
- 수신 완료 및 다음 비트를 받을 준비가 되었다는 신호로 SIGUSR2를 클라이언트로 전송함
