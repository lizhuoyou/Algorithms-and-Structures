// this linked list can be used as queue and stack.
#include <iostream>
#include <string>
using namespace std;

struct lnode{
    struct lnode *pre, *next;
    int value;
};

class llist{
    lnode *head, *tail;
public:
    llist(){
        head = nullptr;
        tail = nullptr;
    }

    ~llist(){
        lnode *tmp = head;
        while (tmp != nullptr) {
            lnode *n = tmp->next;
            delete tmp;
            tmp = n;
        }
    }

    string toString(){
        string ans = "[";
        lnode *tmp = head;
        while (tmp != nullptr) {
            ans += to_string(tmp->value);
            ans += ", ";
            tmp = tmp->next;
        }
        return ans.substr(0, ans.length() - 2) + "]";
    }

    void enqueue(int value){
        // add to the tail
        lnode *node = new lnode;
        node->value = value;
        node->next = nullptr;
        if(head != nullptr){
            node->pre = tail;
            tail->next = node;
            tail = node;
        } else{
            node->pre = nullptr;
            head = node;
            tail = node;
        }
    }

    void pushHead(int value){
        // add to the head
        lnode *node = new lnode;
        node->value = value;
        node->pre = nullptr;
        if(head != nullptr){
            node->next = head;
            head->pre = node;
            head = node;
        } else{
            node->next = nullptr;
            head = node;
            tail = node;
        }
    }

    int dequeue(){
        // remove the head
        if(head != nullptr){
            lnode *tmp;
            tmp = head;
            int ans = head->value;
            head = head->next;
            if(head != nullptr){
                head->pre = nullptr;
            } else{
                tail = nullptr;
            }
            delete tmp;
            return ans;
        } else {
            cerr << "Error, no more nodes!" << endl;
            return -1;
        }
    }


    int pop(){
        // remove the tail
        if(tail != nullptr){
            lnode *tmp;
            tmp = tail;
            int ans = tail->value;
            tail = tail->pre;
            if (tail != nullptr) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
            delete tmp;
            return ans;
        } else {
            cerr << "Error, no more nodes!" << endl;
            return -1;
        }
    }

    void reverse(){
        lnode *tmp = head;
        while (tmp != nullptr) {
            lnode *nNode = tmp->next;
            tmp->next = tmp->pre;
            tmp->pre = nNode;
            tmp = nNode;
        }
        lnode *oldHead = head;
        head = tail;
        tail = oldHead;
    }

    llist* clone(){
        llist *ans = new llist();
        lnode *h = head;
        while(h != nullptr){
            ans->enqueue(h->value);
            h = h->next;
        }
        return ans;
    }
};

int main(){
    llist ll = llist();
    ll.enqueue(1);
    ll.enqueue(2);
    ll.enqueue(3);
    ll.enqueue(4);
    ll.pushHead(0);
    llist ll2 = *ll.clone();
    cout << ll.dequeue() << endl << ll.pop() << endl << ll.dequeue() << endl << ll.pop() << endl << ll.dequeue()
         << endl;

    cout << ll2.dequeue() << " " << ll2.dequeue() << " " << ll2.dequeue() << " " << ll2.dequeue() << endl;

    ll.enqueue(1);
    ll.enqueue(2);
    ll.enqueue(3);
    ll.enqueue(4);
    ll.pushHead(0);
    ll.reverse();
    cout << ll.toString() << endl;
    cout << ll.dequeue() << " " << ll.dequeue() << " " << ll.dequeue() << " " << ll.dequeue() << endl;
    return 0;
};