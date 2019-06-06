//
// Created by huangzp on 4/23/19.
//

#include <assert.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "DataStructure.h"


template<class T>
RedBlackTree<T>::RedBlackTree() {
    this->nil = new Node<T>();
    this->root = this->nil;
}

template<class T>
RedBlackTree<T>::~RedBlackTree() {
    this->destroy();
}

template<class T>
void RedBlackTree<T>::destroy() {
    this->clear(this->root);
    delete this->nil;
}

template<class T>
void RedBlackTree<T>::clear(Node<T> *x) {
    if(x == this->nil){
        return;
    }
    clear(x->left);
    clear(x->right);
    delete x;
}

template<class T>
boolean RedBlackTree<T>::isCorrect() {
    boolean flag1 = true;
    boolean flag2 = true;
    boolean flag3 = true;
    boolean flag4 = true;
    boolean flag5 = true;
    // 判断根节点是否是黑色的
    flag2 = (this->root->color == BLACK);
    // 判断是否所有的叶子节点都是黑色的
    flag3 = isAllLeavesAreBlack(this->root, this->nil);
    // 判断红色节点的孩子节点都是 黑色的
    flag4 = isAllRedFatherBlack(this->root, this->nil);
    // 判断每个节点到其所有的叶子节点的路径中的黑色节点想同
    flag5 = isAllBlackHightTheSame(this->root, this->nil);
    return flag1 && flag2 && flag3 && flag4;
}

template <class T>
boolean isAllBlackHightTheSame(Node<T> *x, Node<T> *nil) {
    if(x == nil){
        return true;
    }
    boolean tmp1 = isAllBlackHightTheSame(x->left, nil);
    int h1 = getBlackHight(x->left, nil);
    boolean tmp2 = isAllBlackHightTheSame(x->right, nil);
    int h2 = getBlackHight(x->right, nil);
    return tmp1 && tmp2 && (h1 == h2);
}

template <class T>
int getBlackHight(Node<T> *x, Node<T> *nil) {
    if(x == nil){
        return 1;
    }
    int h1 = getBlackHight(x->left, nil);
    int h2 = getBlackHight(x->right, nil);
    if(h1 != h2){
        return 0;
    }
    if(x->color == BLACK){
        return h1 + 1;
    }
    else{
        return h1;
    }
}

template<class T>
boolean isAllLeavesAreBlack(Node<T>* x, Node<T> *nil){
    boolean tmp1, tmp2;
    if(x == nil){
        return x->color == BLACK;
    }
    tmp1 = isAllLeavesAreBlack(x->left, nil);
    tmp2 = isAllLeavesAreBlack(x->right, nil);
    return tmp1 && tmp2;
}

template <class T>
boolean isAllRedFatherBlack(Node<T> *x, Node<T> *nil) {
    boolean tmp1 = true;
    boolean tmp2 = true;
    boolean tmp3 = true;
    if(x == nil) {
        // nil 节点
        return true;
    }
    if(x->color == RED){
        tmp1 = ((x->left->color == BLACK) && (x->right->color == BLACK));
    }
    tmp2 = isAllRedFatherBlack(x->left, nil);
    tmp3 = isAllRedFatherBlack(x->right, nil);
    return tmp1 && tmp2 && tmp3;
}


template<class T>
void RedBlackTree<T>::leftRotation(Node<T> *x) {
    Node<T>* y = x->right;
    if(y == this->nil){
        return;
    }
    x->right = y->left; y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == this->nil) {
        // 说明x是root 节点
        this->root = y;
    }
    else{
        if(x == x->parent->left){
            // x 在左边
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
    }
    y->left = x; x->parent = y;
}

template<class T>
void RedBlackTree<T>::rightRotation(Node<T> *x) {
    Node<T>* y = x->left;
    if(y == this->nil){
        return;
    }
    x->left = y->right; y->right->parent = x;
    y->parent = x->parent;
    if(x->parent == this->nil){
        this->root = y;
    }
    else{
        if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
    }
    y->right = x; x->parent = y;
}

template<class T>
Node<T> *RedBlackTree<T>::successor(Node <T> *x) {
    if(x == this->nil){
        return nullptr;
    }
    Node<T>* right = x->right;
    if(right != this->nil) {
        // 右边的子树不为空
        Node<T> *result = right;
        while (result->left != this->nil) {
            result = result->left;
        }
        return result;
    }
    else {
        // 右边的子树为空
        Node<T> *tmp = x;
        Node<T> *result = x->parent;
        while(result->right == tmp && result != this->nil) {
            tmp = result;
            result = result->parent;
        }
        return result;
    }
}

