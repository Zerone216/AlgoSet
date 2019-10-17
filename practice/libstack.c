#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct _stack
{
    int top;
    int stacksize;
    int typesize;
    void * data;
};

typedef struct _stack zStack;

zStack * z_stack_new(int stacksize, int typesize)
{
    zStack * zstack = (zStack *) malloc(sizeof(zStack));
    if(!zstack)
        return NULL;

    zstack->stacksize = stacksize;
    zstack->typesize = typesize;
    zstack->data = malloc(stacksize * sizeof(typesize));
    if(!zstack->data)
    {
        free(zstack);
        return NULL;
    }
    
    return zstack;
} 

void z_stack_destory(zStack ** zstack)
{
    if(*zstack)
    {
        if((*zstack)->data)
        {

            free((*zstack)->data);
            (*zstack)->data = NULL;
        }

        free(*zstack);
        *zstack = NULL;
    }
}

int z_stack_empty(zStack * zstack)
{
    if(!zstack)
        return 1;
    
    return (zstack->top == 0);
}

int z_stack_clear(zStack * zstack)
{
    if(!zstack)
        return 1;
    
    zstack->top = 0;
    return 0;
}

int z_stack_push(zStack * zstack, void * elem, int typesize)
{
    if(!zstack)
        return 1;
    
    if(typesize != zstack->typesize)
        return 2;
    
    if(!zstack->data)
        return 3;
    
    if(zstack->top >= zstack->stacksize - 1)
        return 4;

    int offset = typesize * zstack->top ++;
    memcpy((char *)zstack->data + offset, elem, typesize);
    return 0;
}

int z_stack_top(zStack * zstack, void * elem, int typesize)
{
    if(!zstack)
        return 1;

    if(typesize != zstack->typesize)
        return 2;
    
    if(!zstack->data)
        return 3;
    
    if(zstack->top <= 0)
        return 4;
    
    int offset = typesize * (zstack->top - 1);
    memcpy(elem, (char *)zstack->data + offset, typesize);
    return 0;
}

int z_stack_pop(zStack * zstack)
{
    if(!zstack)
        return 1;

    if(zstack->top <= 0)
        return 2;
    
    -- zstack->top;
    return 0;
}