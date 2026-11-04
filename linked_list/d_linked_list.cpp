#include "d_linked_list.hpp"
#include <iostream>
#include <set>

using namespace std;

DLinkedList::DLinkedList(int head_data) {
    head_ = new DNode();
    head_->prev_ = nullptr;
    head_->next_ = nullptr;
    head_->data_ = head_data;
    tail_ = head_;
    size_ = 1;
}

void DLinkedList::push(DNode* node) {
    node->prev_ = tail_;
    node->next_ = nullptr;
    tail_ = node;
    size_ += 1;
}