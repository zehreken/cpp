#include "linked_list.hpp"
#include <iostream>
#include <set>

using namespace std;

LinkedList::LinkedList(int head_data) {
    head_ = new Node(head_data);
    head_->next_ = nullptr;
    tail_ = head_;
    tail_->next_ = nullptr;
    size_ = 1;
}

void LinkedList::push(int data) {
    Node* node = new Node(data);
    tail_->next_ = node;
    tail_ = node;
    size_ += 1;
}

bool LinkedList::pop(int& out) {
    if (size_ == 0) {
        out = -1;
        return false;
    }
    Node* itr = head_;
    Node* new_tail = nullptr;
    while (itr->next_ != nullptr) {
        new_tail = itr;
        itr = itr->next_;
    }
    out = tail_->data_;
    delete tail_;
    if (new_tail != nullptr) { // this is when there is 1 node
        tail_ = new_tail;
        tail_->next_ = nullptr;
    }
    size_ -= 1;

    return true;
}

void LinkedList::insert(int data, int index) {
    if (index < 0 || index >= size_) {
        cout << "EXCEPTION: illegal index value" << endl;
    } else if (index == 0) {
        Node* node = new Node(data);
        node->next_ = head_;
        head_ = node;
        size_ += 1;
    } else {
        Node* node = new Node(data);
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

bool LinkedList::remove(int index) {
    if (index < 0 || index >= size_) {
        cout << "EXCEPTION: Bad index value" << endl;
        return false;
    }
    if (size_ == 0) {
        cout << "EXCEPTION: No elements to remove" << endl;
        return false;
    }
    if (index == 0) {
        Node* new_head = head_->next_;
        delete head_;
        head_ = new_head;
        size_ -= 1;
    } else {
        Node* prev = nullptr;
        Node* itr = head_;
        int n = 0;
        while (itr != nullptr && n < index) {
            prev = itr;
            itr = itr->next_;
            n += 1;
        }
        prev->next_ = itr->next_;
        delete itr;
        size_ -= 1;
    }

    return true;
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

    Node* temp = new Node(0);
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

size_t LinkedList::get_size() { return size_; }

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
