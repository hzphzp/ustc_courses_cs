#include <iostream>
#include <sort_algorithms.h>

//
// Created by root on 4/12/19.
//
void merge(DATA_TYPE* head, int start, int gap, int end){
    auto* left = new DATA_TYPE[gap - start];
    auto* right = new DATA_TYPE[end - gap];

    for(int i = 0; i < gap - start; i ++){
        left[i] = head[start + i];
    }
    for(int i = 0; i < end - gap; i ++){
        right[i] = head[gap + i];
    }

    int i_left = 0;
    int i_right = 0;
    for(int i = start; i < end; i ++){
        if(i_left >= gap - start){
            head[i] = right[i_right];
            i_right ++;
        }
        else if(i_right >= end - gap){
            head[i] = left[i_left];
            i_left ++;
        }
        else if(left[i_left] >= right[i_right]){
            head[i] = right[i_right];
            i_right ++;
        }
        else if(left[i_left] < right[i_right]){
            head[i] = left[i_left];
            i_left ++;
        }
        else{
            std::cout << "some wrong" << std:: endl;
        }
    }

    delete[] left;
    delete[] right;
}

void sort_merge_unit(DATA_TYPE* head, int start, int end){
    //the end is like python that the end can not be reach
    if(start >= end - 1) return;
    int gap = (start + end) / 2;
    sort_merge_unit(head, start, gap);
    sort_merge_unit(head, gap, end);
    merge(head, start, gap, end);
}



void sort_merge(DATA_TYPE *head, int length) {
    sort_merge_unit(head, 0, length);
}

