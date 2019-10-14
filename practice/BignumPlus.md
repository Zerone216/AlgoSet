# 大数字加法的实现（C）

C语言的内置类型`int`（32位系统下为4字节，32位），无符号整型最大可表示2^32-1=2147483647（字符长度为10位），而`signed long long`也最大为2^64 - 1=18446744073709551999（字符长度为20位），如果要计算更大的数的加法运算，计算机将无法存储这些数字，所以要转换为对字符串的处理。

可以使用小学学到的竖式计算的方式来处理，从个位开始逐位相加，和大于10则进位。

这里首先要考虑到字符串表示的大数在内存的存储方式，数字的位越高对应的数组的索引越小，即个位的数字字符在数组末尾。所以需要先将数字字符串逆序，然后将每一位使用字符对应的真实数值进行计算放入新的数组，最后将结果数组的每一个值还原为字符值并逆序输出。

## 解决思路


### 1. 先将相加的两个大数字符串num1[]和num2[]逆序处理

```C
inline void swap(unsigned char * x, unsigned char * y)
{
	*x += *y;
	*y = *x - *y;
	*x = *x - *y;
}

char * strReverse(char * str)
{
	char * start = str;
	char * end = str + strlen(str) - 1;
	while(start < end) 
		swap((unsigned char *)start ++, (unsigned char *)end --); //对称交换头和尾

	return str;
}
```

这里`swap`是交换两个`unsigned char`类型变量的值，使用内联可以避免函数调用的栈开销，提高运行效率。

### 2. 每一位都转换为真实数值：`c -= '0'`

```C
void transToRealVal(char * str, int len)
{
	char * start = str;
	char * end = str + len - 1;
	while(start <= end) 
	{
		*start -= '0'; 
		start ++;
	}

	return;
}
```

### 3. 从低到高逐位相加（注意进位）存入新的数组result[]

```c
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
		if(result[i] >= 10) //向高位进位
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

```

### 4. 将result[]每一位都还原为数字对应的字符值：`c += '0'`

```c
void transToCharVal(char * str, int len)
{
	char * start = str;
	char * end = str + len - 1;
	while(start <= end)
	{
		*start += '0'; 
		start ++;
	}

	return;
}
```
需要注意的是字符串参数`str`的每一位都是真实数值，中间某一个值可能为0,不能用`strlen()`取长度，必须传入参数`len`来确保`str`的真实长度。

### 5. 将result[]逆序处理


## 完整代码

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max(x,y) ((x) > (y) ? (x) : (y))
#define Min(x,y) ((x) < (y) ? (x) : (y))

#define malloc_type(type, num) (type *)malloc(num * sizeof(type)) 

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

inline void swap(unsigned char * x, unsigned char * y)
{
	*x += *y;
	*y = *x - *y;
	*x = *x - *y;
}

char * strReverse(char * str, int len)
{
	char * start = str;
	char * end = str + Min(len, strlen(str)) - 1;
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
	int resultLen = Max(numLen1, numLen2) + 1; //此处+1考虑到最高位进位，计算结果的长度增加
	printf("resultLen=[%d]\n", resultLen);
	
	char * fmt = strdump("", 64); 
	sprintf(fmt,"[%%%ds]\n", resultLen);//格式化输出，个位对齐
	
	char * num1 = strdump(argv[1], resultLen);
	printf(fmt, num1);

	char * num2 = strdump(argv[2], resultLen);	
	printf(fmt, num2);

    //////////////////////////////////////////////////////
	char * result = bignumPlus(num1, num2, resultLen);
	printf(fmt, result);
    //////////////////////////////////////////////////////

	destoryResult(&result); //销毁结果

	strfree(&fmt);
	strfree(&num1);
	strfree(&num2);
	
    return 0;
}
```

## 运行结果

这里使用的linux环境，源码文件为bigNumPlus.c, 用`gcc`编译：
```
gcc -g -Wall -O3 -o bigNumPlus bigNumPlus.c
```

### 测试结果

#### 两个数位数相同时

```
root@ubuntu:/home/ubuntu/Github# ./bigNumPlus 3 5
resultLen=[2]
[ 3]
[ 5]
[ 8]

root@ubuntu:/home/ubuntu/Github# ./bigNumPlus 8 5
resultLen=[2]
[ 8]
[ 5]
[13]
```

```
root@ubuntu:/home/ubuntu/Github# ./bigNumPlus 1324515231423212344 8231472653421234213
resultLen=[20]
[ 1324515231423212344]
[ 8231472653421234213]
[ 9555987884844446557]

root@ubuntu:/home/ubuntu/Github# ./bigNumPlus 29834728347283498678234092374 92340923947023947628346928348
resultLen=[30]
[ 29834728347283498678234092374]
[ 92340923947023947628346928348]
[122175652294307446306581020722]

```

#### 两个数位数不相同时

```
root@ubuntu:/home/ubuntu/Github# ./bigNumPlus 29283742834238468273642039456234 9234092394702323423652345
resultLen=[33]
[ 29283742834238468273642039456234]
[        9234092394702323423652345]
[ 29283752068330862975965463108579]

root@ubuntu:/home/ubuntu/Github# ./bigNumPlus 1234567893244523452345234584567523234598293465928364502374659029783452345456230345456 34534634567345672345623462345763456733453345634563456345754694057823465234567453645309237452093487528345023904 
resultLen=[111]
[                          1234567893244523452345234584567523234598293465928364502374659029783452345456230345456]
[ 34534634567345672345623462345763456733453345634563456345754694057823465234567453645309237452093487528345023904]
[ 34534634567345672345623463580331349977976797979798040913277928656116931162931956019968267235545832984575369360]
```

## 总结

本文章简单地实现了大数字加法运算，有几个细节需要注意到，此外大数字的减法、乘法和除法可以参考加法的实现思路，对于带小数的大数字运算对小数部分可以单独处理，但是要参考浮点数的表示原理，与整数部分不一样。另外程序要尽可能的优化，减少不必要的操作和无意义的变量，对数组的操作要准确，防止越界。