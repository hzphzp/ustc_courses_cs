#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 100
#define ADDR "127.0.0.1" //在本机测试用这个地址，如果连接其他电脑需要更换IP
#define SERVERPORT 8088
using namespace std;


/*
    文件名: client.cpp

    代码作用: 这个是实验三第一个小实验(talk)的1/2代码, 是talk的首先发起者
            命名为client  的原因是, 情景为 client 先向服务器端talk, server响应, 
            client 再回复, 周而复始, 知道有一方输入 q 并按下回车, 两方程序同时结束退出.

    使用方式: 在该文件目录下输入:
            >make clean
            >make
            >./client
            即可开始这个程序, 输入想要发送的消息, 并且发送后等待server的回复

    作者: 黄志鹏 PB16150288

    代码结构: 定义和初始化变量
            connect()
            talk
    
*/
int main(){
    /*
        下面定义需要用到的一些变量, 并且对其进行初始化
    */
    int client_fd; // 定义ｓｏｃｋｅｔ　描述符
    char buf[1024]; //　用来存储从ｓｅｒｖｅｒ来的信息
    char message[1024]; // 用来存放需要发送的消息
    if((client_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "socket apl error!\n");
        exit(1);
    }
    struct sockaddr_in server_addr; // 用来存储ｓｅｒｖｅｒ的地址结构体
    memset((void *) &server_addr, 0, sizeof(server_addr)); //对地址结构提进行填充
    // 设置server的地址结构体
    server_addr.sin_family = AF_INET; // 通信使用的是ipv4
    server_addr.sin_port = htons(SERVERPORT); // 填写使用的端口是 8088
    server_addr.sin_addr.s_addr = INADDR_ANY; // 表示接收任何的地址

    // 使用ｃｏｎｎｅｃｔ（）　函数进行连接，　并且进行异常处理
    if(connect(client_fd, (sockaddr *) &server_addr, sizeof(sockaddr)) < 0){
        fprintf(stderr, "socket connected error!");
        exit(1);
    }
    else{
        // 提示用户一些连接的信息
        cout << "connected to " << server_addr.sin_addr.s_addr << "::" << server_addr.sin_port << endl;
    }

    
    while(1){
        // 这里使用＞＞＞　提示ｃｌｉｅｎｔ可以进行输入了
        cout << ">>>";
        // 从终端标准输入中得到要发送的信息，　并且存储在message 中
        fgets(message, 1024, stdin); 
        while(write(client_fd, (void *) &message, 1024*sizeof(char)) != 1024){
            //　如果发生异常，　重新输入
            cout << ">>>";
            fgets(message, 1024, stdin); 
        }
        // 判断ｃｌｅｎｔ是否想要停止
        // 这里如果发送的是q\n 说明client想停止, 跳出循环,并通知server 停止
        if(!strcmp(message, "q\n")){
            //close the connection
            cout << "the client close the talk" << endl;
            close(client_fd);
            break;
        }
        // 得到server回复的信息
        while(read(client_fd, (void *) &buf, 1024*sizeof(char)) != 1024);
        // 判断server是否想要停止
        if(!strcmp(buf, "q\n")){
            //close the connection
            cout << "the server close the talk" << endl;
            close(client_fd);
            break;
        }
        // 打印出结果
        cout << buf;
    }
}