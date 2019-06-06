#include<iostream>
#include<fstream>
#include "coder.h"
using namespace std;
void Coder::initialization(){
    int i;
    int w[50];
    cout<<"please input the number you your encode letters"<<endl;
    cin>>n;
    m = 2*n-1;                                           //two private variable;
    cout<<"please input the letters"<<endl;
    ch = new char[n+1];
    cin.clear();
    cin.sync();
    for(i = 1;i<=n;i++) ch[i] = getchar();                                // a private variable;
    cout<<"please input the weights to initialize the huffman tree"<<endl;
    cin.clear();
    cin.sync();
    for(i = 1; i<=n; i++) cin>>w[i];
    HT = new HTNode[m+1];
    create_tree(w);                        //a function and a struct to complete
    outfile.open("E:\\CodeblockFile\\homework\\haffman\\hfmtree.txt", ios::out);
    for(int i = 1;i<=2*n-1;i++) outfile<<HT[i].weight<<" "<<HT[i].parent<<" "<<HT[i].lchild<<" "<<HT[i].rchild<<endl;
    cout<<"the huffmantree is created and its data is written to hfmtree"<<endl;
    delete[]HT;
    outfile.close();
}
void Coder::encoder(){
    int i;                     //the variable for cycling
    HT = new HTNode[m+1];
    HC = new char*[n+1];
    infile.open("E:\\CodeblockFile\\homework\\haffman\\hfmtree.txt", ios::in);
    if(!infile) cout<<"can not open hfmtree.txt";
    for(i = 1; i<=2*n-1; i++) infile>>HT[i].weight>>HT[i].parent>>HT[i].lchild>>HT[i].rchild;
    infile.close();
    HuffmanCoding();                                  //a series of function to complete
    infile.open("E:\\CodeblockFile\\homework\\haffman\\ToBeTran.txt", ios::in);
    if(!infile) cout<<"can not open ToBeTran.txt";
    outfile.open("E:\\CodeblockFile\\homework\\haffman\\codefile.txt", ios::out);
    if(!outfile) cout<<"can not open codefile.txt";
    char c;
    while(!infile.eof()){
            c = infile.get();
            outfile<<HC[letter_to_number(c)];                     // a int function to complete
            i++;
    }
    cout<<"encoder completed and the result is written to codefile"<<endl;
    infile.close();
    outfile.close();
    delete[]HT;
    delete[]HC;
}
void Coder::decoder(){
    int i=0;                     // a variable for cycling
    int p;                    //a pointer
    HT = new HTNode[m+1];
    infile.open("E:\\CodeblockFile\\homework\\haffman\\hfmtree.txt", ios::in);
    if(!infile) cout<<"can not open hfmtree.txt";
    for(i = 1; i<=2*n-1; i++)
        infile>>HT[i].weight>>HT[i].parent>>HT[i].lchild>>HT[i].rchild;
    infile.close();
    p = m;
    infile.open("E:\\CodeblockFile\\homework\\haffman\\codefile.txt", ios::in);
    if(!infile) cout<<"can not open codefile";
    outfile.open("E:\\CodeblockFile\\homework\\haffman\\TextFile.txt", ios::out);
    if(!outfile) cout<<"can not open TextFile";
    char c;
    while(!infile.eof()){
            c = infile.get();
            p = (c =='0')?HT[p].lchild:HT[p].rchild;
            if(HT[p].lchild == 0&&HT[p].rchild == 0){
                    outfile<<ch[p];
                    p = m;
            }
    }
    cout<<"decoder completed and the result is written to TextFile"<<endl;
    infile.close();
    outfile.close();
    delete[]HT;
}
void Coder::print_codefile(){
    int i =0;                    //cycle
    infile.open("E:\\CodeblockFile\\homework\\haffman\\codefile.txt", ios::in);
    if(!infile) cout<<"can not open codefile";
    outfile.open("E:\\CodeblockFile\\homework\\haffman\\CodePrint.txt", ios::out);
    char c;
    cout<<"============the content of codefile is below============"<<endl;
    while(!infile.eof()){
            i++;
            infile>>c;
            cout<<c;
            outfile<<c;
            if(i%50 == 0){
                    cout<<endl;
                    outfile<<endl;
            }
    }
    infile.close();
    outfile.close();
    cout<<"the codefile in specific sequence is written into CodePrint"<<endl;
}
void Coder::print_haffmantree(int bt, int levl, bool start)
{
    if(start){
        cout<<"==============the following is the huffmantree created before==========="<<endl;
        int i;                     //the variable for cycling
        HT = new HTNode[m+1];
        HC = new char*[n+1];
        infile.open("E:\\CodeblockFile\\homework\\haffman\\hfmtree.txt", ios::in);
        if(!infile) cout<<"can not open hfmtree.txt";
        for(i = 1; i<=2*n-1; i++) infile>>HT[i].weight>>HT[i].parent>>HT[i].lchild>>HT[i].rchild;
        infile.close();
        bt = m;
        outfile.open("E:\\CodeblockFile\\homework\\haffman\\TreePrint.txt", ios::out);
    }
	if(bt==0)
		return;                         //已经是最后了
	print_haffmantree(HT[bt].rchild,levl+1,false);//递归调用
	for(int i=0;i<levl;++i){
            cout<<"   ";//先输出空格，给后面的继续输入留出余地
            outfile<<"   ";
	}
	if(levl>=1){
            cout<<"--";
            outfile<<"--";
	}
	cout<<"("<<HT[bt].weight<<")";//输出右结点的信息（权值）
	outfile<<"("<<HT[bt].weight<<")";
	if(HT[bt-1].lchild==0)//如果左结点也是叶子结点，输出左结点的信息
	{
		cout<<ch[bt];
		cout<<':'<<HT[bt].weight<<endl;
        outfile<<ch[bt];
		outfile<<':'<<HT[bt].weight<<endl;
	}
	else{
            cout<<endl;
            outfile<<endl;
	}
	print_haffmantree(HT[bt].lchild,levl+1,false);
	if(start){
            outfile.close();
            cout<<"printing complete and the tree's picture is stored in TreePrint"<<endl;
	}
}






