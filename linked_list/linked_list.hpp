#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Node {
    Node* next_ = nullptr;
    int data_ = 0;
};

class LinkedList {
  private:
    Node* head_;
    Node* tail_;
    int size_;

  public:
    LinkedList(int head_data);
    void push(Node* node);
    Node* pop();
    void insert(Node* node, int index);
    void remove(int index);
    Node* reverse();
    static int compare(Node* head_a, Node* head_b);
    static Node* merge_sorted(Node* head_a, Node* head_b);
    static Node* remove_duplicates(Node* head);
    static int has_cycle(Node* head);
    static Node* find_merge_node(Node* head_a, Node* head_b);
    Node* get_head();
    Node* get_tail();
    int get_size();
    void print();
    void print_reverse();
};

#endif
