#pragma once

struct DNode {
    DNode* prev_ = nullptr;
    DNode* next_ = nullptr;
    int data_ = 0;
};

class DLinkedList {
  private:
    DNode* head_;
    DNode* tail_;
    int size_;

  public:
    DLinkedList(int head_data);
    void push(DNode* node);
    DNode* pop();
    void insert(DNode* node, int index);
    void remove(int index);
    DNode* reverse();
    static int compare(DNode* head_a, DNode* head_b);
    static DNode* merge_sorted(DNode* head_a, DNode* head_b);
    static DNode* remove_duplicates(DNode* head);
    static int has_cycle(DNode* head);
    static DNode* find_merge_node(DNode* head_a, DNode* head_b);
    DNode* get_head();
    DNode* get_tail();
    int get_size();
    void print();
    void print_reverse();
};