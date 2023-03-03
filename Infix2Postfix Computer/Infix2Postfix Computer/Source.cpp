#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>`
#include<stdlib.h>
#include <string.h>
#include<math.h>
#define Max 80
int top = -1;
bool isEmpty();
void In2Post(char*, char*);//�����
int Priority(char);//�B�⤸Rank
float Calculate(char, float, float);//�p��
float evaluatePost(char *);//Postfix�B��
void main()
{
	FILE*fptr = fopen("expressions.dat.txt", "r");
	char infixtemp[Max] = { 0 };
	char postfixtemp[Max] = { 0 };
	while (fgets(infixtemp, 100, fptr))
	{
		memset(postfixtemp, 0, Max);//���ƨϥλݭn�C�����M0
		strtok(infixtemp, "\n");
		printf("Infix:%s\n", infixtemp);
		In2Post(infixtemp, postfixtemp);
		printf("Postfix:%s\n", postfixtemp);
		printf("Evaluate:%f\n", evaluatePost(postfixtemp));
		puts("=========================================================");
	}
	fclose(fptr);
	while (true)
	{
		char infix[Max];
		char*Postfix = (char*)calloc(Max, sizeof(char));//not has \0
		printf("Please Enter  Expression(Enter q can exit):");
		scanf("%s", &infix);
		if (*infix == 'q')break;
		printf("Infix:%s\n", infix);//Infix
		In2Post(infix, Postfix);
		printf("Postfix:%s\n", Postfix);//Postfix
		printf("Evaluate:%f\n", evaluatePost(Postfix));//�B���`�M
		free(Postfix);
	}
}
void In2Post(char* infix, char *Postfix)
{
	char stack[Max];
	int j = 0;
	for (int i = 0; infix[i] != '\0'; i++)
		switch (infix[i])
		{
		case '('://�̰�����,����Push
			stack[++top] = (infix[i]);
			break;
		case '+':case'-':case'*':case'/':case'^':
			while (Priority(stack[top]) >= Priority(infix[i]) && !isEmpty())
				*(Postfix + j++) = stack[top--];
			*(Postfix + j++) = ' ';//�Ϥ�p1 p2
			stack[++top] = infix[i];
			break;
		case')':
			while (stack[top] != '(')//"("���ο�X
				*(Postfix + j++) = stack[top--];
			top--;//stack�^��"("���e����m
			break;
		default:
			*(Postfix + j++) = infix[i];
		}
	while (!isEmpty())
		*(Postfix + j++) = stack[top--];
}
int Priority(char operation)
{
	switch (operation)
	{
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	case '^':return 3;
	default: return 0;
	}
}
float Calculate(char operation, float p1, float p2)
{
	switch (operation)
	{
	case '+': return p1 + p2;
	case '-': return p1 - p2;
	case '*': return p1 * p2;
	case '/': return p1 / p2;
	case '^': return pow(p1, p2);
	}
}
bool isEmpty()
{
	return top == -1;
}
float evaluatePost(char *Postfix)
{
	float stackf[Max] = { 0 };
	char* ptr = strtok(Postfix, " ");
	while (ptr != NULL)
	{
		for (int i = 0; i < strlen(ptr); i++)
			switch (ptr[i])
			{
			case'+':case'-':case'*':case'/':case'^':
				stackf[--top] = Calculate(ptr[i], stackf[top], stackf[top + 1]);//�⵲�G�s�bp1
				break;
			default:
				if (i == 0)stackf[++top] = atof(ptr);//���ƥH�W�u�P�_�@��
			}
		ptr = strtok(NULL, " ");
	}
	return stackf[top--];//�^�Ǯɬ�0,--�^��top=-1
}