//관련된 데이터를 함수의 매개변수로 전달하는 방법
#include<stdio.h>
#include<stdlib.h>

//차후에 스택이 필요하면 여기만 복사하여 붙인다.
//====스택 코드의 시작 ====
#define MAX_STACK_SIZE 100

//스택이 구조체로 정의된다.
typedef int element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

//스택 초기화 함수
void init_stack(StackType *s) {
    s->top = -1;
}

//공백 상태 검출 함수
// 모든 연산은 구조체의 포인터를 받는다.
int is_empty(StackType *s) {
    return (s->top == -1);
}

//포화 상태 검출 함수
int is_full(StackType *s){
    return (s->top == (MAX_STACK_SIZE-1));
}

//삽입함수
void push(StackType *s, element item) {
    if(is_full(s)){
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }else {
        s->data[++(s->top)] = item;
    }
}

//삭제함수
element pop(StackType *s) {
    if(is_empty(s)){
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }else {
        return s->data[(s->top)--];
    }
}

//피크함수
element peek(StackType *s) {
    if(is_empty()) {
        fprintf(stderr, "스택 공백 에러\n");\
        exit(1);
    }else {
        return s->data[s->top];
    }
}

//=====스택 코드의 끝=====

int main(void) {
    //스택을 정적으로 생성한다.
    StackType s;

    init_stack(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
}