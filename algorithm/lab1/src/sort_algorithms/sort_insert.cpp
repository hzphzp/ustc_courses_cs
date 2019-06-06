//
// Created by root on 4/12/19.
//


#include <sort_algorithms.h>

void sort_insert(DATA_TYPE* head, int length) {
    for(int target = 1; target < length; target ++) {
        DATA_TYPE key = head[target];
        int compare = target -1;
        while(compare >= 0&& head[compare] > key){
            head[compare + 1] = head[compare];
            compare --;
        }
        head[compare + 1] = key;
    }
}

