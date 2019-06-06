#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

int main(){
    int count[10][23] = {0};
    char c[23];
    int i, k;
    int s;
    ofstream outfile("feature", ios::out);
    ifstream infile("gsm.dat",ios::in);
    while(!infile.eof()){
        infile >> c;
        for(i = 0; i < 16; i++){
            s = int(c[i]-'0');
            count[s][i] += 1;
        }
    }
    cout << "done" << endl;
    for(i = 0; i < 10; i++){
        for(k = 0; k <16; k++){
            outfile<<setw(8)<<count[i][k];
            cout<<setw(8)<<count[i][k];
        }
        cout<<endl;
        outfile<<endl;
    }
    return 0;
}
