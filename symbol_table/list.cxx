/*
** $VER: list.cxx 1.02 (28 Oct 1996)
**
** C++ file for linked list classes
**
** Eray "eXa" Ozkural
**
*/

#include <stdlib.h>

#include "list.h"

SoftList::SoftList()
{
    Head=NULL;
    Tail=NULL;
}

SoftList::~SoftList()
{
    SoftNode *node=Head, *next;
    while (node)
    {
        next=node->Succ;
        delete node;
        node=next;
    }
}

int SoftList::IsEmpty()
{
    return Head==NULL;
}

void SoftList::Insert( SoftNode *node, SoftNode *pred)
{
    SoftNode *succ;          /* successor of the node to insert */

    if (pred==NULL)                 /* is it an AddHead? */
        this.AddHead(node);
    else if (pred==Tail)      /* an AddTail? */
        this.AddTail(node);
    else
    {
        succ=pred->Succ;                /* let's find that successor*/
        pred->Succ=node;                /* and link the three together */
        node->Pred=pred;
        node->Succ=succ;
        succ->Pred=node;
    }
}

void SoftList::AddHead( void *data )
{
    SoftNode *node = new SoftNode();

    node->Data=data;

    node->Pred=NULL;            /* node will be the first in line */
    node->Succ=Head;      /* old head will be 2nd */
    Head=node;
    if (node->Succ==NULL)
        Tail=node;
    else
        node->Succ->Pred=node;
}

void SoftList::AddTail( void *data )
{
    SoftNode *node = new SoftNode();

    node->Data=data;

    node->Succ=NULL;
    node->Pred=Tail;
    Tail=node;
    if (node->Pred==NULL)
        Head=node;
    else
        node->Pred->Succ=node;
}

void SoftNode::Rem()
{
    if (Succ)
        Succ->Pred=Pred;
    if (Pred)
        Pred->Succ=Succ;
    delete this;
}

void *SoftNode::Get()
{
    return(Data);
}

void *SoftList::RemHead()
{
    SoftNode *node;
    void *data;

    node=Head;
    if (node!=NULL)
       if (Tail!=node)
           Head=node->Succ;
       else
           Head=Tail=NULL;
    data=node->Data;
    delete node;
    return(data);
}

void *SoftList::RemTail()
{
    SoftNode *node;
    void *data;

    node=Head;
    if (node!=NULL)
       if (Tail!=node)
           Tail=node->Pred;
       else
           Head=Tail=NULL;
    data=node->Data;
    delete node;
    return(data);
}

void *SoftList::GetHead()
{
    return Head->Get();
}
