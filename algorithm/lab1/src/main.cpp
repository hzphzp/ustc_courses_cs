#include <data.h>
#include "sort_algorithms.h"
#include "result_visual.h"
#include <time.h>
#include <iostream>
#include <fstream>
#define SAMPLE 6
int main(int, char**) {
    auto *times = new clock_t[4 * SAMPLE];
    clock_t start, end;
    int numbers[7] = {1000, 10000, 50000, 100000, 200000, 500000, 1000000};
    auto* l = new DATA_TYPE[1000000];
    generate(l, 1000000);
    // int numbers[7] = {10, 10, 10, 10, 10, 10, 10};
    for(int i = 0; i < SAMPLE; i ++){
        auto* l1 = new DATA_TYPE[numbers[i]];
        auto* l2 = new DATA_TYPE[numbers[i]];
        auto* l3 = new DATA_TYPE[numbers[i]];
        auto* l4 = new DATA_TYPE[numbers[i]];
        copy(l, l1, numbers[i]);
        copy(l, l2, numbers[i]);
        copy(l, l3, numbers[i]);
        copy(l, l4, numbers[i]);
        // 插入排序
        start = clock();
        sort_insert(l1, numbers[i]);
        end = clock();
        times[SAMPLE * 0 + i] = end - start;
        std::cout << "插入done" << std::endl;
        delete[] l1;
        // 归并排序
        start = clock();
        sort_merge(l2, numbers[i]);
        end = clock();
        times[SAMPLE * 1 + i] = end - start;
        std::cout << "归并done" << std::endl;
        delete[] l2;

        // 快速排序
        start = clock();
        sort_quick(l3, numbers[i]);
        end = clock();
        times[SAMPLE * 2 + i] = end - start;
        std::cout << "快速done" << std::endl;
        delete[] l3;

        // 堆排序
        start = clock();
        sort_max_heap(l4, numbers[i]);
        end = clock();
        times[SAMPLE * 3 + i] = end - start;
        std::cout << "堆done" << std::endl;
        delete[] l4;

        // myprint(l, numbers[i]);
        std::cout << "=============" << numbers[i] << "============" << std::endl;
    }
    // 记录结果
    myprint(times, 4 * SAMPLE);
    std::ofstream outfile;
    outfile.open("result.txt");
    for (int i = 0; i < 4 * SAMPLE; i ++){
        outfile << times[i] << std::endl;
    }

}
