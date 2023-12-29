#include <iostream>

#include "circular-linked-list.hpp"

int main() {
    CircularLinkedList<int> test1;
    test1.ChangeOrder();
    
    test1.InsertInOrder(1);
    test1.InsertInOrder(6);
    test1.InsertInOrder(5);
    test1.InsertInOrder(9);
    test1.InsertInOrder(0);
    test1.InsertInOrder(40);
    CircularLinkedList<int> test2(test1);
    test1.Reverse();
    std::cout << "test1 detail: " << test1 << "\t" << "head is " << test1.head_->data << "\t" << "tail is " << test1.tail_->data   <<"\t" 
    << "head's next is " << (test1.head_)->next->data << " tail's next is " << (test1.tail_)->next->data << std::endl;
    std::cout << "test2 detail: " << test2 << std::endl;
}
