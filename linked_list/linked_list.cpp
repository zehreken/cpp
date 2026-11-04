#include "linked_list.hpp"
#include <iostream>
#include <set>

using namespace std;

LinkedList::LinkedList(int head_data) {
    head_ = new Node();
    head_->next_ = nullptr;
    head_->data_ = head_data;
    tail_ = head_;
    size_ = 1;
}

void LinkedList::push(Node* node) {
    tail_->next_ = node;
    tail_ = node;
    size_ += 1;
}

Node* LinkedList::pop() {
    Node* itr = head_;
    Node* temp = nullptr;
    while (itr->next_ != nullptr) {
        temp = itr;
        itr = itr->next_;
    }
    tail_ = temp;
    size_ -= 1;

    return temp->next_;
}

void LinkedList::insert(Node* node, int index) {
    if (index < 0 || index >= size_) {
        cout << "EXCEPTION: illegal index value" << endl;
    } else if (index == 0) {
        node->next_ = head_;
        head_ = node;
        size_ += 1;
    } else {
        Node* itr = head_;
        Node* next = nullptr;
        int n = 0;
        while (itr != nullptr && n < index - 1) {
            itr = itr->next_;
            n += 1;
        }
        next = itr->next_;
        itr->next_ = node;
        node->next_ = next;
        size_ += 1;
    }
}

void LinkedList::remove(int index) {
    if (index < 0 || index >= size_) {
        cout << "EXCEPTION: illegal index value" << endl;
    } else if (index == 0) {
        delete head_;
        head_ = head_->next_;
        size_ -= 1;
    } else {
        Node* itr = head_;
        int n = 0;
        while (itr != nullptr && n < index - 1) {
            itr = itr->next_;
            n += 1;
        }
        itr->next_ = itr->next_->next_;
        size_ -= 1;
    }
}

Node* LinkedList::reverse() {
    Node *prev, *current, *next;
    prev = nullptr;
    current = head_;
    tail_ = head_;

    while (current != nullptr) {
        next = current->next_;
        current->next_ = prev;
        prev = current;
        current = next;
    }

    head_ = prev;
    return head_;
}

int LinkedList::compare(Node* head_a, Node* head_b) {
    int is_equal = 1;
    Node *itr_a, *itr_b;
    itr_a = head_a;
    itr_b = head_b;
    while (itr_a != nullptr) {
        if (itr_b == nullptr || itr_a->data_ != itr_b->data_) {
            is_equal = 0;
            break;
        }
        itr_a = itr_a->next_;
        itr_b = itr_b->next_;
    }
    if (itr_b != nullptr)
        is_equal = 0;

    return is_equal;
}

Node* LinkedList::merge_sorted(Node* head_a, Node* head_b) {
    if (head_a == nullptr)
        return head_b;
    else if (head_b == nullptr)
        return head_a;

    Node* temp = new Node();
    Node* merged_head = temp;
    Node* itr_a = head_a;
    Node* itr_b = head_b;

    bool iterate = true;
    while (iterate) {
        if (itr_a->data_ <= itr_b->data_) {
            temp->next_ = itr_a;
            temp = temp->next_;
            itr_a = itr_a->next_;
        } else {
            temp->next_ = itr_b;
            temp = temp->next_;
            itr_b = itr_b->next_;
        }
        if (itr_a == nullptr) {
            temp->next_ = itr_b;
            iterate = false;
        } else if (itr_b == nullptr) {
            temp->next_ = itr_a;
            iterate = false;
        }
    }

    return merged_head->next_;
}

Node* LinkedList::remove_duplicates(Node* head) {
    Node* itr = head;
    Node* temp = head;
    Node* new_head = temp;

    while (itr->next_ != nullptr) {
        if (itr->data_ != itr->next_->data_) {
            temp->next_ = itr->next_;
            temp = temp->next_;
        }
        itr = itr->next_;
    }
    temp->next_ = nullptr;

    return new_head;
}

int LinkedList::has_cycle(Node* head) {
    set<Node*> n_refs;
    int size = n_refs.size();
    Node* temp = head;

    while (temp != nullptr) {
        n_refs.insert(temp);
        size++;
        if (size > n_refs.size())
            return 1;
        temp = temp->next_;
    }

    return 0;
}

Node* LinkedList::find_merge_node(Node* head_a, Node* head_b) {
    int merge_node_index = 1;
    Node* itr_one = head_a;
    Node* itr_two = head_b;
    while (itr_one != nullptr) {
        while (itr_two->next_ != nullptr) {
            if (itr_two->next_ == itr_one) {
                return itr_one;
            }
            itr_two = itr_two->next_;
        }
        itr_one = itr_one->next_;
        itr_two = head_b;
        ++merge_node_index;
    }

    return nullptr;
}

Node* LinkedList::get_head() { return head_; }

Node* LinkedList::get_tail() { return tail_; }

int LinkedList::get_size() { return size_; }

void LinkedList::print() {
    Node* itr = head_;
    for (int i = 0; i < size_; ++i) {
        cout << itr->data_;
        itr = itr->next_;
        if (i < size_ - 1)
            cout << ", ";
    }
    cout << endl;
}

void LinkedList::print_reverse() {}
