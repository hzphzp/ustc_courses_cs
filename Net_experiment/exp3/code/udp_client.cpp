#include<sys/types.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
using namespace std;

#define ADDR "127.0.0.1" //在本机测试用这个地址，如果连接其他电脑需要更换IP
#define SLEEP 1 // 每次发送等待1秒时间
#define TIMES 10 // 一共发送100个数据包
#define PORT 1234 // 端口号
#define MAXSIZE 1024 // 数据包大小为1024Byte


/*
    文件名: udp_client.cpp

    代码作用: 这个是实验三第二个小实验(统计udp的丢包率)的1/2代码, 是客户端端(即发送端的代码), 
            这里的情景设置是, client端 使用udp向 server 端 发送100 个数据包, 每个1024字节.
            在server端统计收到的包的数量 count, 并用(100 - count) / count 来计算总的丢包率, 
            故这个程序只要通过for(int i = 0; i < 100; i++) 循环发送100个数据包就行了

    使用方式: 在该文件目录下输入:
            >make clean
            >make
            >./udp_client udp_client_data
            (这里udp_client_data是一个很大的文件, 发送的数据从里面读取出来)
            即可开始这个程序

    作者: 黄志鹏 PB16150288

    代码结构: 定义并初始化变量
            bind()
            sendto()
    
*/
int main(){
    /*
        下面定义需要用到的一些变量
        (大部分变量和之前的talk 相同, 这里不在累述)
    */
    char buf[MAXSIZE];
    struct sockaddr_in server_addr, client_addr;
    memset((void *) &server_addr, 0, sizeof(server_addr));
    memset((void *) &client_addr, 0, sizeof(client_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ADDR);
    server_addr.sin_port = htons(PORT);
    int server_fd;
        if((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        fprintf(stderr, "apply the socket error!\n");
        exit(1);
    }

    // 打开数据文件, 并处理异常
    FILE * client_buf_file = fopen("udp_client_data", "rb");
    if(!client_buf_file){
        fprintf(stderr, "cannot open the udp client buf file!\n");
        exit(1);
    }

    // 发送数据包
    for (int i = 0; i < TIMES; i ++){
        fread(buf, sizeof(char), MAXSIZE, client_buf_file);
        // 打印发送的信息
        cout << buf << endl;
        sendto(server_fd, buf, MAXSIZE, 0, (sockaddr *) &server_addr, sizeof(server_addr));
        //sleep(SLEEP);
    }
    // 关闭socket
    close(server_fd);
    return 0;
}