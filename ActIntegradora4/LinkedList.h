#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "NodeLinkedList.h"

template <class T> 
class LinkedList {
  private:
    NodeLinkedList<T> *head;
    NodeLinkedList<T> *tail;
    int numElements;
  
  public:
    LinkedList();
    ~LinkedList();
    int getNumElements();
    void printList();
    void addFirst(T value);
    void addLast(T value);
    bool deleteData(T value);
    bool deleteAt(int position);
    T getData(int position);
    NodeLinkedList<T> *getHead();

};

// Complejidad O(1)
template <class T> 
LinkedList<T>::LinkedList() {
  //std::cout << "---> Creando una lista ligada vacia: " << this << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T> 
LinkedList<T>::~LinkedList() {
  //std::cout << "---> Liberando memoria de la lista ligada: " << this << std::endl;
  NodeLinkedList<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
  
}

// Complejidad O(1)
template <class T> 
int LinkedList<T>::getNumElements() { 
  return numElements; 
}

// Complejidad O(n)
template <class T> 
void LinkedList<T>::printList() {
  NodeLinkedList<T> *ptr = head;
  while (ptr != nullptr) {
    std::cout << ptr->data << " ";
    ptr = ptr->next;
  }
  std::cout << std::endl;
}

// Complejidad O(1)
template <class T>
void LinkedList<T>::addFirst(T value) {
  // 1. crear un newNode
  NodeLinkedList<T> *newNode = new NodeLinkedList<T>(value);
  // 2. apuntar newNode->next a donde esta head
  newNode->next = head;
  // 3. Actualizar head para apuntar al newNode
  head = newNode;
  // Si fue el primer nodo insertado en la lista, actualiza tail
  if (numElements == 0)
    tail = newNode;
  numElements++;
}

// Complejidad O(1)
template <class T>
void LinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    addFirst(value);
  else {
    // 1. crear un newNode
    NodeLinkedList<T> *newNode = new NodeLinkedList<T>(value);
    // 2. apuntar tail->next a newNode
    tail->next = newNode;
    // 3. actualizar tail para apuntar al newNode
    tail = newNode;
    numElements++;
  }
}

// Complejidad O(n)
template <class T>
bool LinkedList<T>::deleteData(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    return false;
  else {
    NodeLinkedList<T> *p = head;
    NodeLinkedList<T> *prev = nullptr;
    while (p != nullptr && p->data != value) {
      prev = p;
      p = p->next;
    }
    // si no existe value en la lista
    if (p == nullptr)
      return false;
    // si debo borrar el primer elemento de la lista
    if (p != nullptr && p == head) {
      head = p->next;
      if (head == nullptr) // habia solo un nodo en la lista
        tail = nullptr;
    } else if (p->next == nullptr) { // debo borrar el ultimo nodo 
      prev->next = nullptr;
      tail = prev;
    } else {
      prev->next = p->next;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T>
bool LinkedList<T>::deleteAt(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) {
    NodeLinkedList<T> *p = head;
    // si la lista contiene un solo nodo
    if (head != nullptr && head->next == nullptr) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = p->next;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  } else { // borrar cualquier otro elemento de la lista
    NodeLinkedList<T> *p = head;
    NodeLinkedList<T> *prev = nullptr;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (index != position) {
      prev = p;
      p = p->next;
      index++;
    }
    // si debo borrar el ultimo elemento
    if (p->next == nullptr) {
      prev->next = nullptr;
      tail = prev;
    }
    else { // borrar cualquier otro nodo
      prev->next = p->next;
    }
    delete p;
    numElements--;
    return true;
  }
}

template <class T> T LinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else {
    if (position == 0) { // si es el primero de la lista
      return head->data;
    }
    // debemos buscar el elemento
    NodeLinkedList<T> *p = head;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (p != nullptr) {
      if (index == position)
        return p->data;
      p = p->next;
      index++;
    }
    return {};
  }
}

template <class T> 
NodeLinkedList<T> * LinkedList<T>::getHead() { 
  return head; 
}


#endif // _LINKEDLIST_H_


