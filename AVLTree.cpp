#include "AVLTree.h"

#include <fstream>
#include <iostream>

void AVLTree::insert(const string& newdata) {
    Node* newnode = new Node(newdata);
    if (root == nullptr) {  // case for empty Tree
        root = newnode;
        return;
    }
    Node* curr = root;
start:
    if (newdata == curr->getData()) {  // if data is identical
        curr->increaseCount();
        delete newnode;
        return;
    }
    // case for if newdata is larger than curr
    if (newdata > curr->getData()) {
        if (curr->getRightChild() != nullptr) {  //if its not the bottom of the tree yet
            curr = curr->getRightChild();
            goto start;
        } else {  // if it reached the bottom of the tree
            curr->setRightChild(newnode);
            newnode->setParent(curr);
            goto end;
        }
    }
    // case for if newdata is smaller than curr
    if (newdata < curr->getData()) {
        if (curr->getLeftChild() != nullptr) {
            curr = curr->getLeftChild();
            goto start;
        } else {
            curr->setLeftChild(newnode);
            newnode->setParent(curr);
            goto end;
        }
    }

end: //for the balancing part of the tree
    for (Node* newcurr = newnode->getParent(); newcurr != nullptr; newcurr = newcurr->getParent()){
        if (abs(balanceFactor(newcurr)) <= 1){ // check for balanced tree
            continue;
        }
        if (balanceFactor(newcurr) > 1){ //too many on left side
            if (balanceFactor(newcurr->getLeftChild()) == 1){
                rotateRight(newcurr);
                continue;
            }
            if (balanceFactor(newcurr->getLeftChild()) == -1){
                rotateLeft(newcurr->getLeftChild());
                rotateRight(newcurr);
                continue;
            }
        }
        if (balanceFactor(newcurr) < -1){ //too many on right side
            if (balanceFactor(newcurr->getRightChild()) == -1){
                rotateLeft(newcurr);
                continue;
            }
            if(balanceFactor(newcurr->getRightChild()) == 1){
                rotateRight(newcurr->getRightChild());
                rotateLeft(newcurr);
                continue;
            }
        }
    }
}

void AVLTree::inOrder(Node* start) {
    if (start == nullptr) {
        return;
    }
    inOrder(start->getLeftChild());
    cout << start->getData() << '(' << balanceFactor(start) << ')' << ", ";
    inOrder(start->getRightChild());
}

void AVLTree::printBalanceFactors(){
    return inOrder(root);
}

void AVLTree::rotateRight(Node* curr){
    Node* currchild = curr->getLeftChild();
    Node* currparent = curr->getParent();
    currchild->setRightChild(curr);
    currchild->setParent(currparent);
    if (curr == root){
        root = currchild;
    }
}

void AVLTree::rotateLeft(Node* curr){
    Node* currchild = curr->getRightChild();
    Node* currparent = curr->getParent();
    currchild->setLeftChild(curr);
    currchild->setParent(currparent);
    if (curr == root){
        root = currchild;
    }
}

int AVLTree::balanceFactor(Node* curr){
    if (curr == nullptr){return 0;}
    if (curr->hasChild() == false){
        return 0;
    }
    if (curr->getLeftChild() == nullptr){
        return (-1) * height(curr);
    }
    if (curr->getRightChild() == nullptr){
        return height(curr);
    }
    return height(curr->getLeftChild()) - height(curr->getRightChild());
}

int AVLTree::height(Node* curr) const {
    return findHeight(curr);
}

int larger(int one, int two){
    if (one > two){
        return one;
    } else {
        return two;
    }
}

int AVLTree::findHeight(Node* start) const {
    if (start == nullptr) {
        return 0;
    }
    if (start->hasChild() == false) {
        return 0;
    } else {
        return 1 + larger(findHeight(start->getLeftChild()), findHeight(start->getRightChild()));
    }
}


void AVLTree::visualizeTree(const string& outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open()) {
        cout << "Error" << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root);
    outFS << "}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream& outFS, Node* n) {
    if (n) {
        if (n->left()) {
            visualizeTree(outFS, n->left());
            outFS << n->getData() << " -> " << n->left()->getData() << ";" << endl;
        }

        if (n->right()) {
            visualizeTree(outFS, n->right());
            outFS << n->getData() << " -> " << n->right()->getData() << ";" << endl;
        }
    }
}