#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct stack{
	int num[1024];
	int top;
};
int pop(struct stack *st);
void push(struct stack *st, int ele);

long To_Binary1(int num);
char *To_Binary(int num);

int main(int argc, char *argv[])
{
	int message = 4129;	
	message = atoi(argv[1]);
//	printf("Binary sequence:%s\n", To_Binary(message));
	message <<= 2;
	printf("Left shift: %d\n", message);


	return 0;
}

long To_Binary1(int num)
{
	int round = 1, remainder;
	long ret;

	while(num != 0)
	{
		remainder = num % 2;
		ret += remainder * round;
		num /= 2;
		round *= 10;
	}
	return ret;
}
char *To_Binary(int num)
{
	int round = 1, remainder;
	static char ret[1024] = "";
	char tmp[4];
	struct stack *st;
	st->top = -1;

	while(num != 0)
	{
		remainder = num % 2;
		num /= 2;
		push(st, remainder);
	}

	while (st->top >= 0)
	{
		sprintf(tmp, "%d", pop(st));
		strcat(ret, tmp);
	}
	return ret;
}
int pop(struct stack *st)
{
	int ret;
	if (st->top == -1)
	{
		printf("No element in stack;\n");
		exit(1);
	}
	ret = st->num[st->top];
	st->top--;
	return ret;
}
void push(struct stack *st, int ele)
{
	st->top++;
	st->num[st->top] = ele;	
	return;
}

	
