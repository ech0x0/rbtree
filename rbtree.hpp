#pragma once
#ifndef RBT_HPP
#define RBT_HPP

template <class T>
struct RBNode {
    RBNode<T>* parent;
    RBNode<T>* left;
    RBNode<T>* right;
    // 0 -> black, 1 -> red
    char color;
    T data;

    RBNode();
    RBNode(RBNode<T>* iParent, RBNode<T>* iLeft, RBNode<T>* iRight, char iColor, T iData);
    ~RBNode();
};

template <class T>
class RBTree {
private:
    RBNode<T>* root;

    void fixTreeAfterInsert(RBNode<T>* node);
    void fixTreeAfterRemove(RBNode<T>* node);
    // set node x to y in x's parent pointers
    void updateNodeParent(RBNode<T>* x, RBNode<T>* y);
public:
    RBTree();
    ~RBTree();

    RBNode<T>* getRoot() const;

    void insert(T data);
    void remove(RBNode<T>* node);

    RBNode<T>* searchFromNode(RBNode<T>* node, T data) const;
    RBNode<T>* search(T data) const;

    void preorder(RBNode<T>* node, void (*func)(RBNode<T>* x));
    void inorder(RBNode<T>* node, void (*func)(RBNode<T>* x));
    void postorder(RBNode<T>* node, void (*func)(RBNode<T>* x));

    RBNode<T>* minimum(RBNode<T>* node) const;
    RBNode<T>* maximum(RBNode<T>* node) const;

    void leftRotate(RBNode<T>* node);
    void rightRotate(RBNode<T>* node);
};

template <class T>
inline RBNode<T>::RBNode()
    : data() {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = 0;
}

template <class T>
inline RBNode<T>::RBNode(RBNode<T>* iParent, RBNode<T>* iLeft, RBNode<T>* iRight, char iColor, T iData)
    : data(iData) {
    parent = iParent;
    left = iLeft;
    right = iRight;
    color = iColor;
}

template <class T>
inline RBNode<T>::~RBNode() {
    if (left) delete left;
    if (right) delete right;
}

template <class T>
inline void RBTree<T>::fixTreeAfterInsert(RBNode<T>* node) {
    RBNode<T>* x;

    while (node->parent->color == 1) {
        if (node->parent == node->parent->parent->right) {
            x = node->parent->parent->left;

            if (x != nullptr && x->color == 1) {
                x->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;

                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }

                node->parent->color = 0;
                node->parent->parent->color = 1;

                leftRotate(node->parent->parent);
            }
        } else {
            x = node->parent->parent->right;

            if (x != nullptr && x->color == 1) {
                x->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;

                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;

                rightRotate(node->parent->parent);
            }
        }
        if (node == root || node->parent == root) {
            break;
        }
    }
}

template <class T>
inline void RBTree<T>::fixTreeAfterRemove(RBNode<T>* node) {
    RBNode<T>* x;
    while (node != root && node->color == 0) {
        if (node == node->parent->left) {
            x = node->parent->right;
            if (x != nullptr && x->color == 1) {
                x->color = 0;
                node->parent->color = 1;
                leftRotate(node->parent);
                x = node->parent->right;
            }

            if (x != nullptr && (x->left == nullptr || x->left->color == 0) && (x->right == nullptr || x->right->color == 0)) {
                x->color = 1;
                node = node->parent;
            } else {
                if (x && (x->right == nullptr || x->right->color == 0)) {
                    if (x->left) x->left->color = 0;
                    x->color = 1;
                    rightRotate(x);
                    x = node->parent->right;
                }

                if (x) x->color = node->parent->color;
                node->parent->color = 0;
                if (x && x->right) x->right->color = 0;
                leftRotate(node->parent);
                node = root;
            }
        } else {
            x = node->parent->left;
            if (x != nullptr && x->color == 1) {
                x->color = 0;
                node->parent->color = 1;
                rightRotate(node->parent);
                x = node->parent->left;
            }

            if (x != nullptr && (x->left == nullptr || x->left->color == 0) && (x->right == nullptr || x->right->color == 0)) {
                x->color = 1;
                node = node->parent;
            } else {
                if (x != nullptr && x->left != nullptr && x->left->color == 0) {
                    if (x->right) x->right->color = 0;
                    x->color = 1;
                    leftRotate(x);
                    x = node->parent->left;
                }

                if (x) x->color = node->parent->color;
                node->parent->color = 0;
                if (x && x->left) x->left->color = 0;
                rightRotate(node->parent);
                node = root;
            }
        }
    }
    node->color = 0;
}

