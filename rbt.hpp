#pragma once
#ifndef RBT_HPP
#define RBT_HPP

template<class T>
struct Node {
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;
    //0 -> black, 1 -> red
    char color;
    T data;

    Node();
    Node(Node<T>* iParent, Node<T>* iLeft, Node<T>* iRight, char iColor, T iData);
    ~Node();
};

template<class T>
class RBT {
private:
    Node<T>* root;
public:
    RBT();
    ~RBT();

    Node<T>* getRoot() const;

    void insert(T data);
    void remove(T data);
    Node<T>* search(T data) const;

    void leftRotate(Node<T>* node);
    void rightRotate(Node<T>* node);
};

template<class T>
inline Node<T>::Node() : data() {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = 0;
}

template<class T>
inline Node<T>::Node(Node<T>* iParent, Node<T>* iLeft, Node<T>* iRight, char iColor, T iData) : data(iData) {
    parent = iParent;
    left = iLeft;
    right = iRight;
    color = iColor;
}

template<class T>
inline Node<T>::~Node() {
    if (left) delete left;
    if (right) delete right;
}

template<class T>
inline RBT<T>::RBT() {
    root = new Node<T>();
}

template<class T>
inline RBT<T>::~RBT() {
    if (root) delete root;
}

template<class T>
inline Node<T>* RBT<T>::getRoot() const {
    return root;
}

template<class T>
inline void RBT<T>::insert(T data) {
}

template<class T>
inline void RBT<T>::remove(T data) {
}

template<class T>
inline Node<T>* RBT<T>::search(T data) const {
    return nullptr;
}

template<class T>
inline void RBT<T>::leftRotate(Node<T>* node) {
    Node<T>* x = node->right;
    node->right = x->left;

    if (x->left != nullptr) {
        x->left->parent = node;
    }

    x->parent = node->parent;

    if (node->parent == nullptr) {
        this->root = x;
    }
    else if (node == node->parent->left) {
        node->parent->left = x;
    }
    else {
        node->parent->right = x;
    }

    x->left = node;
    node->parent = x;
}

template<class T>
inline void RBT<T>::rightRotate(Node<T>* node) {
    Node<T>* x = node->left;
    node->left = x->right;

    if (x->right != nullptr) {
        x->right->parent = node;
    }

    x->parent = node->parent;

    if (node->parent == nullptr) {
        this->root = x;
    }
    else if (node == node->parent->right) {
        node->parent->right = x;
    }
    else {
        node->parent->left = x;
    }

    x->right = node;
    node->parent = x;
}

#endif
