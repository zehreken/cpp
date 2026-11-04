#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Node {
    Node(int data) : data_(data) {};
    Node* next_ = nullptr;
    int data_ = 0;
};

class LinkedList {
  public:
    explicit LinkedList(int head_data);
    void push(int data);
    bool pop(int& out);
    void insert(int data, int index);
    bool remove(int index);
    Node* reverse();
    static int compare(Node* head_a, Node* head_b);
    static Node* merge_sorted(Node* head_a, Node* head_b);
    static Node* remove_duplicates(Node* head);
    static int has_cycle(Node* head);
    static Node* find_merge_node(Node* head_a, Node* head_b);
    size_t get_size();
    void print();
    void print_reverse();

  private:
    Node* head_;
    Node* tail_;
    size_t size_;
};

#endif
