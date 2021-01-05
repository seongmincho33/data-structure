//큐의 응용: 버퍼

// 큐는 어디에 사용될까? 큐는 서로 다른 속도로 실행되는 두 프로세스 간의 상호 작용을 조하시키는 
// 버퍼 역할을 담당한다. 예를 들면 CPU와 프린터 사이의 프린팅 버퍼, 또는 CPU와 키보드 사이의
// 키보드 버퍼 등이 이에 해당한다. 대개 데이터를 생산하는 생산자 프로세스가 있고 데이터를 소비하는 
// 소비자 프로세스가 있으며 이 사이에 큐로 구성되는 버퍼가 존재한다. 다음과 같은 분야가 큐의 대표적인 
// 응용분야 이다.

// -생산자 소비자 프로세스 : 큐를 버퍼로 사용한다.
// -교통 관리 시스템: 컴퓨터로 제어되는 신호등에서는 신호등을 순차적으로 제어하는데 원형큐가 사용된다.
// -CPU스케줄링: 운영체제는 실행 가능한 프로세스들을 저장하거나 이벤트를 기다리는 프로세스들을 저장하기
// 위하여 몇 개의 큐를 사용한다.

// 여기서 큐를 버퍼처럼 사용해본다. 큐에 일정한 비율(20%)로 난수를 생성하여 큐에 입력하고, 일정한 비율(10%)
// 로 큐에서 정수를 꺼내는 프로그램을 작성해 보자. 생산자가 소비자보다 빠르므로 큐가 포화 상태가 될 가능성이 높아진다.

#include<stdio.h>
#include<stdlib.h>

//queue2.c를 복사해넣는다.
//=====원형큐 코드 시작=====
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
}QueueType;

//오류 함수
void error(char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

//초기화 함수
void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

//공백 상태 검출 함수
int is_empty(QueueType* q) {
    return q->front == q->rear;
}

//포화 상태 검출 함수
int is_full(QueueType* q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

//원형큐 출력 함수
void queue_print(QueueType* q){
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
    if(!is_empty(q)){
        int i = q->front;
        do {
            i = (i + 1) % (MAX_QUEUE_SIZE);
            printf("%d | ", q->data[i]);
            if(i == q->rear) {
                break;
            }
        }while (i != q->front);
    }
    printf("\n");
}

//삽입 함수
void enqueue(QueueType* q, element item) {
    if(is_full(q)) {
        error("큐가 포화상태 입니다.");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

//삭제 함수
element dequeue(QueueType* q){
    if(is_empty(q)) {
        error("큐가 공백상태입니다.");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

//보기 함수
element peek(QueueType* q) {
    if(is_empty(q)) {
        error("큐가 공백상태입니다.");
    }
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}


//=====원형큐 코드 종료=====

int main(void) {
    QueueType queue;
    int element;

    init_queue(&queue);
    srand(time(NULL));

    for(int i = 0; i<100; i++) {
        if(rand() % 5 == 0) {
            enqueue(&queue, rand() % 100);
        }
        queue_print(&queue);
        if(rand() % 10 == 0) {
            int data = dequeue(&queue);
        }
        queue_print(&queue);
    }
    return 0;
}