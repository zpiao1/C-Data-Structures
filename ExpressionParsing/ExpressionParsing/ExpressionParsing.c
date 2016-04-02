#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

// char stack
char stack[25];
int top = -1;

void push(char item)
{
	stack[++top] = item;
}

char pop()
{
	return stack[top--];
}

// returns precedence of opeartors
int precedence(char symbol)
{
	if (strchr("+-", symbol) != NULL)
		return 2;
	else if (strchr("*/", symbol) != NULL)
		return 3;
	else if (symbol == '^')
		return 4;
	else if (strchr("()#", symbol) != NULL)
		return 1;
	else
		return INT_MIN;
}

// check whether the symbol is operator?
int isOperator(char symbol)
{
	if (strchr("+-*/^()", symbol) != NULL)
		return 1;
	else
		return 0;
}

// converts infix expression to postfix
void convert(char infix[], char postfix[])
{
	size_t i;
	int symbol, j = 0;
	stack[++top] = '#';

	for (i = 0; i < strlen(infix); i++)
	{
		symbol = infix[i];

		if (!isOperator(symbol))
			postfix[j++] = symbol;
		else
		{
			if (symbol == '(')
				push(symbol);
			else
			{
				if (symbol == ')')
				{
					while (stack[top] != '(')
						postfix[j++] = pop();
					pop();
				}
				else
				{
					if (precedence(symbol) > precedence(stack[top]))
						push(symbol);
					else
					{
						while (precedence(symbol) <= precedence(stack[top]))
							postfix[j++] = pop();
						push(symbol);
					}
				}
			}
		}
	}

	while (stack[top] != '#')
		postfix[j++] = pop();
	postfix[j] = '\0';
}

int stack_int[25];
int top_int = -1;

void push_int(int item)
{
	stack_int[++top_int] = item;
}

char pop_int()
{
	return stack_int[top_int--];
}

// evaluates postfix expression
int evaluate(char *postfix)
{
	char ch;
	int i = 0, operand1, operand2;

	while (ch = postfix[i++])
	{
		if (isdigit(ch))
			push_int(ch - '0');	// Push the operand
		else
		{
			// Operator, pop two operands
			operand2 = pop_int();
			operand1 = pop_int();

			switch (ch)
			{
			case '+':
				push_int(operand1 + operand2);
				break;
			case '-':
				push_int(operand1 - operand2);
				break;
			case '*':
				push_int(operand1 * operand2);
				break;
			case '/':
				push_int(operand1 / operand2);
				break;
			}
		}
	}

	return stack_int[top_int];
}

int main()
{
	char infix[25] = "1*(2+3)", postfix[25];
	convert(infix, postfix);

	printf("Infix expression is: %s\n", infix);
	printf("Postfix expression is: %s\n", postfix);
	printf("Evaluated expression is: %d\n", evaluate(postfix));

	return 0;
}