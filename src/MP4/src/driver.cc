#include <iostream>

#include "dna_strand.hpp"

int main() {
    DNAstrand * test1 = new DNAstrand("ctgaattcg");
    // test1->PushBack('o');
    // test1->PushBack('a');
    // test1->PushBack('b');
    // test1->PushBack('a');
    // test1->PushBack('b');
    // test1->PushBack('a');
    // test1->PushBack('b');

    // for (Node * i = test1.head_; i != NULL; i = i->next) {
    //     std::cout << i->data << std::endl;
    // }
    DNAstrand * test2  = new DNAstrand("tgatc");
    // test2.PushBack('t');
    // test2.PushBack('c');
    DNAstrand * test3  = new DNAstrand("xxx");
    

    test1->SpliceIn("gaattc", *test2);
    

    // test1->SpliceIn("bbb", *test2);
    int count = 0;
    for (Node * i = test1->head_; i != NULL; i = i->next) {
        count++;
        
        std::cout << i->data << std::endl;
    }
    std::cout << "head is " << test1->head_->data << " " << "tail is " << test1->tail_->data << "count is " << count << std::endl;
}