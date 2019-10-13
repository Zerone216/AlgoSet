#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max(x,y) ((x) > (y) ? (x) : (y))
#define Min(x,y) ((x) < (y) ? (x) : (y))

#define malloc_type(type, num) (type *)malloc(num * sizeof(type)) 

inline void swap(unsigned char * x, unsigned char * y)
{
	*x += *y;
	*y = *x - *y;
	*x = *x - *y;
}

char * strdump(char * str, int size)
{
	char * string = (char *)malloc(size + 1);
	if(!string)
		return NULL;
	memset(string, '\0', size + 1);
	memcpy(string, str, Min(strlen(str), size));

	return string;
}

void strfree(char ** str)
{
	if(*str)
	{
		free(*str);
		*str = NULL;
	}
}

char * strReverse(char * str)
{
	char * start = str;
	char * end = str + strlen(str) - 1;
	while(start < end) 
		swap((unsigned char *)start ++, (unsigned char *)end --);

	return str;
}

void transToRealVal(char * str, int len)
{
	char * start = str;
	char * end = str + len - 1;
	while(start <= end) 
	{
		*start -= '0'; //'RVal(*start);
		start ++;
	}

	return;
}

void transToCharVal(char * str, int len)
{
	char * start = str;
	char * end = str + len - 1;
	while(start <= end)
	{
		*start += '0'; //''CVal(*start);
		start ++;
	}

	return;
}

char * bignumPlus(char * num1, char * num2, int resultLen)
{
	
	strReverse(num1);
	strReverse(num2);
	
	transToRealVal(num1, strlen(num1));
	transToRealVal(num2, strlen(num2));
	
	char * result = malloc_type(char, resultLen);
	
	int resultSize = 0;
	int i = 0;
	for(i = 0; i < resultLen - 1; i ++)
	{
		result[i] += (num1[i]+ num2[i]);
		resultSize = i + 1;
		if(result[i] >= 10)
		{
			result[i + 1]  += 1;
			result[i] %= 10;
			resultSize ++;
		}
	}

	transToCharVal(result, resultSize);
	strReverse(result);	

	return result;
}

void destoryResult(char ** result)
{
	if(*result)
	{
		free(*result);
		*result = NULL;
	}
}

int main(int argc, char ** argv)
{
	int numLen1 = strlen(argv[1]);
	int numLen2 = strlen(argv[2]);
	int resultLen = Max(numLen1, numLen2) + 1; //
	printf("resultLen=[%d]\n", resultLen);
	
	char * fmt = strdump("", 64);
	sprintf(fmt,"[%%%ds]\n", resultLen);
	
	char * num1 = strdump(argv[1], resultLen);
	//printf("num1=\t[%50s]\n", num1);
	printf(fmt, num1);
	char * num2 = strdump(argv[2], resultLen);	
	//printf("num2=\t[%50s]\n", num2);
	printf(fmt, num2);

	char * result = bignumPlus(num1, num2, resultLen);

	//printf("result=\t[%50s]\n", result);	
	printf(fmt, result);	
	destoryResult(&result);
	strfree(&fmt);
	strfree(&num1);
	strfree(&num2);
	return 0;
}
