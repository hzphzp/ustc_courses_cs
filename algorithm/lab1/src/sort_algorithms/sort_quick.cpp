//
// Created by root on 4/12/19.
//

#include <iostream>
#include <sort_algorithms.h>

int partition(DATA_TYPE* head, int start, int end){
    DATA_TYPE compare = head[end - 1];
    int gap = start;
    for(int i = start; i < end - 1; i ++){
        if(head[i] <= compare){
            gap ++;
            DATA_TYPE tmp = head[gap - 1];
            head[gap -1] = head[i];
            head[i] = tmp;
        }
    }
    head[end - 1] = head[gap];
    head[gap] = compare;
    return gap;
}

void sort_quick_headandtail(DATA_TYPE* head, int start, int end){
    // 这里的end 的pythontic的 到达不到的
    if(start >= end) return;
    int gap = partition(head, start, end);
    sort_quick_headandtail(head, start, gap);
    sort_quick_headandtail(head, gap + 1, end);

}



void sort_quick(DATA_TYPE *head, int length) {
    sort_quick_headandtail(head, 0, length);
}



