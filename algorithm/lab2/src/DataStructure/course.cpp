//
// Created by huangzp on 4/23/19.
//

#include <iostream>
#include "DataStructure.h"

using namespace std;
/*
template<class D>
Course<D>::Course() {
    this->name = "";
    this->min = 0;
    this->max = 0;
}

template<class D>
Course<D>::Course(string name, D min, D max) {
    if(min >= max){
        cout << "时间数组输入错误" << endl;
        return;
    }
    this->name = name;
    this->min = min;
    this->max = max;

}

template<class D>
Course<D>::~Course() {
    delete this;
}

template<class D>
boolean Course<D>::operator<(const Course<D> &b) {
    return this->max <= b.min;
}

template<class D>
boolean Course<D>::operator>(const Course<D> &b) {
    return this->min >= b.max;
}


template<class D>
boolean Course<D>::operator==(const Course<D> &b) {
    return !((this->min >= b.max) && (this->max <= b.min));
}



template<class D>
void Course<D>::operator|(Course<D> &b) {
    D tmpMin = b.min;
    D tmpMax = b.max;
    b.min = this->min;
    b.max = this->max;
    this->min = tmpMin;
    this->max = tmpMax;
}


template<class D>
void Course<D>::show() {
    cout << "[" << this->min << ", " << this->max << "]" << endl;
}

template <class D>
ostream & operator<<(ostream &output, Course<D> &c) {
    output << c.name <<"("<<c.min<<", "<<c.max<<")"<<endl;
    return output;
}

template <class D>
istream & operator>>(istream &input, Course<D> &c) {
    input >> c.name >> c.min >> c.max;
    return input;
}




// 通过显示实例化来解决模板不嫩分开编译的问题
template class Course<int>;
template class Course<float>;

 */
