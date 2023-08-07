#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define size 100
char stack[size];
char infix[size], postfix[size];
int top = -1;
bool f2=false;
void inToPost();
bool isEmpty() {
	if(top==-1)
		return true;
	else
		return false;
}
void push(char ch) {
	if(top>=size-1) {
		printf("Stack overflow");
		return;
	}
	top++;
	stack[top] = ch;
}
int pop() {
	if(top<=-1) {
		printf("Stack underflow");
		return 0;
	}
	top--;
	return stack[top+1];
}
int precedence(char symbol) {
	switch(symbol) {
		case '^':
			return 3;
		case '/':
		case '*':
			return 2;
		case '+':
		case '-':
			return 1;
		default:
			return 0;
	}
}
void print() {
	int i=0;
	printf("Postfix expression: ");
	while(postfix[i]) {
		if(f2==true)
			printf("%c ",postfix[i++]);
		else
			printf("%c ",postfix[i++]);
	}
	printf("\n");
}
int main() {
	printf("Enter infix expression: ");
	gets(infix);
	
	inToPost();
	print();
	return 0;
}
void inToPost() {
	int i,j=0;
	bool flag;
	char symbol,next;
	for(i=0;i<strlen(infix);i++) {
		flag = false;
		if(infix[i]==' ') {
			flag = true;
			f2 = true;
			continue;
		}
		symbol = infix[i];
		switch (symbol) {
			case '(':
					push(symbol);
					break;
			case ')':
					while((next=pop()) != '(')
						postfix[j++] = next;
					break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
					while(!isEmpty() && precedence(stack[top]) >= precedence(symbol))
						postfix[j++] = pop();
					push(symbol);
					break;
			default:
					postfix[j++] = symbol;			
		}
	}
	while(!isEmpty())
		postfix[j++] = pop();
	postfix[j] = '\0';
	
}