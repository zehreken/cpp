#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

struct Node
{
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val):prev(p), next(n), key(k), value(val){};
    Node(int k, int val):prev(nullptr), next(nullptr), key(k), value(val){};
};

class Cache
{
protected:
    map<int, Node*> mp; // map the key to the node in the linked list
    int cp; // capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; // set function
    virtual int get(int) = 0; // get function
};

class LRUCache : public Cache
{
public:
    LRUCache(int capacity)
    {
        cp = capacity;
        Node* head = new Node(1, 0);
        tail = head;
    }

    void set(int key, int value)
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->key == key) break;
            temp = temp->next;
        }
    }

    int get(int)
    {
        return 0;
    }
};

int main()
{
    int n;
    int capacity;
    int i;
    cin >> n >> capacity;
    LRUCache l(capacity);

    for (i = 0; i < n; i++)
    {
        string command;
        cin >> command;
        if (command == "get")
        {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        }
        else if (command == "set")
        {
            int key;
            int value;
            cin >> key >> value;
            l.set(key, value);
        }
    }

    return 0;
}
