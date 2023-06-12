#ifndef _NODELINKEDLIST_H_
#define _NODELINKEDLIST_H_

template <class T>
class NodeLinkedList {
  public:
    T data;
    NodeLinkedList<T> *next;

    NodeLinkedList();
    NodeLinkedList(T value);

};


template <class T>
NodeLinkedList<T>::NodeLinkedList() : data{}, next{nullptr} {}

template <class T>
NodeLinkedList<T>::NodeLinkedList(T value) : data{value}, next{nullptr} {}


#endif // _NODELINKEDLIST_H_

