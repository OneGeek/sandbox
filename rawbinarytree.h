#pragma once

#include "voronoi.h"

template <class T>
class RawBinaryTree {
public:
    RawBinaryTree<T>* parent;
    RawBinaryTree<T>* left;
    RawBinaryTree<T>* right;
    T value;

    RawBinaryTree(RawBinaryTree<T>* _parent, T _value);
    ~RawBinaryTree();
    void insert(T _value);
    RawBinaryTree<T>* minimum();
    RawBinaryTree<T>* next();
    void print();
};

template <class T> inline bool operator==(const RawBinaryTree<T>& lhs, const RawBinaryTree<T>& rhs){return lhs.data == rhs.data;}
template <class T> inline bool operator!=(const RawBinaryTree<T>& lhs, const RawBinaryTree<T>& rhs){return !operator==(lhs,rhs);}
template <class T> inline bool operator< (const RawBinaryTree<T>& lhs, const RawBinaryTree<T>& rhs){return lhs.data < rhs.data;}
template <class T> inline bool operator> (const RawBinaryTree<T>& lhs, const RawBinaryTree<T>& rhs){return  operator< (rhs,lhs);}
template <class T> inline bool operator<=(const RawBinaryTree<T>& lhs, const RawBinaryTree<T>& rhs){return !operator> (lhs,rhs);}
template <class T> inline bool operator>=(const RawBinaryTree<T>& lhs, const RawBinaryTree<T>& rhs){return !operator< (lhs,rhs);}



template <class T>
RawBinaryTree<T>::RawBinaryTree(RawBinaryTree<T>* _parent, T _value)
:parent(_parent), left(nullptr), right(nullptr), value(_value)
{}

template <class T>
RawBinaryTree<T>::~RawBinaryTree() {
    if (left != nullptr) {
        delete left;
    }

    if (right != nullptr) {
        delete right;
    }
}

template <class T>
void RawBinaryTree<T>::insert(T _value) {

    // No duplicate values
    if (_value == value) {
        return;
    }

    if (_value < value) {

        if (left == nullptr) {
            left = new RawBinaryTree(this, _value);

        }else {
            left->insert(_value);
        }

    }else {
        if (right == nullptr) {
            right = new RawBinaryTree(this, _value);

        }else {
            right->insert(_value);
        }
    }
}

template <class T>
RawBinaryTree<T>* RawBinaryTree<T>::minimum() {
    if (left == nullptr) {
        return this;
    }else {
        return left->minimum();
    }
}



template <class T>
RawBinaryTree<T>* RawBinaryTree<T>::next() {
    if (right != nullptr) {
        return right->minimum();

    }else {

        RawBinaryTree<T>* ancestor = this;
        RawBinaryTree<T>* ancestorsParent = parent;

        while (ancestorsParent != nullptr) {
            if (ancestorsParent->left == ancestor) {
                break;
            }

            ancestor = ancestorsParent;
            ancestorsParent = ancestorsParent->parent;
        }

        return ancestorsParent;
    }
}

template <>
void RawBinaryTree<Voronoi::SitePtr>::print();

template <class T>
void RawBinaryTree<T>::print() {

    RawBinaryTree<T>* node = minimum();

    while (node != nullptr) {
        printf("%d ", node->value);
        node = node->next();
    }
    printf("\n");
}

