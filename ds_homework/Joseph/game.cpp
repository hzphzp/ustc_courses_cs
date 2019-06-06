#include<iostream>
#include "cyclelist.h"
#include "game.h"
void game::gamestart(){
    int k,i;
    cout<<"input the number of agents"<<endl;
    cin>>n;
    cout<<"input the keys of agents in order"<<endl;
    for(i=1;i<=n;i++){
            cin>>k;
            L.Append(i,k);
    }
    cout<<endl<<"============the game is ready=============="<<endl;
    p = L.get_head();
}
void game::killprocess(){
    int k;
    cout<<"input the initial key"<<endl;
    cin>>k;
    while(!L.ListEmpty()) k=killer(k);                 //update the key
}
int game::killer(int k){
    int i,n_,k_;
    for(i=1;i<k;i++) p=p->next;       //Get the prior pointer of the agent be killed
    L.Delete(p,k_,n_);
    cout<<n_<<' ';
    return k_;
}


