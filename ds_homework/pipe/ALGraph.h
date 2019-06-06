#ifndef ALGRAPH_H_INCLUDED
#define ALGRAPH_H_INCLUDED
#include<iostream>
using namespace std;
#include<fstream>
#define Weighttype float
#define VertexType char
#define MAX_INIT_SIZE 20
typedef struct ArcNode{
    int adjvex;               //邻节点的位置下标
    Weighttype weight;
    struct ArcNode *nextarc;
}ArcNode;


typedef struct VertexNode{
    VertexType data;
    ArcNode *firstarc;
}VertexNode;

class ALGraph
{
public:
    ALGraph();
    void creategraph();
    void Prim(int);
    void Kruskal(int);
    int LocateVex(VertexType d);
    void print();
    int minedge(Weighttype *lowcast);
private:
////    int LocateVex(char d);

    VertexNode *vertices;
    int vexnum;
    int arcnum;
    int kind;
};







#endif // ALGRAPH_H_INCLUDED
