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
class RBTree {
private:
    Node<T>* root;

    void fixTreeAfterInsert(Node<T>* node);
public:
    RBTree();
    ~RBTree();

    Node<T>* getRoot() const;

    void insert(T data);
    void remove(T data);

    Node<T>* searchFromNode(Node<T>* node, T data) const;
    Node<T>* search(T data) const;

    void preorder(Node<T>* node, void (*func)(Node<T>* x));
    void inorder(Node<T>* node, void (*func)(Node<T>* x));
    void postorder(Node<T>* node, void (*func)(Node<T>* x));

    Node<T>* minimum(Node<T>* node) const;
    Node<T>* maximum(Node<T>* node) const;

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
inline void RBTree<T>::fixTreeAfterInsert(Node<T>* node) {
    Node<T>* x;

    while (node->parent->color == 1) {
        if (node->parent == node->parent->parent->right) {
            x = node->parent->parent->left;

            if (x != nullptr && x->color == 1) {
                x->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;

                node = node->parent->parent;
            }
            else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }

                node->parent->color = 0;
                node->parent->parent->color = 1;

                leftRotate(node->parent->parent);
            }
        }
        else {
            x = node->parent->parent->right;

            if (x != nullptr && x->color == 1) {
                x->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;

                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;

                rightRotate(node->parent->parent);
            }
        }
        if (node == root) {
            break;
        }
    }
}

template<class T>
inline RBTree<T>::RBTree() {
    root = nullptr;
}

template<class T>
inline RBTree<T>::~RBTree() {
    if (root) delete root;
}

template<class T>
inline Node<T>* RBTree<T>::getRoot() const {
    return root;
}

template<class T>
inline void RBTree<T>::insert(T data) {
    Node<T>* node = new Node<T>();
    node->parent = nullptr;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 1;

    Node<T>* y = nullptr;
    Node<T>* x = this->root;

    while (x != nullptr) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    }
    else if (node->data < y->data) {
        y->left = node;
    }
    else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->color = 0;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    fixTreeAfterInsert(node);
}

template<class T>
inline void RBTree<T>::remove(T data) {
}

template<class T>
inline Node<T>* RBTree<T>::searchFromNode(Node<T>* node, T data) const {
    if (node == nullptr || node->data == data) return node;

    if (data < node->data) return searchFromNode(node->left, data);
    return searchFromNode(node->right, data);
}

template<class T>
inline Node<T>* RBTree<T>::search(T data) const {
    return searchFromNode(root, data);
}

template<class T>
inline void RBTree<T>::preorder(Node<T>* node, void(*func)(Node<T>* x)) {
    if (node != nullptr) {
        func(node);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

template<class T>
inline void RBTree<T>::inorder(Node<T>* node, void(*func)(Node<T>* x)) {
    if (node != nullptr) {
        inorder(node->left, func);
        func(node);
        inorder(node->right, func);
    }
}

template<class T>
inline void RBTree<T>::postorder(Node<T>* node, void(*func)(Node<T>* x)) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node);
    }
}

template<class T>
inline Node<T>* RBTree<T>::minimum(Node<T>* node) const {
    Node<T>* x = node;
    while (x->left != nullptr) {
        x = x->left;
    }
    return x;
}

template<class T>
inline Node<T>* RBTree<T>::maximum(Node<T>* node) const {
    Node<T>* x = node;
    while (x->right != nullptr) {
        x = x->right;
    }
    return x;
}

template<class T>
inline void RBTree<T>::leftRotate(Node<T>* node) {
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
inline void RBTree<T>::rightRotate(Node<T>* node) {
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
