#pragma once

#include<memory>
#include<stdio.h>

using namespace std;

template <class T>
class BinaryTree {
public:
    typedef shared_ptr<BinaryTree<T>> TreePtr;

    TreePtr parent;
    TreePtr left;
    TreePtr right;
    BinaryTree<T>* PARENT;
    BinaryTree<T>* LEFT;
    BinaryTree<T>* RIGHT;

    T data;

    BinaryTree(const TreePtr _parent, const T _data);
    void insert(T _data);
    const TreePtr minimum();
    const TreePtr maximum();
    const TreePtr next();
    const TreePtr prev();
    void print();

    operator TreePtr();

};

template <class T> inline bool operator==(const typename BinaryTree<T>::TreePtr& lhs, const typename BinaryTree<T>::TreePtr& rhs){return lhs->data == rhs->data;}
template <class T> inline bool operator!=(const typename BinaryTree<T>::TreePtr& lhs, const typename BinaryTree<T>::TreePtr& rhs){return !operator==(lhs,rhs);}
template <class T> inline bool operator< (const typename BinaryTree<T>::TreePtr& lhs, const typename BinaryTree<T>::TreePtr& rhs){return lhs->data < rhs->data;}
template <class T> inline bool operator> (const typename BinaryTree<T>::TreePtr& lhs, const typename BinaryTree<T>::TreePtr& rhs){return  operator< (rhs,lhs);}
template <class T> inline bool operator<=(const typename BinaryTree<T>::TreePtr& lhs, const typename BinaryTree<T>::TreePtr& rhs){return !operator> (lhs,rhs);}
template <class T> inline bool operator>=(const typename BinaryTree<T>::TreePtr& lhs, const typename BinaryTree<T>::TreePtr& rhs){return !operator< (lhs,rhs);}

template <class T>
BinaryTree<T>::BinaryTree(const TreePtr _parent, const T _data)
:parent(_parent), left(nullptr), right(nullptr), PARENT(_parent.get()), LEFT(nullptr), RIGHT(nullptr), data(_data)
{}

template <class T>
void BinaryTree<T>::insert(T value) {
    // No duplicate entries
    if (value == data) {
        return;
    }

    if (value < data) {
        if (left == nullptr) {
            left = BinaryTree<T>(shared_ptr<BinaryTree<T>>(this), value);

        }else {
            left->insert(value);
        }

    }else {
        if (right == nullptr) {
            right = BinaryTree<T>(shared_ptr<BinaryTree<T>>(this), value);

        }else {
            right->insert(value);
        }
    }
}

template <class T>
BinaryTree<T>::operator TreePtr(){
    return TreePtr(this);
};

template <class T>
const typename BinaryTree<T>::TreePtr BinaryTree<T>::minimum() {
    if (left != nullptr) {
        return left->minimum();

    }else {
        return *this;
    }
}

template <class T>
const typename BinaryTree<T>::TreePtr BinaryTree<T>::maximum() {
    if (right != nullptr) {
        return right->minumum();

    }else {
        return *this;
    }
}


template <class T>
const typename BinaryTree<T>::TreePtr BinaryTree<T>::next() {
    if (right != nullptr) {
        return right->minimum();

    }else {

        TreePtr ancestor = shared_ptr<BinaryTree<T>>(this);
        TreePtr ancestorsParent = parent;

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

template <class T>
const typename BinaryTree<T>::TreePtr BinaryTree<T>::prev(){
}

template <class T>
void BinaryTree<T>::print()
{
    TreePtr node = minimum();

    while (node != nullptr) {
        printf("%d ", node->data);
        node = node->next();
    }
    printf("\n");
}














