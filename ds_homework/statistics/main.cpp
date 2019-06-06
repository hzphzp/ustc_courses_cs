#include<iostream>
using namespace std;
#include<stdio.h>
#include "account.h"
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/types.h>
int main(){
    clock_t start, end,end2;
    start = clock();
    account list[100000];
//    ifstream infile("gsm.dat", ios::in);
//    if(!infile.is_open()){
//        cout<<"can not open the file";
//    }
	

    int fd;
    char* ptr;
    fd=open("gsm.dat",O_CREAT|O_RDWR,00777);
    if(fd<0){
        printf("can not open the fjle");
    }
	struct stat buf;
    fstat(fd, &buf);
    
    ptr=(char*)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE, MAP_SHARED , fd , 0);
    int i = 0;
    char* c;
    record r;
    while(i<buf.st_size) {
        c = ptr+i;
        get_record(c,r);
        get_account(list,r);
        i += 22;
    }
    end2 = clock();
    FILE* fp;
    fp = fopen("result", "w+");
    accptr p;
    for(int i;i<100000;i++){
        if(list[i].key2 == -1) continue;
        p = &list[i];
        preorder(p, fp);
    }
    fclose(fp);
    end = clock();
    cout<<"Total time: "<<(double)(end - start)/CLOCKS_PER_SEC<<"s"<<endl;

    cout<<"creating time: "<<(double)(end2 - start)/CLOCKS_PER_SEC<<"s"<<endl;
    return 0;
}
