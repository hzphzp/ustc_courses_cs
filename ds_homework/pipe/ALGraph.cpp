#include "ALGraph.h"
#include<iostream>
using namespace std;
ALGraph::ALGraph(){
    vertices = new VertexNode[MAX_INIT_SIZE];
}
void ALGraph::creategraph(){
    int i,j,k;
    Weighttype weight;
    cout<<"please input the vexnum , the arcnum, and the kind of the graph"<<endl;
    cin>>vexnum>>arcnum>>kind;
    cout<<"please input the vertices"<<endl;
    for(  i = 0; i < vexnum; i++){
            cin>>vertices[i].data;
            vertices[i].firstarc = NULL;
    }
    for(k = 0; k < arcnum; k++){
            ArcNode *p;
            VertexType vi, vj;
            cout<<"please input the arc and its weight"<<endl;
            cin >> vi >>vj;
            if(vi =='I'){
                    cout<<"find it";
            }
            i = LocateVex(vi);
            j = LocateVex(vj);
            p = new ArcNode;
            cin>>weight;
            p->weight = weight;
            cin.clear();
            cin.sync();
            p->adjvex = j;
            p->nextarc = vertices[i].firstarc;
            vertices[i].firstarc = p;
            p = NULL;
            if(kind ==2){
                    p = new ArcNode;
                    p->weight = weight;
                    p->adjvex = i;
                    p->nextarc = vertices[j].firstarc;
                    vertices[j].firstarc = p;
                    p = NULL;
            }
    }
}//CreateGraph
int ALGraph::LocateVex(VertexType d){
    for(int i= 0 ; i<vexnum;i++)
            if( vertices[i]. data == d) return i;
    return -1;
}//LocateVex

void ALGraph::Prim(int v0){
    int i,k;
    Weighttype lowcast[MAX_INIT_SIZE];//记录各个点到红区的最短距离
    for(i=0;i<vexnum;i++) lowcast[i] = 1000;
    int lowcast_adjvex[MAX_INIT_SIZE];//记录最短距离下对应的红点
    ArcNode *p;
    p = vertices[v0].firstarc;
    while(p){
            lowcast[p->adjvex] = p->weight;
            lowcast_adjvex[p->adjvex] = v0;
            p = p->nextarc;
    }
    lowcast[v0] = 0;
    for(i=0;i<vexnum;i++){
            k = minedge(lowcast);
            if(k == -1){
                    cout<<"finished"<<endl;
                    return;
            }
            cout<<vertices[lowcast_adjvex[k]].data<<"------"<<vertices[k].data<<"       "<<lowcast[k]<<endl;
            lowcast[k] = 0;
            p = vertices[k].firstarc;
            while(p){
                    if(lowcast[p->adjvex] != 0){
                        if(p->weight < lowcast[p->adjvex]){
                                lowcast[p->adjvex] = p->weight;
                                lowcast_adjvex[p->adjvex] = k;
                        }
                    }
                    p = p->nextarc;
            }
    }

}
int ALGraph::minedge(Weighttype *lowcast){
    int i;
    int k = -1;
    Weighttype w = 1000;
    for(i = 0; i<vexnum; i++){
            if(lowcast[i]!= 0 && lowcast[i]<w){
                    w = lowcast[i];
                    k = i;
            }
    }
    return k;
        return 0;
}



void ALGraph::Kruskal(int v0){
    cout<<"Kruskal"<<endl;
}

void ALGraph::print(){
    ArcNode *p;
    for(int i = 0 ;i< vexnum; i++){
            cout << vertices[i].data<<"->";
            p = vertices[i].firstarc;
            while(p){
                    cout<<vertices[p->adjvex].data;
                    p = p->nextarc;
            }
            cout<<endl;
    }
}




