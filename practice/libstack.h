#ifndef __LIB_STACK__
#define __LIB_STACK__

#include <stdlib.h>

#pragma pack(1)

typedef struct _stack zStack;

struct _stack
{
    int top;
    int stacksize;
    int typesize;
    void * data;
};

#pragma pack()

zStack * z_stack_new(int stacksize, int typesize);

void z_stack_destory(zStack ** zstack);

int z_stack_empty(zStack * zstack);

int z_stack_clear(zStack * zstack);

int z_stack_push(zStack * zstack, void * elem, int typesize);

int z_stack_top(zStack * zstack, void * elem, int typesize);

int z_stack_pop(zStack * zstack);

#endif
