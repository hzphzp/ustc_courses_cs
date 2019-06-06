#pragma once

#include "sort_algorithms.h"

class Max_heap{
    private: 
    DATA_TYPE* head;
    int length;
    public: 
    Max_heap(DATA_TYPE* head, int length);

    bool is_max_heap();

    void max_heapify(int i);

    void shorten_the_length();
};


