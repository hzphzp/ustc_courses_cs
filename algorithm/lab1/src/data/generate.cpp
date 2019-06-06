//
// Created by root on 4/12/19.
//

#include <cstdlib>
#include <time.h>
#include <iostream>
#include <sort_algorithms.h>


DATA_TYPE* generate(DATA_TYPE* head, int number) {
    srand((unsigned)time(NULL));
    for(int i = 0; i < number; i++ )
        head[i] = rand();
}
