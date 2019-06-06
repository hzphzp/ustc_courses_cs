//
// Created by root on 4/11/19.
// by huangzp

#include "data_struction.h"
#include "sort_algorithms.h"

void sort_max_heap(DATA_TYPE *head, int length) {
    Max_heap maxHeap(head, length);
    for(int i = int(length / 2 - 1); i >= 0; i--){
        maxHeap.max_heapify(i);
    }
    for(int i = length - 1; i >= 0; i--){
        DATA_TYPE tmp = head[0];
        head[0] = head[i];
        head[i] = tmp;
        maxHeap.shorten_the_length();
        maxHeap.max_heapify(0);
    }
}


