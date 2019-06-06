//
// Created by huangzp on 4/23/19.
//
#include <jmorecfg.h>

#ifndef LAB2_DATASTRUCTURE_H
#define LAB2_DATASTRUCTURE_H

using namespace std;
template <class D>
class Course
{
public:
    string name;
    D min;
    D max;
    Course() {
        this->name = "";
        this->min = 0;
        this->max = 0;
    }

    Course(const string& name, D min, D max) {
        if(min > max){
            cout << "时间数组输入错误" << endl;
            return;
        }
        this->name = name;
        this->min = min;
        this->max = max;

    }

    boolean operator<(const Course<D> &b) {
        return this->max <= b.min;
    }

    boolean operator>(const Course<D> &b) {
        return this->min >= b.max;
    }

    boolean operator==(const Course<D> &b) {
        return (this->name == b.name) && (this->min == b.min) && (this->max == b.max);
    }

    void operator|(Course<D> &b) {
        D tmpMin = b.min;
        D tmpMax = b.max;
        b.min = this->min;
        b.max = this->max;
        this->min = tmpMin;
        this->max = tmpMax;
    }

    /*
    Course();
    Course(string name, D min, D max);
    ~Course();
    boolean operator<(const Course<D> &b);
    boolean operator>(const Course<D> &b);
    boolean operator==(const Course<D> &b);
    friend ostream & operator << (ostream &output, Course &c);
    friend istream & operator >> (istream &input , Course &c);
    void operator|(Course<D> &b);
    void show();
     */
};

template<class D>
ostream & operator<<(ostream &output, Course<D> &c) {


    return output;
}

template<class D>
istream & operator>>(istream &input, Course<D> &c) {
    input >> c.name >> c.min >> c.max;
    return input;
}


enum RBTColor{RED, BLACK};

template <class T>
class Node
{
public:
    Node* parent;
    Node* left;
    RBTColor color;
    T key;
    Node* right;

    Node(Node* parent, Node* left, RBTColor color, T key, Node* right){
        this->parent = parent;
        this->left = left;
        this->color = color;
        this->key = key;
        this->right = right;
    }

    Node() {
        // generate a nil Node
        this->parent = this;
        this->left = this;
        this->color = BLACK;
        this->right = this;
    }

};


template <class T>
class RedBlackTree
{
private:
public:
    Node<T>* root;
    Node<T>* nil;
    // 构造函数
    RedBlackTree();

    // 析构函数
    ~RedBlackTree();

    // 判断是否是红黑树
    boolean isCorrect();



    // 左旋
    void leftRotation(Node<T> *x);

    // 右旋
    void rightRotation(Node<T> *x);

    // 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
    Node<T>* successor(Node<T> *x);
    // 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
    Node<T>* predecessor(Node<T> *x);

    // 将结点(key为节点键值)插入到红黑树中
    boolean insert(T key);

    // 删除结点(key为节点键值)
    boolean remove(T key);

    // 销毁红黑树
    void destroy();

    // 打印红黑树
    void print();

    // 销毁子树
    void clear(Node<T>* x);

    // 中序遍历"红黑树"
    void inOrder(Node<T>* x);

    // (递归实现)查找"红黑树"中键值为key的节点
    Node<T>* search(T key);


    // 按照名字搜索 只用在 课程上
    void searchName(Course<int> key);

    // 查找最小结点：返回最小结点的键值。
    T minimum();

    // 查找最大结点：返回最大结点的键值。
    T maximum();

    // 查找范围
    void range(T min, T max);

};

#endif //LAB2_DATASTRUCTURE_H
