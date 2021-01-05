//원형큐

// 선형큐는 이해하기는 쉽지만 문제점이 있다. 즉, front와 rear의 값이
// 계속 증가만 하기 때문에 언젠가는 배열의 끝에 도달하게 되고 배열의 앞부분이 비어 있더라도
// 사용하지를 못한다는 점이다. 따라서 주기적으로 모든 요소들을 왼쪽으로 이동시켜야 한다. 예를
// 들어 큐는 삽입을 위한 공간을 만들기 위해서는 모든 요소들을 앞쪽으로 이동시켜야 한다. 이런
// 식으로 요소들을 이동시키면 해결을 되지만 매번 이동시키려면 상당한 시간이 걸리고 또한 프로그램
// 코딩이 복잡해진다.

// 이 문제는 배열을 선현으로 생각하지 말고 원형으로 생각하면 쉽게 해결된다. 즉, front와 rear의 값이 배열의
// 끝인 (MAX_QUEUE_SIZE - 1) 에 도달하면 다음에 증가되는 값은 0이 되도록 하는 것이다. 즉 다음과 같이 배열이
// 원형으로 처음과 끝이 연결되어 있다고 생각하는 것이다. 여기서 실제 배열이 원형으로 변화되는 것은 아니다. 그냥
// 개념상으로 원형으로 배열의 인덱스를 변화시켜주는 것 뿐이다.

// 원형큐에서는 front와 rear의 개념이 약간 변경된다. 먼저 초기값은 -1 이 아닌 0이다. 또 front 는 항상 큐의 첫 번째
// 요소의 하나 앞을 rear는 마지막 요소를 가리킨다.

// front와 rear값이 같으면 원형 큐가 비어 있음을 나타낸다. 원형큐에서는 하나의 자리는 항상 비워둔다. 왜냐하면 포화상태와
// 공백 상태를 구별하기 위해서이다. 따라서 만약 front == rear이면 공백상태가 되고 만약 front가 rear보다 하나 앞에 있으면
// 포화 상태가 된다. 만약 요소들의 개수를 저장하고 있는 추가적인 변수 count변수를 사용할 수 있다면 한자리를 비워두지
// 않아도 된다.

// 결론은 원형큐에서의 front는 첫 번째 요소 하나 앞을, rear는 마지막 요소를 가리킨다. 따라서 삽입을 할때는 rear를 무조건
// 먼저 하나 증가시키고 증가된 위치에 삽입을 하여야 하고, 삭제를 할 때도 먼저 front를 증가 시킨 다음, 그 위치에서 데이터를
// 꺼내 와야 한다.

#include<stdio.h>
#include<stdlib.h>

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

//=====원형큐 코드 끝=====

int main(void) {
    QueueType queue;
    int element;

    init_queue(&queue);
    printf("--데이터 추가 단계--\n");
    while(!is_full(&queue)){
        printf("정수를 입력하세요: ");
        scanf("%d", &element);
        enqueue(&queue, element);
        queue_print(&queue);
    }
    printf("큐는 포화상태 입니다.\n\n");

    printf("--데이터 삭제 단계--\n");
    while(!is_empty(&queue)) {
        element = dequeue(&queue);
        printf("꺼내진 정수: %d\n", element);
        queue_print(&queue);
    }
    printf("큐는 공백상태입니다.\n");
    return 0;
}
