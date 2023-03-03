#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>`
#include<stdlib.h>
#include <string.h>
#include<math.h>
#define Max 80
int top = -1;
bool isEmpty();
void In2Post(char*, char*);//中轉後
int Priority(char);//運算元Rank
float Calculate(char, float, float);//計算
float evaluatePost(char *);//Postfix運算
void main()
{
	FILE*fptr = fopen("expressions.dat.txt", "r");
	char infixtemp[Max] = { 0 };
	char postfixtemp[Max] = { 0 };
	while (fgets(infixtemp, 100, fptr))
	{
		memset(postfixtemp, 0, Max);//重複使用需要每次都清0
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
		printf("Evaluate:%f\n", evaluatePost(Postfix));//運算總和
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
		case '('://最高順位,直接Push
			stack[++top] = (infix[i]);
			break;
		case '+':case'-':case'*':case'/':case'^':
			while (Priority(stack[top]) >= Priority(infix[i]) && !isEmpty())
				*(Postfix + j++) = stack[top--];
			*(Postfix + j++) = ' ';//區分p1 p2
			stack[++top] = infix[i];
			break;
		case')':
			while (stack[top] != '(')//"("不用輸出
				*(Postfix + j++) = stack[top--];
			top--;//stack回到"("之前的位置
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
				stackf[--top] = Calculate(ptr[i], stackf[top], stackf[top + 1]);//把結果存在p1
				break;
			default:
				if (i == 0)stackf[++top] = atof(ptr);//兩位數以上只判斷一次
			}
		ptr = strtok(NULL, " ");
	}
	return stackf[top--];//回傳時為0,--回到top=-1
}