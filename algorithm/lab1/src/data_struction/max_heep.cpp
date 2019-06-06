#include <data_struction.h>

Max_heap::Max_heap(DATA_TYPE* head, int length){
    this->head = head;
    this->length = length;
}

bool Max_heap::is_max_heap(){
    bool flag = true;
    for(int i = 0; i < this->length; i++){
        if(2 * (i + 1) - 1 >= this->length)
            continue;
        if(int left = (2 * (i + 1) - 1) < this->length){
            if(this->head[left] > this->head[i]){
                flag = false;
            }
        }
        if(int right = (2 * (i + 1)) < this->length){
            if(this->head[right] > this->head[i]){
                flag = false;
            }
        }
    }
    return flag;
}

void Max_heap::max_heapify(int i){
    // arg i is the index of the root, start with 0
    int left = 2 * (i + 1) -1;
    int right = left + 1;
    int i_largest = i;
    if(left < this->length && this->head[i_largest] < this->head[left])
        i_largest = left;
    if(right < this->length && this->head[i_largest] < this->head[right])
        i_largest = right;
    if(i_largest != i){
        // 大根堆产生了变动
        DATA_TYPE tmp = this->head[i];
        this->head[i] = this->head[i_largest];
        this->head[i_largest] = tmp;
        this->max_heapify(i_largest);
    }
}

void Max_heap::shorten_the_length() {
    this->length --;
}