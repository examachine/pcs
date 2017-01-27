/*
**
** generic linked list class
**
** exa/analog
**
*/

#ifndef LIST_H
#define LIST_H

template <T>
class SoftNode
{
public:
    friend class SoftList;

    void Rem(); 
    void *Get();

private:
    SoftNode *Succ;
    SoftNode *Pred;
    void     *Data;
};

template <T>
class SoftList
{
public:
    friend SoftNode;

    SoftList();
    ~SoftList();

    int IsEmpty();
    void Insert( SoftNode *, SoftNode *);
    void add_head( void * );
    void add_tail( void * );
    void *eemHead();
    void *RemTail();
    void *GetHead();
    void *GetTail();

private:
    SoftNode *Head;
    SoftNode *Tail;

};

#endif
