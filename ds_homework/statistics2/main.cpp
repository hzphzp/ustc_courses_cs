#include<iostream>
using namespace std;
#include<stdio.h>
#include "account.h"
#include<time.h>
int main(){
    clock_t start, end,end2;
    start = clock();
    account list[100000];
    FILE * pFile;  
    long lSize;  
    char * buffer;  
    size_t result;  
      
    /* 若要一个byte不漏地读入整个文件，只能采用二进制方式打开 */   
    pFile = fopen ("gsm.dat", "rb" );  
    if (pFile==NULL)  
    {  
        fputs ("File error",stderr);  
        exit (1);  
    }  
  
    /* 获取文件大小 */  
    fseek (pFile , 0 , SEEK_END);  
    lSize = ftell (pFile);  
    rewind (pFile);  
  
    /* 分配内存存储整个文件 */   
    buffer = (char*) malloc (sizeof(char)*lSize);  
    if (buffer == NULL)  
    {  
        fputs ("Memory error",stderr);   
        exit (2);  
    }  
  
    /* 将文件拷贝到buffer中 */  
    result = fread (buffer,1,lSize,pFile);  
    if (result != lSize)  
    {  
        fputs ("Reading error",stderr);  
        exit (3);  
    }  
  
    /* 结束演示，关闭文件并释放内存 */  
    fclose (pFile);  
//    ifstream infile("gsm.dat", ios::in);
//    if(!infile.is_open()){
//        cout<<"can not open the file";
//    }
	
   // int fd;
   // char* ptr;    int fd;
   // char* ptr;
   // fd=open("gsm.dat",O_CREAT|O_RDWR,00777);
   // if(fd<0){
   //     printf("can not open the fjle");
   // }
   // struct stat buf;
   // fstat(fd, &buf);
   // 
   // ptr=(char*)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE, MAP_SHARED , fd , 0);
   // int i = 0;
   // fd=open("gsm.dat",O_CREAT|O_RDWR,00777);
   // if(fd<0){
   //     printf("can not open the fjle");
   // }
   // struct stat buf;
   // fstat(fd, &buf);
   // 
   // ptr=(char*)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE, MAP_SHARED , fd , 0);
    int i = 0;
    char* c;
    record r;

    while(i<lSize) {
        c = buffer+i;
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
