#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _slistnode zSListNode;
struct _slistnode
{
    int typesize;
    void * data;
    zSListNode * next;
};

zSListNode * z_slist_new()
{
    zSListNode * new = (zSListNode *) malloc(sizeof(zSListNode));
    if(!new)
        return NULL;

    new->next = NULL;
    new->data = NULL;
    new->typesize = 0;
    return new; 
}

void z_slist_destory(zSListNode ** head)
{
    zSListNode * ptmp = *head;
    zSListNode * pdes = NULL;
    while(ptmp)
    {
        pdes = ptmp;
        ptmp = ptmp->next;

        if(pdes)
        {
            if(pdes->data)
                free(pdes->data);
            
            free(pdes);
        }
    }    

    *head = NULL;
}

zSListNode * z_slist_first(zSListNode * head)
{
    if(!head)
        return NULL;
      
    return head->next;
}

zSListNode * z_slist_last(zSListNode * head)
{
    if(!head)
        return NULL;
    
    zSListNode * ptmp = head->next;
    while(ptmp && ptmp->next)
        ptmp = ptmp->next;

    return ptmp;
}

int z_slist_append(zSListNode * head, void * elem, int typesize)
{
    zSListNode * new = (zSListNode *) malloc(sizeof(zSListNode));
    if(!new)
        return 1;

    new->typesize = typesize;
    new->next = NULL;
    new->data = malloc(typesize);
    if(!new->data)
    {
        free(new);
        return 2;
    }

    memcpy(new->data, elem, typesize);
    head->next = new;
    return 0;
}

int z_slist_prepend(zSListNode * head, void * elem, int typesize)
{
    zSListNode * new = (zSListNode *) malloc(sizeof(zSListNode));
    if(!new)
        return 1;

    new->typesize = typesize;
    new->next = NULL;
    new->data = malloc(typesize);
    if(!new->data)
    {
        free(new);
        return 2;
    }

    memcpy(new->data, elem, typesize);

    head->next = new;
    return 0;
}