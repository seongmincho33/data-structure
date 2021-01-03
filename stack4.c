//동적 배열 스택 프로그램
//앞에서는 모두 컴파일 시간에 크기가 결정되는 1차원 배열을 사용하였다. 따라서 컴파일
//시간에 필요한 스택의 크기를 알아야 하는데 실제로는 아주 어렵다. 
//C언어에서는 malloc()을 호출하여서 실행 시간에 메모리를 할당 받을 수 있다. 이 기능을
//사용하면 필요할 때마다 스택의 크기를 동적으로 늘릴 수 있다. 다음은 동적 메모리 할당을 이용하는 스택 코드이다.
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
    element *data;  //data는 포인터로 정의된다.
    int capacity;   //현재 크기
    int top;
} StackType;

//스택 생성 함수
void init_stack(StackType *s) {
    s->top = -1;
    s->capacity = 1;
    s->data = (element *)malloc(s->capacity * sizeof(element));
}

//공백 상태 검출 함수
int is_empty(StackType *s) {
    return (s->top == -1);
}

//포화 상태 검출 함수
int is_full(StackType *s) {
    return (s->top == (s->capacity -1));
}

//삽입 함수
void push(StackType *s, element item) {
    if(is_full(s)) {
        s->capacity *= 2;
        s->data = (element *)realloc(s->data, s->capacity * sizeof(element));
    }
    s->data[++(s->top)] = item;
}

//삭제 함수
element pop(StackType *s) {
    if(is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else {
        return s->data[s->top--];
    }
}

int main(void) {
    StackType s;
    init_stack(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
    free(s.data);
    return 0;
}