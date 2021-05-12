#include "AVLTree.h"
#include <fstream>
#include <iostream>


void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left()){
            visualizeTree(outFS,n->left());
            outFS<< n->getData() <<" -> " <<n->left()->getData()<<";"<<endl;    
        }

        if(n->right()){
            visualizeTree(outFS,n->right());
            outFS<<n->getData() <<" -> " <<n->right()->getData()<<";"<<endl;    
        }
    }
}




////////////////////////////////////
//            NODE STUFF          //
////////////////////////////////////

Node::Node() {
    rightChild = leftChild = parent = nullptr;
    data = "";
    count = 1;
}
Node::Node(string newdata) {
    this->data = newdata;
    rightChild = leftChild = parent = nullptr;
    count = 1;
}

string Node::getData() {
    return this->data;
}

Node* Node::getParent() {
    return this->parent;
}

Node* Node::getLeftChild() {
    return this->leftChild;
}

Node* Node::getRightChild() {
    return this->rightChild;
}

void Node::setData(string newdata) {
    this->data = newdata;
}

void Node::setParent(Node* newparent) {
    this->parent = newparent;
}

void Node::setLeftChild(Node* newleft) {
    this->leftChild = newleft;
    if (newleft == nullptr) {
        return;
    } else {
        newleft->parent = this;
    }
}

void Node::setRightChild(Node* newright) {
    this->rightChild = newright;
    if (newright == nullptr) {
        return;
    } else {
        newright->parent = this;
    }
}

bool Node::hasChild() {
    if (rightChild != nullptr or leftChild != nullptr) {
        return true;
    }
    return false;
}

int Node::getCount() {
    return count;
}

void Node::increaseCount() {
    count++;
}

void Node::decreaseCount() {
    count--;
}

bool Node::leftChildExists() {
    if (leftChild != nullptr) {
        return true;
    }

    return false;
}

bool Node::rightChildExists() {
    if (rightChild != nullptr) {
        return true;
    }

    return false;
}

void Node::setCount(int newCount) {
    this->count = newCount;
}