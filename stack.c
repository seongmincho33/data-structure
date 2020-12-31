#include<stdio.h>
#include<stdlib.h>

//스택이 전역 변수로 구현됩니다.
#define MAX_STACK_SIZE 100 // 스택의 최대 크기
typedef int element; // 데이터의 자료형
element stack[MAX_STACK_SIZE]; // 1차원 배열
int top = -1;

//공백 상태 검출 함수
int is_empty(){
    return (top == -1);
}

//포화 상태 검출 함수
int is_full(){
    return (top == (MAX_STACK_SIZE -1));
}

//삽입 함수
//stderr : 기본 출력장치 (모니터) ->에러 표시할 때 사용합니다. 
//fprintf(stderr, "Error Test!"); 처럼 사용합니다.
//fprintf가 그냥 파일에 작성하는 함수인줄 알았나요? 사실 스트림에 출력하는 함수입니다.
//왜 printf를 안쓸까요. 이유는 버퍼때문에 출력을 재때 못하는 경우가 있습니다.
void push(element item){
    if (is_full()){
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else {
        stack[++top] = item;
    }
}

//삭제함수
void pop(){
    if (is_empty()) {
        fprintf(stderr, "스택 공백 에러\n");
    }
    else {
        return stack[top--];
    }
}

//피크 함수
// C에서 exit() 이라는 함수는, 현재의 C프로그램 자체를 완전 종료하는 기능을 가집니다. 
// 주로, 에러가 났을 때 강제 종료시키기 위해 if문 속에서 사용됩니다. 종료하기 전에 
// 또한 "모든 열려진 파일"들을 자동으로 닫습니다. 출력 버퍼 속에 데이터가 있으면 그것을 쓰기 완료시킵니다. 
// 즉, 모든 것을 잘 정리해 놓고 종료합니다.

// 그리고 exit(123) 이렇게 괄호 속에 int형 정수 숫자를 넣어주면 그 숫자를 운영체제에 반환합니다. 
// 즉 "에러 코드"를 반환합니다. 에러 없이 정상 종료할 때에는 exit(0) 이렇게 0을 반환하고, 
// 에러가 나서 종료할 때에는 0이 아닌 숫자, 대체로 1을 반환합니다.

// exit() 함수를 사용하기 위해서는 stdlib.h 헤더파일을 인클루드해 주어야 합니다. 그렇지 않으면 
// error C3861: 'exit': identifier not found 라는 에러가 발생합니다.
element peek() {
    if(is_empty()) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else {
        return stack[top];
    }
}

//메인함수
int main(void) {
    push(1);
    push(2);
    push(3);
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    return 0;
}