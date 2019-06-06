#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
using namespace std;

#define PORT 1234 // 定义端口号
#define MAXSIZE 1024 // 定义数据包的字节数
#define TIMES 10 // 定义client 发送的总次数
                    // 一共会有100个数据包发送过来.

/*
    文件名: udp_server.cpp

    代码作用: 这个是实验三第二个小实验(统计udp的丢包率)的1/2代码, 是服务器端(即接收端的代码), 
            这里的情景设置是, client端 使用udp向 server 端 发送100 个数据包, 每个1024字节.
            在server端统计收到的包的数量 count, 并用(100 - count) / count 来计算总的丢包率, 
            故这个程序不能通过for(int i = 0; i < 100; i++) 来做接受循环, 而应该是一个while(1)
            的循环, 并设置一个长达7秒的计时器来标定接受的结束, 当7秒内没有数据包到达的时候, 退出循环, 并结算
            丢包率.

    使用方式: 在该文件目录下输入:
            >make clean
            >make
            >./udp_server udp_server_data
            (这里udp_server_data是新的文件, 用来接受数据)
            即可开始这个程序, 并等待另一个终端的udp_client 程序进行数据发送

    作者: 黄志鹏 PB16150288

    代码结构: 定义并初始化变量
            bind()
            recvFrom()
    
*/

int main(){
    /*
        下面定义需要用到的一些变量
        (大部分变量和之前的talk 相同, 这里不在累述)
    */
    int count = 0; // count 记录收到的数据包的数量
    socklen_t len; //to store the length of the client address
    char buf[MAXSIZE];
    struct sockaddr_in server_addr, client_addr;
    memset((void *) &server_addr, 0, sizeof(server_addr));
    memset((void *) &client_addr, 0, sizeof(client_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORT);
    server_addr.sin_addr.s_addr= htonl (INADDR_ANY);
    int server_fd;

    // 打开文件, 存储收到的数据, 并且进行异常处理
    FILE* server_buf_file = fopen("udp_server_data", "wb");
    if(!server_buf_file){
        fprintf(stderr, "cannot open the server buf file!\n");
        exit(1);
    }

    // 申请socket 并且绑定地址
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if((bind(server_fd, (sockaddr *) &server_addr, sizeof(server_addr))) < 0){
        fprintf(stderr, "bind error!\n");
        exit(1);
    }

    // 这里循环接受数据, 设置有 7秒的计时器, 如果7秒内没有接收到任何的数据包, 
    // 程序认为发送结束, 退出这个循环, 并计算丢包率
    while(1){
        struct timeval timeout={7,0}; // 设置7秒计时

        /* set receive UDP message timeout */

        setsockopt(server_fd, SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));

        // 接收数据包
        int recv_len = recvfrom(server_fd, (void *) buf, MAXSIZE*sizeof(char), \
        0, (sockaddr *) &client_addr, (socklen_t *) &len);

        // 如果7秒内有数据包, 且没有发生异常
        if (recv_len == MAXSIZE) {
            // 输出这个数据包的长度
            cout << recv_len << endl;
            // Message Received
            fprintf(stderr, "receive the packet!\n");
            count ++; // 又收到一个数据包, count 加一
            // 写入数据, 并且处理异常
            if(fwrite((void *) buf, sizeof(char), MAXSIZE, server_buf_file) != MAXSIZE){
                fprintf(stderr, "write the buf wrong!\n");
            } 
        }
        // 如果7秒内有数据包, 但是传输发生了异常
        else if (recv_len > 0 && recv_len < MAXSIZE){
            fprintf(stderr, "the packet is incomplete, \
            I suppose this is a way of dropping packet!\n"); 
        }
        // 如果7秒内没有数据包发来, 认为传输结束, 退出循环
        else{
            //Message Receive Timeout or other error
            break;
        }
    }

    // 退出循环后, 计算丢包率
    cout << "received " << count << " packets" << endl;
    cout << "dropped " << TIMES - count << " packets" << endl;
    cout << "丢包率为: " << (TIMES - count) / count * 100 << "% " << endl;
    close(server_fd);
    return 0;
}