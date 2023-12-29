#include "dna_strand.hpp"

#include <stdexcept>
DNAstrand::~DNAstrand() {
    while(head_ != nullptr) {
        Node* ptr = head_->next;
        delete head_;
        head_ = ptr;
    }
    head_ = nullptr;
    tail_ = nullptr;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
    if (Strlen(pattern) == 0 || to_splice_in.head_ == nullptr || this == &to_splice_in) {
        return;
    }
    Node * seq_start = nullptr;
    Node * seq_end = nullptr;
    Node temp('\0',head_);
    // std::cout << temp->next->data << std::endl;
    FindSpliceRange(&temp, pattern, seq_start, seq_end);
    if (seq_start == nullptr) {
        throw std::runtime_error("sequence not found");
    }
    Node * to_del = seq_start->next;
    while (to_del != seq_end) {
        Node * ptr = to_del->next;
        delete to_del;
        to_del = ptr;
    }
    if (seq_start == &temp && seq_end == nullptr) {
        head_ = to_splice_in.head_;
        tail_ = to_splice_in.tail_;
    } else if (seq_start == &temp && seq_end != nullptr) {
        head_ = to_splice_in.head_;
        to_splice_in.tail_->next = seq_end;
    } else if (seq_start != &temp && seq_end == nullptr) {
        seq_start->next = to_splice_in.head_;
        tail_ = to_splice_in.tail_;
    } else if (seq_start != &temp && seq_end != nullptr) {
        seq_start->next = to_splice_in.head_;
        to_splice_in.tail_->next = seq_end;
    }
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr;
}

void DNAstrand::FindSpliceRange(Node * find_start, const char* pattern, Node *& seq_start, Node *& seq_end) {
    unsigned int index = 0;
    bool found = false;
    Node * possible = nullptr;
    while (find_start->next != nullptr) {
        if (find_start->next->data == pattern[index]) {
            if (index == 1 && find_start->next->data == pattern[0]) {
                FindSpliceRange(find_start, pattern, seq_start, seq_end);
                if (seq_start != nullptr) {
                    break;
                }
            }
            if (!found){
                possible = find_start;
                found = true;
            }
            index += 1;
            if (index == Strlen(pattern)) {
                seq_start = possible;
                if (find_start->next != nullptr && find_start->next->next != nullptr) {
                    seq_end = find_start->next->next;
                } else {
                    seq_end = nullptr;
                }
                FindSpliceRange(find_start->next, pattern, seq_start, seq_end);
                break;
            }
            find_start = find_start->next;
        } else {
            index = 0;
            found = false;
            if (find_start->next->data != pattern[0]) {
                find_start = find_start->next;
            }
        }
    }
}

void DNAstrand::PushBack(char data) {
    if (head_ == nullptr) {
        Node * newnode = new Node(data);
        head_ = newnode;
        tail_ = newnode;
    } else {
        Node * newnode = new Node(data);
        tail_->next = newnode;
        tail_ = newnode;
    }
}

unsigned int DNAstrand::Strlen(const char *s) {
    unsigned int count = 0;
    while(*s!='\0') {
        count++;
        s++;
    }
    return count;
}

DNAstrand::DNAstrand(const char* pattern) {
    unsigned int index = 0;
    while (pattern[index] != '\0') {
        PushBack(pattern[index]);
        index++;
    }
}
