#include "d_linked_list.hpp"
#include "linked_list.hpp"
#include <iostream>

/*
Node *newHead = NULL;
Node* recursiveReverse(Node *head)
{
    if (head->next != NULL)
    {
        Node *temp = recursiveReverse(head->next);
        temp->next = head;
        head->next = NULL;
        return temp->next;
    }
    else
    {
        newHead = head;
    }

    return newHead;
}
//*/

int main() {
    using namespace std;

    LinkedList ll(0);
    for (int i = 1; i < 10; ++i) {
        ll.push(i);
    }

    LinkedList cc(0);
    for (int i = 2; i < 20; i += 2) {
        cc.push(i);
    }

    ll.print();
    cc.print();

    // Node* merged_head = LinkedList::merge_sorted(ll.get_head(),
    // cc.get_head());
    // Node* itr = merged_head;
    // while (itr != nullptr) {
    //     cout << itr->data_ << ", ";
    //     itr = itr->next_;
    // }
    // cout << endl;

    // Node* temp = LinkedList::remove_duplicates(merged_head);
    // itr = temp;
    // cout << "duplicates removed" << endl;
    // while (itr != nullptr) {
    //     cout << itr->data_ << ", ";
    //     itr = itr->next_;
    // }
    // cout << endl;

    // ======= Doubly linked list
    DNode* head = new DNode();
    DNode* mid = new DNode();
    DNode* tail = new DNode();

    head->next_ = mid;
    mid->prev_ = head;
    mid->next_ = tail;
    tail->prev_ = mid;

    LinkedList dd(0);
    for (int i = 1; i < 10000; ++i) {
        dd.push(i);
    }
    // cout << LinkedList::has_cycle(dd.get_head()) << endl;

    return 0;
}
