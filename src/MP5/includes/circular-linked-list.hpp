#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void InsertASC(const T& data);
  void InsertDESC(const T& data);
  void Reverse();
  void ReverseHelper();
  void ChangeOrder();
  // void ReverseToDESC();
  void Copy(const CircularLinkedList<T>& source);
  void Destroy();
  void Pushback(const T& data);


  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);
  
  
private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template<typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  Copy(source);
}

template<typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source) {
  if (this == &source) {
    return *this;
  }
  Destroy();
  Copy(source);
  return *this;
}

template<typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  Destroy();
}

template<typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    Pushback(data);
  } else if (node_order_ == Order::kASC) {
    InsertASC(data);
  } else {
    InsertDESC(data);
  }
}

template<typename T>
void CircularLinkedList<T>::InsertASC(const T& data) {
  if (head_ == tail_) {
    Node<T>* newnode = new Node<T>(data);
    if (data >= head_->data) {
      head_->next = newnode;
      tail_ = newnode;
      tail_->next = head_;
    } else {
      newnode->next = head_;
      head_ = newnode;
      tail_->next = newnode;
    }
    return;
  }
  if (data < head_->data || data >= tail_->data) {
    Node<T>* newnode = new Node<T>(data);
    newnode->next = head_;
    tail_->next = newnode;
    if (data < head_->data) {
      head_ = newnode;
    } else if (data>= tail_->data){
      tail_ = newnode;
    }
    return;
  }
  Node<T>* temp = head_;
  do {
    Node<T>* tempnext = temp->next;
    if (data >= temp->data && data < tempnext->data) {
      Node<T>* newnode = new Node<T>(data);
      newnode->next = tempnext;
      temp->next = newnode;
      return;
    }
    temp = temp->next;
  } while (temp != head_);
}

template<typename T>
void CircularLinkedList<T>::InsertDESC(const T& data) {
  if (head_ == tail_) {
    Node<T>* newnode = new Node<T>(data);
    if (data >= head_->data) {
      newnode->next = head_;
      head_ = newnode;
      tail_->next = newnode;
    } else {
      head_->next = newnode;
      tail_ = newnode;
      tail_->next = head_;
    }
    return;
  }
  if (data > head_->data || data <= tail_->data) {
    Node<T>* newnode = new Node<T>(data);
    newnode->next = head_;
    tail_->next = newnode;
    if (data > head_->data) {
      head_ = newnode;
    } else if (data <= tail_->data) {
      tail_ = newnode;
    }
    return;
  }
  Node<T>* temp = head_;
  do {
    Node<T>* tempnext = temp->next;
    if (data <= temp->data && data > tempnext->data) {
      Node<T>* newnode = new Node<T>(data);
      newnode->next = tempnext;
      temp->next = newnode;
      return;
    }
    temp = temp->next;
  } while (temp != head_);
}


template<typename T>
void CircularLinkedList<T>::Reverse() {
  if (head_ == nullptr) {
    ChangeOrder();
    return;
  }
  if (head_ == tail_) {
    ChangeOrder();
    head_->next = tail_;
    tail_->next = head_;
    return;
  }
  ReverseHelper();
  ChangeOrder();
}

template<typename T>
void CircularLinkedList<T>::ChangeOrder() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else if (node_order_ == Order::kDESC) {
    node_order_ = Order::kASC;
  }
}

template<typename T>
void CircularLinkedList<T>::ReverseHelper() {
  Node<T>* temp = tail_;
  Node<T>* prev = temp;
  temp = temp->next;
  Node<T>* next = temp->next;
  do {
    temp->next = prev;
    prev = temp;
    temp = next;
    next = next->next;
  } while (temp != head_);
  Node<T> *transit = head_;
  head_ = tail_;
  tail_ = transit;
}


template<typename T>
void CircularLinkedList<T>::Copy(const CircularLinkedList<T>& source) {
  if (source.node_order_ != node_order_) {
    node_order_ = source.node_order_;
  }
  if (source.head_ == nullptr) {
    return;
  }
  Node<T> * temp = source.head_;
  do {
    Pushback(temp->data);
    temp = temp->next;
  } while (temp != source.head_);
}

template<typename T>
void CircularLinkedList<T>::Destroy() {
  if (head_ == nullptr) {
    return;
  }
  tail_->next = nullptr;
  Node<T> * temp = this->head_;
  while (temp != nullptr) {
    Node<T> * tempnext = temp->next;
    delete temp;
    temp = tempnext;
  }
  head_ = nullptr;
  tail_ = nullptr;
  node_order_ = Order::kASC;
}

template<typename T>
void CircularLinkedList<T>::Pushback(const T& data) {
  if (head_ == nullptr) {
    Node<T>* newnode = new Node<T>(data);
    head_ = newnode;
    tail_ = newnode;
    head_->next = tail_;
    tail_->next = head_;
    return;
  }
  Node<T>* newnode = new Node<T>(data);
  tail_->next = newnode;
  tail_ = newnode;
  tail_->next = head_;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif