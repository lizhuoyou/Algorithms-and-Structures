#include <iostream>
#include <string>
using namespace std;

struct bNode{
    bNode *left, *right;
    int val;
};

class bTree{
    bNode *root;
    void addInto(int num, bNode *node){
        if (num > node->val) {
            if (node->right == nullptr) {
                bNode *nNode = new bNode;
                nNode->val = num;
                nNode->left = nullptr;
                nNode->right = nullptr;
                node->right = nNode;
            } else {
                addInto(num, node->right);
            }
        } else {
            if (node->left == nullptr) {
                bNode *nNode = new bNode;
                nNode->val = num;
                nNode->left = nullptr;
                nNode->right = nullptr;
                node->left = nNode;
            } else {
                addInto(num, node->left);
            }
        }
    }

    string branchString(bNode *node){
        if(node == nullptr){
            return "";
        } else {
            return branchString(node->left) + to_string(node->val) + ", " + branchString(node->right);
        }
    }

    void addNode(bNode *node){
        if (node != NULL) {
            add(node->val);
            addNode(node->left);
            addNode(node->right);
        }
    }

    void deleteLeafPlus(int num, bNode *node, bNode *preNode){
        if (node != nullptr) {
            if(node->val==num){
                if(preNode == nullptr){
                    delete root;
                    root = nullptr;
                }
                bNode *nodeRight = node->right;
                bNode *nodeLeft = node->left;
                delete node;
                if(preNode->val < num){
                    preNode->right = NULL;
                } else {
                    preNode->left = NULL;
                }
                if(nodeRight != nullptr){
                    addNode(nodeRight);
                }
                if(nodeLeft != nullptr){
                    addNode(nodeLeft);
                }
            } else if (num > node->val) {
                deleteLeafPlus(num, node->right, node);
            } else {
                deleteLeafPlus(num, node->left, node);
            }
        } else{
            cerr << "Error, no such value" << endl;
        }
    }
public:
    bTree(){
        root = nullptr;
    }

    string toString(){
        string ans = "[";
        ans += branchString(root);
        return ans.substr(0, ans.length() - 2) + "]";
    }

    void add(int num){
        if (root == nullptr) {
            root = new bNode;
            root->val = num;
            root->left = nullptr;
            root->right = nullptr;
        } else{
            addInto(num, root);
        }
    }

    int getLargestVal(){
        if (root != nullptr) {
            bNode *tmp = root;
            while (tmp->right != nullptr) tmp = tmp->right;
            return tmp->val;
        } else{
            cerr << "Error, no value." << endl;
            return -1;
        }
    }

    void deleteLargestVal(){
        if (root != nullptr) {
            bNode *tmp = root;
            while (tmp->right->right != nullptr) tmp = tmp->right;
            if(tmp->right->left != nullptr){
                bNode *largest = tmp->right;
                tmp->right = tmp->right->left;
                delete largest;
            } else{
                delete tmp->right;
                tmp->right = nullptr;
            }
        }
    }

    int getSmallestVal(){
        if (root != nullptr) {
            bNode *tmp = root;
            while (tmp->left != nullptr) tmp = tmp->left;
            return tmp->val;
        } else{
            cerr << "Error, no value." << endl;
            return -1;
        }
    }

    void deleteSmallestVal(){
        if (root != nullptr) {
            bNode *tmp = root;
            while (tmp->left->left != nullptr) tmp = tmp->left;
            if(tmp->right->right != nullptr){
                bNode *smallest = tmp->left;
                tmp->left = tmp->left->right;
                delete smallest;
            } else{
                delete tmp->right;
                tmp->right = nullptr;
            }
        }
    }

    void deleteLeaf(int num){
        deleteLeafPlus(num, root, NULL);
    }

    void comBine(bTree *bt){
        addNode(bt->root);
    }
};

int main(){
    bTree bt = bTree();
    bt.add(7);
    bt.add(1);
    bt.add(3);
    bt.add(2);
    bt.add(4);
    bt.add(6);
    bt.add(5);
    cout << bt.toString() << endl;

    bTree bt1 = bTree();
    bt1.add(10);
    bt1.add(9);
    bt1.add(11);
    bt1.add(8);
    bt1.add(12);
    bt1.add(13);
    bt1.add(14);
    bt.comBine(&bt1);
    cout << bt.toString() << endl;
    cout << bt.getLargestVal() << endl;
    cout << bt.getSmallestVal() << endl;
    bt.deleteLargestVal();
    bt.deleteSmallestVal();
    cout << bt.toString() << endl;
    bt.deleteLeaf(5);
    cout << bt.toString() << endl;
    return 0;
}