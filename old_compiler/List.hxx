/*
**
** generic linked list class
**
** exa/analog
**
*/

#ifndef List_h
#define List_h

template<class T>
class List;

template<class T>
class ListTraversal;

template<class T>
class ListNode
{
private:
  ListNode<T> *succ;
  ListNode<T> *pred;
  T content;

public:
friend class List<T>;
friend class ListTraversal<T>;
  
  // constructors
  ListNode() : succ(NULL), pred(NULL) {}
  ListNode(ListNode<T> *s, ListNode<T> *p, T c)
    : succ(s), pred(p), content(c) {}
  
  // destructor
  //~ListNode<T>() {}

  T  get() { return content; }
};


template<class T>
class List
{
public:
  friend ListNode<T>;

  List() : head(NULL), tail(NULL) {}
  ~List() {
    ListNode<T> *node=head, *next;
    while (node) {
      next=node->succ;
      delete node;
      node=next;
    }
  }

  int is_empty() { return head==NULL; }
  
  //void insert( ListNode<T> *node, ListNode<T> *pred) {
  //  ListNode<T> *succ;	/* successor of the node to insert */
  //  
  //  if (pred==NULL)		/* is it an add_head? */
  //    this.add_head(node);
  //  else if (pred==tail)	/* an add_tail? */
  //    this.add_tail(node);
  //  else {
  //    succ=pred->succ;	/* let's find that successor*/
  //    pred->succ=node;	/* and link the three together */
  //    node->pred=pred;
  //    node->succ=succ;
  //    succ->pred=node;
  //  }
  //}

  void add_head( T c) {
    ListNode<T> *node = new ListNode<T>(head, NULL, c);
    head=node;
    if (tail)
      node->succ->pred=node;
    else
      tail=node;
  }
  
  void add_tail( T c) {
    ListNode<T> *node = new ListNode<T>(NULL, tail, c);
    tail=node;
    if (head)
      node->pred->succ=node;
    else
      head=node;
  }

  void add_tail( List<T>& list) {
    if (list.head) {
      if (head) { 
	tail->succ=list.head;
	list.head->pred=tail;
      }
      else
	head=list.head;
      tail=list.tail;
    }
  }
  
  T rem_head() {
    ListNode<T> *node;
    T content;
    
    node=head;
    if (node) {
      if (tail!=node)
	head=node->succ;
      else
	head=tail=NULL;
      content=node->content;
      delete node;
      return(content);
    }
    else
      return node->content;
  }
  
  T rem_tail() {
    ListNode<T> *node;
    T content;
    
    node=tail;
    if (node) {
      if (head!=node)
	tail=node->pred;
      else
	head=tail=NULL;
      content=node->content;
      delete node;
      return(content);
    }
    else
      return node->content;
  }

  T get_head() { return head->get(); }
  T get_tail() { return tail->get(); }

  ListTraversal<T> beg_head() { return ListTraversal<T>(head); }
  ListTraversal<T> beg_tail() { return ListTraversal<T>(tail); }

  T operator [](ListTraversal<T> i) { return i.node->content; }
  
private:
  ListNode<T> *head;
  ListNode<T> *tail;
  
};


template<class T>
class ListTraversal
{
  friend class List<T>;

  ListNode<T> *node;

public:
  ListTraversal() {}
  ListTraversal(ListNode<T> *n) : node(n) {}
  ~ListTraversal() {}

  void succ() { node = node->succ; }
  void pred() { node = node->pred; }
  int state() { return (int)node; }
};

#endif