template<class T>
Node<T> *RedBlackTree<T>::predecessor(Node<T> *x) {
    if(x == this->nil){
        return nullptr;
    }
    Node<T>* left = x->left;
    if(left != this->nil) {
        // 右边的子树不为空
        Node<T> *result = left;
        while (result->right != this->nil) {
            result = result->right;
        }
        return result;
    }
    else {
        // 右边的子树为空
        Node<T> *tmp = x;
        Node<T> *result = x->parent;
        while(result->left == tmp && result != this->nil) {
            tmp = result;
            result = result->parent;
        }
        return result;
    }
}

template<class T>
boolean RedBlackTree<T>::insert(T key) {
    auto* newNode = new Node<T>(nullptr, nullptr, RED, key, nullptr);
    Node<T>* y = this->nil;
    Node<T>* x = this->root;
    while(x != this->nil) {
        y = x;
        if(key < x->key){
            x = x->left;
        }
        else if(key > x->key) {
            x = x->right;
        }
        else {
            std::cout << "there is a conflict! please check it out" << std::endl;
            return false;
        }
    }
    newNode->parent = y;
    if(y == this->nil){
        // 插入的是空疏
        this->root = newNode;
    }
    else {
        // 插入的不是空树
        newNode->parent = y;
        if(key < y->key) {
            // 插入左边
            y->left = newNode;
        }
        else if(key > y -> key){
            // 插入右边
            y->right = newNode;
        }
        else{
            std::cout << "there is a conflict! please check it out" << std::endl;
            return false;
        }
    }
    newNode->left = this->nil;
    newNode->right = this->nil;
    newNode->color = RED;
    InsertFixUp(newNode, this);
    return true;
}

