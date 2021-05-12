#ifndef AVLTREE_H
#define AVLTREE_H
#include "Node.h"

using namespace std;

class AVLTree {

    public:
        AVLTree(){};
        void insert(const string&); //done
        int balanceFactor(Node*); //done
        void printBalanceFactors();
        void visualizeTree(const string&); //done

    private:
        Node* root = nullptr;
        void visualizeTree(ofstream &, Node*); //done
        void rotateRight(Node*); //done
        void rotateLeft(Node*); //done
        int findHeight(Node *) const; //done
        int height(Node*) const; //done
        void inOrder(Node* start); //done


};




#endif