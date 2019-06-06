#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include<string>
using namespace std;
typedef struct{
    string key;
    int num;
}Elemtype;

typedef struct LHNode{
	Elemtype	data;
	struct LHNode		*next;		//记录数
}LHNode,*LHNodeptr;



class hashtable
{
public:
    hashtable(int maxsize = 43);
    int searchword(string s, LHNodeptr &p);   //在表中找到词，返回位置指针p
    void insertword(string s);//在表中插入新的词
    void reset();  //重置表中关键词的次数项
    LHNodeptr	*elem;
	int		countnum;		//记录数
	int		sizeindex;  //哈希表容量
};

int Hash(string s);



#endif // HASHTABLE_H_INCLUDED
