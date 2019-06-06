#include<iostream>
using namespace std;
#include "app.h"


void app::show(){
    cout << "this is the huffman en-decoder communication system" << endl;
    cout << "=============tap I to initialize==================" <<endl;
    cout << "=============tap E to encode the tobetran=========" <<endl;
    cout << "=============tap D to decode the codefile====="<<endl;
    cout << "=============tap P to print what you want=======" <<endl;
    cout << "=============tap Q to quit=====================" <<endl;
    cout <<endl<<"*************i am the split line********************" <<endl;
}
bool app::cycle(){
    char control;
    cin>>control;
    switch(control){
    case 'I':
        {
            coder.initialization();                //TODO: a method to complete
            break;
        }
    case 'P':
        {
            char control_1;
            cout << "Do you want to print the codefile or the huffman tree" <<endl;
            cout <<" ====tap f for codefile ====tap t for huffman tree" << endl;
            cin >> control_1;
            switch(control_1){
            case 'f':
                {
                    coder.print_codefile();                     //TODO: a method to complete
                    break;
                }
            case 't':
                {
                    coder.print_haffmantree(0,0,true);             //TODO: a method to complete
                    break;
                }
            default:
                {
                    cout<<"wrong comment for print"<<endl;
                }
            }
            break;
        }
    case 'E':
        {
            coder.encoder();                               //TODO: a method to complete
            break;
        }
    case 'D':
        {
            coder.decoder();                               //TODO: a method to complete
            break;
        }
    case 'Q':
        {
        return false;
        }
    default:
        {
            cout<<"wrong comment"<<endl;
        }
    }
    cin.clear();
    cin.sync();
    return true;
}//app::cycle



