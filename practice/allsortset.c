/*
 * @Declaration: 
 *  Copyright (c) 2009-2019 Zhang Sheng (Mr. Zhang) 
 * 
 *  This program is free software; you can redistribute it and/or modify it under 
 *  the terms of the GNU General Public License as published by the Free Software 
 *  Foundation, either version 2 or any later version. 
 *  
 *  Redistribution and use in source and binary forms, with or without modification, 
 *  are permitted provided that the following conditions are met: 
 *  
 *  1. Redistributions of source code must retain the above copyright notice, this 
 *  list of conditions and the following disclaimer. 
 *  
 *  2. Redistributions in binary form must reproduce the above copyright notice, 
 *  this list of conditions and the following disclaimer in the documentation and/or 
 *  other materials provided with the distribution. 
 *  
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY 
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or ITNESS FOR A 
 *  PARTICULAR PURPOSE. See the GNU General Public License for more details. A copy 
 *  of the GNU General Public License is available at: 
 *  http://www.fsf.org/licensing/licenses 
 *  
 *  All manufacturing, reproduction,use, and sales rights pertaining to this subject 
 *  matter are governed bythe license agreement. The recipient of this software 
 *  implicitly accepts the terms of the license.
 * 
 * @Description: 
 * @version: 
 * @Author: Zhang Sheng
 * @Date: 2018-11-27 15:20:33
 * @LastEditTime: 2018-11-27 15:20:33
 * @E-Mail: zerone216@163.com
 * @Homepage: http://www.zerone216.top:8080
 * @Repository: https://github.com/zerone216/
 * @Support: 
 * @Others: 
 * @Modifylogs: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

typedef char CHAR;
typedef short SHORT;
typedef void VOID;

typedef u_int8_t BYTE;
typedef BYTE u8;
typedef BYTE UINT8;

typedef u_int16_t WORD;
typedef WORD u16;
typedef WORD UINT16;

typedef u_int32_t DWORD;
typedef DWORD u32;
typedef DWORD UINT32;

typedef u_int64_t DDWORD;
typedef DDWORD u64;
typedef DDWORD UINT64;

typedef long LONG;
typedef unsigned long ULONG;

typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;

#define P_VOID(p) (VOID *)(p)
#define POINTER(p) P_VOID(p)

#define P_BYTE(p) (BYTE *)(p)
#define P_WORD(p) (WORD *)(p)
#define P_DWORD(p) (DWORD *)(p)
#define P_DDWORD(p) (DDWORD *)(p)

#define DIRECT_SMALL_TO_BIG 0
#define DIRECT_BIG_TO_SMALL 1

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef struct _Sort_Info
{
	int * array;
	int len;
	int direction;
	//void (*function)(void *);
}SORT_INFO, *pSORT_INFO;

int time_use(void (*func)(void *), void * data)
{
	struct timespec begintime = {0,0};
	struct timespec endtime = {0,0};

	//获得开始时间
	clock_gettime(CLOCK_REALTIME, &begintime);
	
	//////////////////
	func(data);
	/////////////////

	//获得结束时间
	clock_gettime(CLOCK_REALTIME, &endtime);
	
	DDWORD time_pass = (endtime.tv_sec * 1000000000 + endtime.tv_nsec ) - (begintime.tv_sec * 1000000000 + begintime.tv_nsec );
	printf("timeused: %llu ns\n", time_pass);
	
	return 0;
}

void show_array(int * array, int len)
{
	int i = 0;
	//printf("current array: ");
	for(i = 0; i < len; i ++)
		;//printf("%d ", *(array + i));

	printf("\n");
	return ;
}

int swap_value(void * a, void * b, int memlen)
{
	if(memlen > sizeof(ULONGLONG))
		return -1;
	
	ULONGLONG tmp = 0;
	memcpy(&tmp, a, memlen);
	memcpy(a, b, memlen);
	memcpy(b, &tmp, memlen);
	//printf("swap [%d]<-->[%d]\n", * (int *)a, *(int *)b);
	
	return 0;
}

int get_max_of_array(int * array, int len)
{
	int i = 0;
	int max = *array;
	for(i = 0; i < len; i ++)
	{
		max = MAX(max, *(array + i));
	}

	return max;
}

int get_min_of_array(int * array, int len)
{
	int i = 0;
	int min = *array;
	for(i = 0; i < len; i ++)
	{
		min = MIN(min, *(array + i));
	}
	
	return min;
}

int get_radix_of_number(int num)
{
	int radix = 1;
	int value = num;
	
	while(value)
	{
		value /= 10;
		if(value) radix ++;
	}
	
	return radix;
}

//快速排序1
void quick_sort1(int * array, int start, int end, int direction)
{
	if(start > end)
		return;
	
	int i = start;
    int j = end;
    int temp = *(array + start);
    
    while(i < j)
    {
    	// 越过不小于基准值的数据 
        if(DIRECT_SMALL_TO_BIG == direction)
    		while( *(array + j) >= temp && j > i ) j --;
		else
			while( *(array + j) <= temp && j > i ) j --;
        
        
        if( j > i )
        {
			swap_value(array + i, array + j, sizeof(int));
            i++;
			
            // 越过小于基准值的数据 
            if(DIRECT_SMALL_TO_BIG == direction)
	    		while(*(array + i) < temp && i < j ) i ++;
			else
	            while(*(array + i) > temp && i < j ) i ++;
			
            if( i < j )
            {
                swap_value(array + j, array + i, sizeof(int));
                j--;
            }
        }        
    }
	
    *(array + i) = temp; 
	
    quick_sort1(array, start, i - 1, direction);
    quick_sort1(array, j + 1, end, direction);  
	
	return ;
}

void quick_sort1_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	quick_sort1(sort_info->array, 0, sort_info->len - 1, sort_info->direction);
	return;
}

//快速排序2
void quick_sort2(int * array, int start, int end, int direction) 
{
	if(start > end)
		return;
	
	int temp = *(array + start); //temp中存的就是基准数 
	int i = start; 
	int j = end; 

	while(i != j) 
	{ 
		if(DIRECT_SMALL_TO_BIG == direction)
	 	{
			while(*(array + j) >= temp && i < j) j --; //顺序很重要，要先从右边开始找 
			while(*(array + i) <= temp && i < j) i ++; //再找右边的 
	 	}
		else
		{
			while(*(array + j) <= temp && i < j) j --; //顺序很重要，要先从右边开始找 
			while(*(array + i) >= temp && i < j) i ++; //再找右边的 
		}
		
		if(i < j) swap_value(array + i, array + j, sizeof(int));//交换两个数在数组中的位置 
	} 
	
	//最终将基准数归位 
	*(array + start) = *(array + i);
	*(array + i) = temp;

	quick_sort2(array, start, i-1, direction);//继续处理左边的，这里是一个递归的过程 
	quick_sort2(array, i+1, end, direction);//继续处理右边的 ，这里是一个递归的过程 

	return;
} 

void quick_sort2_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	quick_sort2(sort_info->array, 0, sort_info->len - 1, sort_info->direction);
	return;
}

//冒泡排序
void bubble_sort(int * array, int len, int direction)
{
	int i = 0, j = 0;//同时找最大值的最小需要两个下标遍历
	int flag = 0; //交换动作的标记
	int pos = 0;//用来记录最后一次交换的位置
	int start = 0, end = len - 1;  //每次遍历的下标范围
	
	for (i = 0; i < len - 1; i ++)//确定排序趟数
	{
		flag = 0;
		start = pos;
		//正向冒泡
		for (j = start; j < end; j++) //正向比较到记录位置即可
		{
			if(DIRECT_SMALL_TO_BIG == direction)
			{
				if (*(array + j) > *(array + j + 1))
				{
					swap_value(array +j, array + j + 1, sizeof(int)); //交换

					flag = 1;//加入标记
					pos = j;//交换元素，记录最后一次交换的位置
				}
			}
			else
			{
				if (*(array + j) < *(array + j + 1))
				{
					swap_value(array +j, array + j + 1, sizeof(int)); //交换

					flag = 1;//加入标记
					pos = j;//交换元素，记录最后一次交换的位置
				}
			}
		}
		
		if (flag == 0) return;//如果没有交换过元素，则已经有序,直接结束

		flag = 0;
		end = pos;
		//反向冒泡
		for (j = end; j > start; j --)//反向比较到记录位置即可
		{
			if(DIRECT_SMALL_TO_BIG == direction)
			{
				if (*(array + j) < *(array + j - 1))
				{
					swap_value(array +j, array + j - 1, sizeof(int)); //交换

					flag = 1;//加入标记
					pos = j;//交换元素，记录最后一次交换的位置
				}
			}
			else
			{
				if (*(array + j) > *(array + j - 1))
				{
					swap_value(array +j, array + j - 1, sizeof(int)); //交换

					flag = 1;//加入标记
					pos = j;//交换元素，记录最后一次交换的位置
				}
			}
		}
		
		if (flag == 0) return;//如果没有交换过元素，则已经有序,直接结束
	}

	return ;
}

void bubble_sort_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	bubble_sort(sort_info->array, sort_info->len, sort_info->direction);
	return;
}

int get_max_index(int * array, int index_a, int index_b)
{
	return *(array + index_a) > *(array + index_b) ? index_a : index_b;		
}

int get_min_index(int * array, int index_a, int index_b)
{
	return *(array + index_a) < *(array + index_b) ? index_a : index_b;		
}

//选择排序
void select_sort(int * array, int len, int direction)
{
	int i = 0, j = 0;
	int swap_idnex = 0;
	
	for(i = 0; i < len - 1; i ++)
	{
		swap_idnex = i;
		
		for(j = i + 1; j < len; j ++)
		{
			if(DIRECT_SMALL_TO_BIG == direction) 
				swap_idnex = get_min_index(array, swap_idnex, j);
			else 
				swap_idnex = get_max_index(array, swap_idnex, j);
		}

 		if(swap_idnex != i) swap_value(array + swap_idnex, array + i, sizeof(int));
	}

	return;
}

void select_sort_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	select_sort(sort_info->array, sort_info->len, sort_info->direction);
	return;
}

//插入排序
void insert_sort(int * array, int len, int direction)
{
	int i = 0, j = 0;
	for(i = 1; i < len; i ++)
	{
		for(j = i; j > 0; j --)
		{
			if(DIRECT_SMALL_TO_BIG == direction) 
			{
				if(*(array + j) < *(array +j - 1))
					swap_value(array + j, array + j - 1, sizeof(int));
			}
			else 
			{
				if(*(array + j) > *(array +j - 1))
					swap_value(array + j, array + j - 1, sizeof(int));
			}
		}
	}

	return;
}

void insert_sort_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	insert_sort(sort_info->array, sort_info->len, sort_info->direction);
	return;
}


void merge(int * arr, int left, int mid, int right, int * temp, int direction)
{
	int i = left;//左序列指针
	int j = mid + 1;//右序列指针
	int t = 0;//临时数组指针
	
	while (i <= mid && j <= right)
	{
		if(DIRECT_SMALL_TO_BIG == direction) 
		{
			if(*(arr + i) <= *(arr + j) )
				*(temp + (t ++)) = *(arr + (i ++));
			else
				*(temp + (t ++)) = *(arr + (j ++));
		}
		else
		{
			if(*(arr + i) >= *(arr + j) )
				*(temp + (t ++)) = *(arr + (i ++));
			else
				*(temp + (t ++)) = *(arr + (j ++));
		}	
	}
	
	while(i <= mid)//将左边剩余元素填充进temp中
		*(temp + (t ++)) = *(arr + (i ++));
	
	while(j <= right)//将右序列剩余元素填充进temp中
		*(temp + (t ++)) = *(arr + (j ++));
	
	t = 0;
	
	//将temp中的元素全部拷贝到原数组中
	while(left <= right)
		*(arr + (left ++)) = *(temp + (t ++));

	return ;
}

void merge_sort_kernel(int * arr, int left, int right, int * temp, int direction)
{
	if(left >= right)
		return ;
	
	int mid = (left + right) / 2;
	merge_sort_kernel(arr, left, mid, temp, direction);//左边归并排序，使得左子序列有序
	merge_sort_kernel(arr, mid+1, right, temp, direction);//右边归并排序，使得右子序列有序
	merge(arr, left, mid, right, temp, direction);//将两个有序子数组合并操作
	
	return ;
}

//归并排序
void merge_sort(int * array, int len, int direction)
{
	int memsize = sizeof(int) * len;
	int * temp = (int *) malloc(memsize);//在排序前，先建好一个长度等于原数组长度的临时数组，避免递归中频繁开辟空间
	memset(temp, 0x00, memsize);
	
	merge_sort_kernel(array, 0, len-1, temp, direction);
	
	free(temp);
	return ;
}

void merge_sort_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	merge_sort(sort_info->array, sort_info->len, sort_info->direction);
	return;
}

//调整大顶堆（仅是调整过程，建立在大顶堆已构建的基础上）
void adjust_heap(int  * arr, int i, int length, int direction)
{
	int temp = *(arr + i);//先取出当前元素i
	int k = 0;

	for(k = i * 2 + 1; k < length; k = k * 2 + 1) //从i结点的左子结点开始，也就是2i+1处开始
	{
		if(DIRECT_SMALL_TO_BIG == direction) 
		{
			if(k+1 < length && *(arr + k)  < *(arr + k + 1))//如果左子结点小于右子结点，k指向右子结点
				k++;

			if(*(arr + k) > temp) //如果子节点大于父节点，将子节点值赋给父节点（不用进行交换）
			{
				*(arr + i) = *(arr + k);
				i = k;
			}
			else
				break;
		}
		else
		{
			if(k+1 < length && *(arr + k)  > *(arr + k + 1))//如果左子结点大于右子结点，k指向右子结点
				k++;

			if(*(arr + k) < temp) //如果子节点小于父节点，将子节点值赋给父节点（不用进行交换）
			{
				*(arr + i) = *(arr + k);
				i = k;
			}
			else
				break;
		}
	}
	
	*(arr + i) = temp;//将temp值放到最终的位置

	return;
 }

//堆排序
void heap_sort(int * array, int len, int direction)
{
	int i = 0;
	
	//1.构建大顶堆
	for(i = len /2 -1; i >= 0; i --)//从第一个非叶子结点从下至上，从右至左调整结构
		adjust_heap(array, i, len, direction);

	//2.调整堆结构+交换堆顶元素与末尾元素
	for(i = len -1; i > 0; i --)
	{
		swap_value(array, array + i, sizeof(int));//将堆顶元素与末尾元素进行交换
		adjust_heap(array, 0, i, direction);//重新对堆进行调整
	}

	return;
}

void heap_sort_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	heap_sort(sort_info->array, sort_info->len, sort_info->direction);
	return;
}

//希尔排序
void shell_sort(int * array, int len, int direction)
{
    int d = 0; //d为增量
	int i = 0, j = 0;
	int temp = 0;
	
    for(d = len/2; d >= 1; d = d/2) //增量递减到1使完成排序
    {
    	
        for(i = d; i < len; i ++)   //插入排序的一轮
        {
            temp = *(array + i);
			
            for(j = i -d; j >= 0; j = j -d)
            {
            	if(DIRECT_SMALL_TO_BIG == direction)
        		{
		         	if( *(array + j) > temp) 
						*(array + j + d) = *(array + j);
					else
						break;
        		}
				else
				{
					if( *(array + j) < temp) 
						*(array + j + d) = *(array + j);
					else
						break;
				}
            }
			
        	*(array + j + d) = temp;
        }
    }

	return;
}

void shell_sort_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	shell_sort(sort_info->array, sort_info->len, sort_info->direction);
	return;
}


#define RADIX_10 10   //以十进制表示，十个桶，表示每一位的十个数字（0 ~ 9）
#define RADIX_8 8   //以八进制表示，八个桶，表示每一位的八个数字（0 ~ 7）
#define RADIX_16 16   //以十六进制表示，十六个桶，表示每一位的十六个数字（0 ~ f）

int get_num_in_pos(int num,int pos) //获得某个数字的第pos位的值
{
    int temp = 1;
    for (int i = 0; i < pos - 1; i++)
        temp *= RADIX_10;
	
    return (num / temp) % RADIX_10;
}

//基数排序
void radix_sort(int * array, int len, int direction)
{
	int max_value = get_max_of_array(array, len);
	int keynum = get_radix_of_number(max_value);//最大数的整数位数
	
    int * radixArrays[RADIX_10];    //分别为0~9的序列空间
    for (int i = 0; i < RADIX_10; i++)
    {
		*(radixArrays + i) = (int *) malloc(sizeof(int) * len);
        **(radixArrays + i) = 0;    //index为0处记录这组数据的个数
    }
	
    for (int pos = 1; pos <= keynum; pos ++)    //从个位开始到31位
    {
        for (int i = 0; i < len; i++)    //分配过程
        {
			int num = get_num_in_pos(*(array + i), pos);
			int index = ++ *(*(radixArrays + num));
			*(*(radixArrays + num) + index) = *(array + i);
        }

		if(DIRECT_SMALL_TO_BIG == direction)
		{
	        for (int i = 0, j =0; i < RADIX_10; i++) //位数从低到高，写回到原数组中，复位radixArrays
	        {
		        for (int k = 1; k <= *(*(radixArrays + i)); k ++)
		            *(array + (j ++)) = *(*(radixArrays + i) + k);
				
	            **(radixArrays + i) = 0;
	        }
		}
		else
		{
			for (int i = RADIX_10 - 1, j =0; i >= 0 ; i --) //位数从高到低，写回到原数组中，复位radixArrays
	        {
		        for (int k = 1; k <= *(*(radixArrays + i)); k ++)
		            *(array + (j ++)) = *(*(radixArrays + i) + k);
				
	            **(radixArrays + i) = 0;
	        }
		}
    }

	for (int i = 0; i < RADIX_10; i++)
    {
        if(*(radixArrays + i) != NULL)
			free(*(radixArrays + i));
    }
	 
	return ;
}

void radix_sort_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	radix_sort(sort_info->array, sort_info->len, sort_info->direction);
	return;
}

//计数排序1（比较法）
void count_sort1(int * array, int len, int direction)
{
	int i = 0, j = 0;
	int memsize = 0;
	int max = get_max_of_array(array, len);
	int min = get_min_of_array(array, len);
    int countnum = max -min + 1;
	
	memsize = len * sizeof(int);
    int * temp = (int *)malloc(memsize); 
	memset(temp, 0x00, memsize);
	
	memsize = countnum * sizeof(int);
    int * count = (int *)malloc(memsize); 
	memset(count, 0x00, memsize);
	
	for(i = 0; i < len - 1; i ++) 
	{
		for(j = i + 1;j < len; j ++) 
		{
			if(array[i] < array[j])
				count[j] ++;
			else
				count[i] ++;
		}
	}
	
	for(i = 0; i < len; i ++)
		temp[count[i]] = array[i];

	for(i = 0; i < len; i ++)
	{
		if(DIRECT_SMALL_TO_BIG == direction)
			array[i] = temp[i];
		else
			array[i] = temp[len - 1 - i];
	}
	
	free(count);
	free(temp);
	
	return;
}

void count_sort1_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	count_sort1(sort_info->array, sort_info->len, sort_info->direction);
	return;
}

//计数排序2（分布法）
void count_sort2(int * array, int len, int direction)
{
    int i = 0, j = 0;
	int memsize = 0;
	int max = get_max_of_array(array, len);
	int min = get_min_of_array(array, len);
    int countnum = max -min + 1;
	
	memsize = len * sizeof(int);
    int * temp = (int *)malloc(memsize); 
	memset(temp, 0x00, memsize);
	
	memsize = countnum * sizeof(int);
    int * count = (int *)malloc(memsize); 
	memset(count, 0x00, memsize);
	
	for(i = 0; i < len; i ++)
		count[array[i] - min] ++;
	
	for(i = 0; i < max - min; i ++)
		count[i + 1] += count[i];
	
	for(i = 0; i < len; i ++) 
	{
		j = array[i] - min;
		temp[count[j] - 1] = array[i];
		count[j] --;
	}
	
	for(i = 0; i < len; i ++)
	{
		if(DIRECT_SMALL_TO_BIG == direction)
			array[i] = temp[i];
		else
			array[i] = temp[len - 1 - i];
	}
	
	free(count);
	free(temp);
	
	return;
}

void count_sort2_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	count_sort2(sort_info->array, sort_info->len, sort_info->direction);
	return;
}

typedef struct _BS_TREE_NODE
{
    int data; //保存数组元素的值
    //int deepth; //结点所在深度
    struct _BS_TREE_NODE * left;
    struct _BS_TREE_NODE * right;
} BS_TREE, *pBS_TREE;

void insert_BS_Tree(BS_TREE ** tree, int value) 
{
    if (*tree == NULL) 
	{
        *tree = (BS_TREE *) malloc(sizeof(BS_TREE));
		
        (*tree)->left=(*tree)->right=NULL;
        (*tree)->data = value;
        return;
    }
	
    if (value < (*tree)->data)
        insert_BS_Tree(&((*tree)->left), value);
    else
        insert_BS_Tree(&((*tree)->right), value);

	return;
}

void create_BS_Tree(BS_TREE** tree, int * array, int len) 
{
    *tree = NULL;
    for (int i=0; i < len; i++)
        insert_BS_Tree(tree, array[i]);

	return;
}

void destroy_BS_Tree(BS_TREE * tree) 
{
    if (tree == NULL) 
        return;

	if(tree->left != NULL)
    	destroy_BS_Tree(tree->left);

	if(tree->left != NULL)
   		destroy_BS_Tree(tree->right);
	
	free(tree);
	
	return;
}

void show_BS_Tree(BS_TREE * tree) {
    if (tree == NULL)
        return;
	
    if (tree->left != NULL)
        show_BS_Tree(tree->left);
	
	printf("%d ", tree->data);
	
    if (tree->right != NULL)
        show_BS_Tree(tree->right);
	
	return;
}

void get_data_from_BS_Tree(BS_TREE * tree, int * array, int *index, int direction) 
{
    if (tree == NULL)
        return;

	if(DIRECT_SMALL_TO_BIG == direction)
	{
	    if (tree->left != NULL)
	        get_data_from_BS_Tree(tree->left, array, index, direction);
		
		array[(*index) ++] = tree->data;
		
	    if (tree->right != NULL)
	        get_data_from_BS_Tree(tree->right, array, index, direction);
	}
	else
	{
		if (tree->right != NULL)
			get_data_from_BS_Tree(tree->right, array, index, direction);
		
		array[(*index) ++] = tree->data;
		
		if (tree->left != NULL)
			get_data_from_BS_Tree(tree->left, array, index, direction);	 
	}
	
	return;
}

void bstree_sort(int * array, int len, int direction)
{
    BS_TREE * root;
    create_BS_Tree(&root, array, len);
	
	int index = 0;
	get_data_from_BS_Tree(root, array, &index, direction);
	destroy_BS_Tree(root);

	return;
}

void bstree_sort_func(void * data)
{
	SORT_INFO * sort_info = (SORT_INFO *)data;
	bstree_sort(sort_info->array, sort_info->len, sort_info->direction);
	return;
}

int find_value_of(int * array, int len, int search)
{
	int i = 0;
	int index = -1;
	for(i = 0; i < len; i ++)
	{
		if(*(array + i) == search)
		{
			index = i;
			break;
		}
	}

	return index;
}

int generate_rand_array(int * array, int len, int min, int max, int ditto)
{
	int i = 0;
	int range = max - min + 1;
	if(range <= 0)
		return 1;
	
	printf("Generating the rand array ......\n");
	
	struct timespec stime = {0,0};
	for(i = 0; i < len; )
	{
		clock_gettime(CLOCK_REALTIME, &stime);
		int seed = stime.tv_sec + stime.tv_nsec * 1000000000; //以纳秒级作为产生随机数的种子
		srand(seed);
		int randvalue = rand() % range + min;
		
		if(ditto || find_value_of(array, len, randvalue) == -1)
		{
			*(array + i) = randvalue;
			i ++;
		}
	}

	return 0;
}

int main(int argc, char ** argv)
{
	int direction = DIRECT_SMALL_TO_BIG; //默认从小到大排序
	if(argc >= 2)
	{
		if(strncasecmp(argv[1],"-bs", 2) == 0)
		{
			direction = DIRECT_BIG_TO_SMALL;
		}
		else if(strncasecmp(argv[1],"-sb", 2) == 0)
		{
			direction = DIRECT_SMALL_TO_BIG;
		}
	}

	int valuenum = 0;
	int range_start = 0;
	int range_end = 0;
	int ditto = 0;
	
	printf("Please input the length of array:");
	scanf("%d", &valuenum);
	if(valuenum <= 0)
	{
		printf("Waring: The length of array is %d, cannot generate array!\n", valuenum);
		return 1;
	}
	
	printf("Please input the range of array element (start ~ end):");
	scanf("%d %d", &range_start, &range_end);

	if(range_end < range_start)
	{
		printf("Error: Start of range is larger than the end of it!\n");
		return 1;
	}
	else
	{
		if((range_end - range_start) < valuenum)
			ditto = 1;
		else
		{
			ditto = 0;
		}
	}
	
	int memsize = sizeof(int) * valuenum;
	int * array = (int *) malloc( memsize);
	if(array == NULL)
		return 0;

	memset(array, 0x00, memsize);
	generate_rand_array(array, valuenum, range_start, range_end, ditto);
	show_array(array, valuenum);
	
	int * arr = (int *) malloc( memsize);
	if(arr == NULL)
		return 0;
	
	SORT_INFO sort_info;
	memset(&sort_info, 0x00, sizeof(SORT_INFO));
	sort_info.array = arr;
	sort_info.len = valuenum;
	sort_info.direction = direction;
	
	printf("\nBubble sort(冒泡排序): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)bubble_sort_func, (void *)&sort_info);
	//bubble_sort(arr, valuenum, direction);
	show_array(arr, valuenum);

	printf("\nSelect sort(选择排序): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)select_sort_func, (void *)&sort_info);
	//select_sort(arr, valuenum, direction);
	show_array(arr, valuenum);

	printf("\nInsert sort(插入排序): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)insert_sort_func, (void *)&sort_info);
	//insert_sort(arr, valuenum, direction);
	show_array(arr, valuenum);

	printf("\nQuick sort1(快速排序1): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)quick_sort1_func, (void *)&sort_info);
	//quick_sort1(arr, 0, valuenum -1, direction);
	show_array(arr, valuenum);

	printf("\nQuick sort2(快速排序2): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)quick_sort2_func, (void *)&sort_info);
	//quick_sort2(arr, 0, valuenum -1, direction);
	show_array(arr, valuenum);
	
	printf("\nMerge sort(归并排序): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)merge_sort_func, (void *)&sort_info);
	//merge_sort(arr, valuenum, direction);
	show_array(arr, valuenum);

	printf("\nHeap sort(堆排序): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)heap_sort_func, (void *)&sort_info);
	//heap_sort(arr, valuenum, direction);
	show_array(arr, valuenum);

	printf("\nShell sort(希尔排序): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)shell_sort_func, (void *)&sort_info);
	//shell_sort(arr, valuenum, direction);
	show_array(arr, valuenum);

	printf("\nRadix sort(基数排序): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)radix_sort_func, (void *)&sort_info);
	//radix_sort(arr, valuenum, direction);
	show_array(arr, valuenum);

	printf("\nCount sort1(计数排序1): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)count_sort1_func, (void *)&sort_info);
	//count_sort1(arr, valuenum, direction);
	show_array(arr, valuenum);
	
	printf("\nCount sort2(计数排序2): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)count_sort2_func, (void *)&sort_info);
	//count_sort2(arr, valuenum, direction);
	show_array(arr, valuenum);

	printf("\nBtree sort(二叉树排序): \n");
	memset(arr, 0x00, memsize);
	memcpy(arr, array, memsize);
	show_array(arr, valuenum);
	time_use((void *)bstree_sort_func, (void *)&sort_info);
	//bstree_sort(arr, valuenum, direction);
	show_array(arr, valuenum);
	
	free(arr);
	free(array);
	return 0;
}