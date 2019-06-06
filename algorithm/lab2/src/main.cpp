#include <iostream>
#include "DataStructure.h"

using namespace std;
void test() {
    cout << "==============test==============!" << endl;
    auto* test = new RedBlackTree<Course<int>>;
    test->insert(Course<int>("math",1, 2));
    test->insert(Course<int>("alg",10, 20));
    test->insert(Course<int>("math",7, 8));
    test->insert(Course<int>("alg",3, 4));
    test->insert(Course<int>("c++",5, 7));
    test->insert(Course<int>("python",21, 30));
    test->remove(Course<int>("math", 7, 8));
    test->print();
    test->inOrder(test->root);
}
int main() {
    // test();
    char operate;
    auto timeTable = new RedBlackTree<Course<int>>;
    cout << "===============课表系统=================" << endl;
    cout << "插入课程----I" << endl <<
    "删除课程----D" << endl << "查询课程----S" << endl <<
    "显示当前课程信息----P" << endl << "打印红黑树----C" << endl << "退出系统----Q" << "请输入：" << endl;
    while(true) {
        string name;
        int min, max;
        Course<int> course;
        Course<int> minRange, maxRange;
        cin >> operate;
        switch(operate) {
            case 'I':
                cout << "请输入课程名称：" << endl;

                cin >> name;
                cout << "请输入时间区间:" << endl;
                cin >> min >> max;
                course = Course<int>(name, min, max);
                if(timeTable->insert(course)) cout << "插入成功" << endl;
                else{
                    cout << "插入失败， 可能是存在时间冲突" << endl;
                }
                break;
            case 'D':
                cout << "请输入课程名称：" << endl;
                cin >> name;
                cout << "请输入时间区间:" << endl;
                cin >> min >> max;
                course = Course<int>(name, min, max);
                if(timeTable->remove(course)) cout << "删除成功" << endl;
                else{
                    cout << "删除失败， 可能是没有这个课程" << endl;
                }
                break;
            case 'S':
                cout << "按照时间还是课程名字----时间T & 课程名字N" << endl;
                cin >> operate;
                if(operate == 'T'){
                    cout << "请输入时间区间：" << endl;
                    cin >> min >> max;
                    minRange = Course<int>("", min, min);
                    maxRange = Course<int>("", max, max);
                    timeTable->range(minRange, maxRange);
                }
                else if(operate == 'N'){
                    cout << "请输入课程名称:" << endl;
                    cin >> name;
                    course = Course<int>(name, 0, 0);
                    timeTable->searchName(course);
                }
                else{
                    cout << "输入错误， 请重新输入" << endl;
                }
                break;
            case 'P':
                timeTable->inOrder(timeTable->root);
                break;
            case 'C':
                timeTable->print();
                cout << timeTable->isCorrect() << endl;

                break;
            case 'Q':
                break;
            default: cout << "输入错误， 请重新输入" << endl;
        }
        if (operate == 'Q') break;
        cout << "===============课表系统=================" << endl;
        cout << "插入课程----I" << endl <<
        "删除课程----D" << endl << "查询课程----S" << endl <<
        "显示当前课程信息----P" << endl << "打印红黑树----C" << endl << "退出系统----Q" << "请输入：" << endl;
    }
    return 0;
}