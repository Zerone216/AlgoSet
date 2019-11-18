
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
 * @Date: 2019-9-18 15:50:33
 * @LastEditTime: 2019-9-18 15:50:37
 * @E-Mail: zerone216@163.com
 * @Homepage: http://www.zerone216.top
 * @Repository: https://github.com/zerone216/
 * @Support: 
 * @Others: 
 * @Modifylogs: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned long long DDWORD;

#define TRUE 1
#define FALSE 0

#define SEARCH_MAX 1024

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define malloc_type(type, size) (type *)malloc(sizeof(type) * size)

static char *str_dup(const char *src, int size)
{
    int len = strlen(src);
    if (size == -1)
        size = len + 1;

    char *pStr = malloc_type(char, size);
    if (!pStr)
        return NULL;
    
    memset(pStr, 0x00, size);
    memcpy(pStr, src, MIN(len, size - 1));
    return pStr;
}

static void str_free(char **p)
{
    if (p && *p)
    {
        free(*p);
        *p = NULL;
    }
}

static void init_next_table(BYTE *parten, int *next, int len)
{
    int i, j;
    next[0] = -1;
    for (i = 1; i < len; i++)
    {
        j = next[i - 1];
        while (parten[j + 1] != parten[i] && (j >= 0))
            j = next[j];
        if (parten[i] == parten[j + 1])
            next[i] = j + 1;
        else
            next[i] = -1;
    }

    return;
}

int kmp_match(BYTE *src, int slen, BYTE *parten, int plen, int *next)
{
    if (src == NULL || parten == NULL || next == NULL)
        return -1;

    if (plen <= 0 || slen <= 0 || plen > slen)
        return -1;

    int sindex = 0, pindex = 0;
    while (sindex < slen && pindex < plen)
    {
        if (src[sindex] == parten[pindex])
        {
            sindex++;
            pindex++;
        }
        else
        {
            if (pindex == 0)
                sindex++;
            else
                pindex = next[pindex - 1] + 1;
        }
    }

    return (pindex == plen) ? (sindex - plen) : -1;
}

int search_all_match(BYTE *src, int slen, BYTE *parten, int plen, int *position, int ptnum)
{
    if (src == NULL || parten == NULL || position == NULL)
        return 0;

    if (plen <= 0 || slen <= 0 || plen > slen)
        return 0;

    int *next = malloc_type(int, plen);
    if (!next)
        return 0;

    memset(next, 0x00, plen);
    init_next_table(parten, next, plen);

    int offset = 0;
    int num = 0;

    while (TRUE)
    {
        if (offset > (slen - plen) || num >= ptnum)
            break;

        *(position + num) = kmp_match(src + offset, slen - offset, parten, plen, next);
        if (*(position + num) == -1)
            break;

        *(position + num) += offset;
        if (*(position + num) > slen)
            break;

        printf("find position = [%d]\n", *(position + num));

        offset = *(position + num) + 1;
        num ++;
    }

    free(next);

    return num;
}

int main(int argc, char **argv)
{
    if(argc < 4)
    {
        printf("Missing Parameters!\nUsage:\n\t./kmp string1[src] string2[parten] searchLimits[num]\n\n");
        return 1;
    }

    int ptnum = atoi(argv[3]);
    if(ptnum <= 0)
    {
        printf("Error Parameters!\nThe third para must be a num!\n\n");
        return 2;
    }

    char * src = str_dup((const char *)argv[1], -1);
    char * parten = str_dup((const char *)argv[2], -1);

    
    
    int * position = malloc_type(int, ptnum);
    search_all_match((BYTE *)src, strlen(src), (BYTE *)parten, strlen(parten), position, ptnum);

    str_free(&src);
    str_free(&parten);
    return 0;
}
