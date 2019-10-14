/*************************************************************************
	> File Name: InversePolandExp.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: Mon 14 Oct 2019 07:06:03 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

struct _Def_Stack {
	int top;
	double * data;
};

typedef struct _Def_Stack Stack;

#define malloc_type(type, size) (type *)malloc(sizeof(type) * size)
#define Bzero(p, size) memset(p, 0x00, size);
#define Db(var) (double)(var)

Stack * stackInit(int stackSize)
{
	Stack * stack = malloc_type(Stack, 1);
	if(!stack)
		return NULL;
	
	Bzero(stack, sizeof(Stack));
	stack->data = malloc_type(double, stackSize);
	if(!stack->data)
	{
		free(stack);
		return NULL;
	}

	Bzero(stack->data, sizeof(double) * stackSize);
	return stack;
}

void stackDestory(Stack ** stack)
{
	if(*stack)
	{
		if((*stack)->data)
		{
			free((*stack)->data);
			(*stack)->data = NULL;
		}

		free(*stack);
		*stack = NULL;
	}
}

void stack_push(Stack * stack, double data)
{
	
	stack->data[stack->top ++] = data;
	return;
}

double stack_top(Stack * stack)
{
	if(stack->top > 0)
		return stack->data[stack->top - 1];
	else
		return 0;
}

void stack_pop(Stack * stack)
{
	stack->top --;
	return;
}

void stack_clean(Stack * stack)
{
	stack->top = 0;
	return;
}

int stack_ifempty(Stack *stack)
{
	return (stack->top == 0);
}

int isDigitString(char * string)
{
	char * start = string;
	char * end = string + strlen(string) - 1;
	while(start <= end)
	{
		if(!isdigit(*start))
			return FALSE;

		start ++;
	}

	return TRUE;
}

double inversePolandExp(char ** expr, int exprSize)
{
	if(!expr || exprSize == 0)
		return -1;
	
	Stack * stack = stackInit(exprSize);
	if(!stack)
		return -1;
	
	double optNum1 = 0.0, optNum2 = 0.0;

	int i = 0;
	for(i = 1; i < exprSize; i ++)
	{

		//printf("[INFO][%s, %d] expr[%d]=[%s]\n", __FILE__, __LINE__, i, expr[i]);
		if(strcmp(expr[i], "+") == 0)
		{
			optNum1 = stack_top(stack);
			stack_pop(stack);
			optNum2 = stack_top(stack);
			stack_pop(stack);
			
			printf("[%lf]+[%lf]=[%lf]\n", optNum2, optNum1, (optNum2 + optNum1));
			optNum2 += optNum1;
			stack_push(stack, optNum2);
		}
		else if(strcmp(expr[i], "-") == 0)
		{
			optNum1 = stack_top(stack);
			stack_pop(stack);
			optNum2 = stack_top(stack);
			stack_pop(stack);
			printf("[%lf]-[%lf]=[%lf]\n", optNum2, optNum1, (optNum2 - optNum1));
			
			optNum2 -= optNum1;
			stack_push(stack, optNum2);
		}
		else if(strcmp(expr[i], "*") == 0)
		{
			optNum1 = stack_top(stack);
			stack_pop(stack);
			optNum2 = stack_top(stack);
			stack_pop(stack);
			printf("[%lf]*[%lf]=[%lf]\n", optNum2, optNum1, (optNum2 * optNum1));
			
			optNum2 *= optNum1;
			stack_push(stack, optNum2);
		}
		else if(strcmp(expr[i], "/") == 0)
		{
			optNum1 = stack_top(stack);
			stack_pop(stack);
			if(optNum1 == 0)
			{
				printf("[ERROR][%s, %d] Dividing zero!\n", __FILE__, __LINE__);
				stackDestory(&stack);
				return -1;
			}
			else
			{
				optNum2 = stack_top(stack);
				stack_pop(stack);
				printf("[%lf]/[%lf]=[%lf]\n", optNum2, optNum1, (optNum2 / optNum1));
			
				optNum2 /= optNum1;
				stack_push(stack, optNum2);
			}
		}
		else
		{
			if(isDigitString(expr[i]))
				stack_push(stack, Db(atoi(expr[i])));
		}
	}

	double result = -1;
	if(!stack_ifempty(stack))
		result = stack_top(stack);

	stackDestory(&stack);

	return result;
}

int main(int argc, char ** argv)
{
	printf("result=[%lf]\n", inversePolandExp(argv, argc));
	return 0;
}
