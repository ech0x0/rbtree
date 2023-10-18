#pragma once
#ifndef RBT_HPP
#define RBT_HPP

template<class T>
struct Node {
    Node* parent;
    Node* left;
    Node* right;
    //0 -> black, 1 -> red
    char color;
    T data;
};

template<class T>
class RBT {
private:
    Node<T>* root;
public:
    RBT();

    Node<T>* getRoot() const;

    void insert(T data);
    void remove(T data);
    Node<T>* search(T data) const;

    void leftRotate(Node<T>* node);
    void rightRotate(Node<T>* node);
};

#endif RBT_HPP