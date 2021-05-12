#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>

using namespace std;

class AVLTree {

    public:
        void insert(const string&);
        int balanceFactor(Node*);
        void printBalanceFactors();
        void visualizeTree(const string&);

    private:
        Node* root = nullptr;
        void visualizeTree(ofstream &, Node*);


};


class Node {
   public:
    // Constructors
    Node();
    Node(string);

    //Accessors
    string getData();
    Node* getLeftChild();
    Node* left(){return leftChild;}
    Node* getRightChild();
    Node* right(){return rightChild;}
    Node* getParent();
    bool hasChild();
    bool leftChildExists();
    bool rightChildExists();
    int getCount();
    Node* findNode(const string&);

    //Mutators
    void setData(string);
    void setRightChild(Node*);
    void setLeftChild(Node*);
    void setParent(Node*);
    void setCount(int);
    void increaseCount();
    void decreaseCount();

   private:
    string data;
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    int count;
};

#endif