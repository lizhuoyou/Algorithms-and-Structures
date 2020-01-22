#include <iostream>
using namespace std;

struct lnode{
    struct lnode *pre, *next;
    int value;
};

class llist{
private:
    lnode *head, *tail;
public:
    llist(){
        head = NULL;
        tail = NULL;
    }

    void enqueue(int value){
        // add to the tail
        lnode *node = new lnode;
        node->value = value;
        node->next = NULL;
        if(head != NULL){
            node->pre = tail;
            tail->next = node;
            tail = node;
        } else{
            node->pre = NULL;
            head = node;
            tail = node;
        }
    }

    void pushHead(int value){
        // add to the head
        lnode *node = new lnode;
        node->value = value;
        node->pre = NULL;
        if(head != NULL){
            node->next = head;
            head->pre = node;
            head = node;
        } else{
            node->pre = NULL;
            head = node;
            tail = node;
        }
    }

    int dequeue(){
        // remove the head
        if(head != NULL){
            lnode *tmp;
            tmp = head;
            int ans = head->value;
            head = head->next;
            if(head != NULL){
                head->pre = NULL;
            } else{
                tail = NULL;
            }
            delete tmp;
            return ans;
        } else {
            cerr << "No more nodes!" << endl;
        }
    }

    int pop(){
        // remove the tail
        if(tail != NULL){
            lnode *tmp;
            tmp = tail;
            int ans = tail->value;
            tail = tail->pre;
            if (tail != NULL) {
                tail->next = NULL;
            } else {
                head = NULL;
            }
            delete tmp;
            return ans;
        } else {
            cerr << "No more nodes!" << endl;
        }
    }
};

int main(){
    llist ll = llist();
    ll.enqueue(1);
    ll.enqueue(2);
    ll.enqueue(3);
    ll.enqueue(4);
    ll.pushHead(0);
    cout << ll.dequeue() << endl << ll.pop() << endl << ll.dequeue() << endl << ll.pop() << endl << ll.dequeue()
         << endl;
    return 0;
};