template <class T>
void InsertFixUp(Node<T> * z, RedBlackTree<T>* tree) {
    if(z->parent == tree->nil) {
        z->color = BLACK;
        return;
    }
    while(z->parent->color == RED){
        if(z->parent == z->parent->parent->left){
            // case1, 2, 3
            Node<T>* uncle = z->parent->parent->right;
            if(uncle -> color == RED){
                // case
                z->parent->parent->color = RED;
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->color = RED;
                z = z->parent->parent;
                assert(z->color == RED);
            }
            else {
                // case2, 3
                if(z->parent->right == z) {
                    // case2
                    z = z->parent;
                    tree->leftRotation(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                assert(z->color == RED);
                tree->rightRotation(z->parent->parent);
                assert(z->parent->color == BLACK);
            }
            // end
        }
        else {
            // case 4,5,6
            Node<T>* uncle = z->parent->parent->left;
            if(uncle->color == RED){
                // case 4
                z->parent->parent->color = RED;
                uncle->color = BLACK;
                z->parent->color = BLACK;
                z = z->parent->parent;
            }
            else {
                // case 5, 6
                if(z->parent->left == z){
                    // case 5
                    z = z->parent;
                    tree->rightRotation(z);
                }
                // case 6
                z->parent->parent->color = RED;
                z->parent->color = BLACK;
                assert(z->color == RED);
                tree->leftRotation(z->parent->parent);
                assert(z->parent->color == BLACK);
                // end
            }
        }
    }
    tree->root->color = BLACK;
}

template<class T>
boolean RedBlackTree<T>::remove(T key) {
    Node<T>* z = this->search(key);
    if(!z){
        cout << "没找到" << endl;
        return false;
    }
    Node<T> *x, *y;
    if(z->left == this->nil || z->right == this->nil) {
        // case 1, 2
        y = z;
    }
    else {
        // case 3
        y = this->successor(z);
    }
    if(y->left != this->nil) {
        x = y->left;
    }
    else {
        x = y->right;
    }
    x->parent = y->parent;
    if(y->parent == this->nil) {
        this->root = x;
    }
    else{
        if(y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }
    }
    if(y != z){
        z->color = y->color;
        z->key = y->key;
    }
    if(y->color == BLACK){
        deleteFixUp(x, this);
    }
    delete y;
    return true;
}


template <class T>
void deleteFixUp(Node<T> *x, RedBlackTree<T>* tree){
    // 缩进好像有问题
    Node<T>* w;
    while(x != tree->root && x->color == BLACK){
        if(x == x->parent->left){
            w = x->parent->right;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                tree->leftRotation(x->parent);
                w = x->parent->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }
            else if(w->right->color == BLACK){
                w->left->color = BLACK;
                w->color = RED;
                tree->rightRotation(w);
                w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            tree->leftRotation(x->parent);
            x = tree->root;
        }
        else{
            w = x->parent->right;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                tree->rightRotation(x->parent);
                w = x->parent->right;
            }
            if(w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }
            else if(w->right->color == BLACK){
                w->right->color = BLACK;
                w->color = RED;
                tree->rightRotation(w);
                w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            tree->rightRotation(x->parent);
            x = tree->root;
        }
    }
    x->color = BLACK;
}



template<class T>
void RedBlackTree<T>::print() {
    cout << "============文字版递归红黑树=============" << endl;
    printRecursive(this->root, this->nil, this->root->key, 0);
    cout << "============文字版层序红黑树=============" << endl;
    printLevel(this->root, this->nil);
    cout << "============图形版红黑树=============" << endl;
    printPretty("", this->root, false, this->nil);
}

template <class T>
void printLevel(Node<T>* z, Node<T>* nil){
    vector<Node<T>*> queue = vector<Node<T>*>();
    Node<T> *tmp;
    queue.push_back(z);
    while(!queue.empty()){
        tmp = queue[0];
        queue.erase(queue.begin());
        cout << tmp->key << endl;
        if(tmp->left != nil)
            queue.push_back(tmp->left);
        if(tmp->right != nil)
            queue.push_back(tmp->right);
    }
}

template <class T>
void printPretty(const std::string& prefix, Node<T>* node, bool isLeft, Node<T>* nil)
{
    if( node != nil )
    {
        string mark = node->color == BLACK ? "◆" : "◇";
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->key << mark << std::endl;

        // enter the next tree level - left and right branch
        printPretty( prefix + (isLeft ? "│   " : "    "), node->left, true, nil);
        printPretty( prefix + (isLeft ? "│   " : "    "), node->right, false, nil);
    }
}

template<class T>
void printRecursive(Node<T>* z, Node<T>* nil, T parentKey, int direction) {
    if(z != nil)
    {
        if(z->parent == nil)    // tree是根节点
                std::cout << right << std::setw(12) << z->key << "(◆) is root" << std::endl;
        else                // tree是分支节点
            std::cout << right << std::setw(12) << z->key <<  (z->color == RED ? "(◇)":"(◆)") \
            << " is " << std::setw(12) << parentKey << "'s "  << std::setw(12) <<\
            (direction ==1 ?"right child" : "left child") << std::endl;

        printRecursive(z->left, nil, z->key, -1);
        printRecursive(z->right, nil, z->key,  1);
    }
}



template<class T>
Node<T> *RedBlackTree<T>::search(T key) {
    return searchRecursive(this->root, key, this->nil);
}

template<class T>
Node<T> *searchRecursive(Node<T>* x, T key, Node<T> * nil) {
    Node<T>* tmp1, *tmp2;
    if(x == nil){
        return nullptr;
    }
    if(x->key == key){
        // 找到了
        return x;
    }
    tmp1 = searchRecursive(x->left, key, nil);
    tmp2 = searchRecursive(x->right, key, nil);
    if(tmp1) return tmp1;
    if(tmp2) return tmp2;
    return nullptr;
}

template<class T>
T RedBlackTree<T>::minimum() {
    Node<T>* x = this->root;
    while(x->left != this->nil){
        x = x->left;
    }
    return x->key;
}

template<class T>
T RedBlackTree<T>::maximum() {
    Node<T>* x = this->root;
    while(x->right != this->nil){
        x = x->right;
    }
    return x->key;
}

template<class T>
void RedBlackTree<T>::inOrder(Node<T>* x) {
    if(x == this->nil) {
        return;
    }
    inOrder(x->left);
    std::cout << x->key <<std::endl;
    inOrder(x->right);
}

template<class T>
void RedBlackTree<T>::range(T min, T max) {
    rangeRecursive(this->root, min, max, this->nil);
}

void searchNameRecursive(Node<Course<int>> *x, Course<int> key, Node<Course<int>>* nil) {
    if(x == nil){
        return;
    }
    searchNameRecursive(x->left, key, nil);
    if(x->key.name == key.name){
        cout << x->key << endl;
    }
    searchNameRecursive(x->right, key, nil);
}

template<> void RedBlackTree<Course<int>>::searchName(Course<int> key) {
    searchNameRecursive(this->root, key, this->nil);
}




template <class T>
void rangeRecursive(Node<T>* x, T min, T max, Node<T>* nil){
    if(x == nil){
        return;
    }
    rangeRecursive(x->left, min, max, nil);
    if(x->key > min && x->key < max) {
        cout << x->key << endl;
    }
    rangeRecursive(x->right, min, max, nil);
}


// 实例化模板类
template class RedBlackTree<int>;
template class Course<int>;
template class RedBlackTree<Course<int>>;