template <class T>
inline void RBTree<T>::updateNodeParent(RBNode<T>* x, RBNode<T>* y) {
    if (x == nullptr) return;

    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    if (y != nullptr) y->parent = x->parent;
}

template <class T>
inline RBTree<T>::RBTree() {
    root = nullptr;
}

template <class T>
inline RBTree<T>::~RBTree() {
    if (root) delete root;
}

template <class T>
inline RBNode<T>* RBTree<T>::getRoot() const {
    return root;
}

template <class T>
inline void RBTree<T>::insert(T data) {
    RBNode<T>* y = nullptr;
    RBNode<T>* x = this->root;
    while (x != nullptr) {
        y = x;
        if (data == x->data) return;
        else if (data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    RBNode<T>* node = new RBNode<T>();
    node->parent = nullptr;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 1;

    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
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

template <class T>
inline void RBTree<T>::remove(RBNode<T>* node) {
    if (node == nullptr) return;

    RBNode<T>* x;
    char originalColor = node->color;

    if (node->left == nullptr && node->right == nullptr) {
        x = node->parent;
        updateNodeParent(node, nullptr);
    } else if (node->left == nullptr) {
        x = node->right;
        updateNodeParent(node, node->right);
    } else if (node->right == nullptr) {
        x = node->left;
        updateNodeParent(node, node->left);
    } else {
        RBNode<T>* y = minimum(node->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == node) {
            if (x) x->parent = y;
        } else {
            updateNodeParent(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }

        updateNodeParent(node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }

    node->left = nullptr;
    node->right = nullptr;
    delete node;

    if (originalColor == 0) {
        if (x) fixTreeAfterRemove(x);
    }
}

template <class T>
inline RBNode<T>* RBTree<T>::searchFromNode(RBNode<T>* node, T data) const {
    if (node == nullptr || node->data == data) return node;

    if (data < node->data) return searchFromNode(node->left, data);
    return searchFromNode(node->right, data);
}

template <class T>
inline RBNode<T>* RBTree<T>::search(T data) const {
    return searchFromNode(root, data);
}

template <class T>
inline void RBTree<T>::preorder(RBNode<T>* node, void (*func)(RBNode<T>* x)) {
    if (node != nullptr) {
        func(node);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

template <class T>
inline void RBTree<T>::inorder(RBNode<T>* node, void (*func)(RBNode<T>* x)) {
    if (node != nullptr) {
        inorder(node->left, func);
        func(node);
        inorder(node->right, func);
    }
}

template <class T>
inline void RBTree<T>::postorder(RBNode<T>* node, void (*func)(RBNode<T>* x)) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node);
    }
}

template <class T>
inline RBNode<T>* RBTree<T>::minimum(RBNode<T>* node) const {
    RBNode<T>* x = node;
    while (x->left != nullptr) {
        x = x->left;
    }
    return x;
}

template <class T>
inline RBNode<T>* RBTree<T>::maximum(RBNode<T>* node) const {
    RBNode<T>* x = node;
    while (x->right != nullptr) {
        x = x->right;
    }
    return x;
}

template <class T>
inline void RBTree<T>::leftRotate(RBNode<T>* node) {
    if (node->right == nullptr) return;

    RBNode<T>* x = node->right;
    node->right = x->left;

    if (x->left != nullptr) {
        x->left->parent = node;
    }

    x->parent = node->parent;

    if (node->parent == nullptr) {
        this->root = x;
    } else if (node == node->parent->left) {
        node->parent->left = x;
    } else {
        node->parent->right = x;
    }

    x->left = node;
    node->parent = x;
}

template <class T>
inline void RBTree<T>::rightRotate(RBNode<T>* node) {
    if (node->left == nullptr) return;

    RBNode<T>* x = node->left;
    node->left = x->right;

    if (x->right != nullptr) {
        x->right->parent = node;
    }

    x->parent = node->parent;

    if (node->parent == nullptr) {
        this->root = x;
    } else if (node == node->parent->right) {
        node->parent->right = x;
    } else {
        node->parent->left = x;
    }

    x->right = node;
    node->parent = x;
}

#endif
