#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
using namespace std;

// 这里是定义这个程序将要使用的端口号
#define PORT 8088

/*
    文件名: server.cpp

    代码作用: 这个是实验三第一个小实验(talk)的1/2代码, 是talk的其次发起者
            命名为server 的原因是, 情景为 client 先向服务器端talk, server响应, 
            client 再回复, 周而复始, 知道有一方输入 q 并按下回车, 两方程序同时结束退出.

    使用方式: 在该文件目录下输入:
            >make clean
            >make
            >./server
            即可开始这个程序, 并等待另一个终端的client 程序发来消息

    作者: 黄志鹏 PB16150288
    
    代码结构: 定义并初始化变量
            bind()
            listen()
            accept()
    
*/

int main(){
    /*
        下面定义需要用到的一些变量
    */
    char buf[1024]; // 存储从client 端接收的消息
    char message[1024];// 存储将要向client 发送的消息
    socklen_t len; // 用于accept 等函数来存储client_in 地址的长度
    struct sockaddr_in server_in, client_in; // 定义服务器端和客户端的 socket地址
    int server_fd, client_fd; // 定义服务器端和客户端的socket 描述符

    /*
        下面对一些变量进行初始化或者是值填充
    */
    // 填充空指针, 全部填写的是0
    memset((void *) &server_in, 0, sizeof(sockaddr_in));
    memset((void *) &client_in, 0, sizeof(sockaddr_in));
    // 设置server的地址结构体
    server_in.sin_family = AF_INET; // 通信使用的是ipv4
    server_in.sin_port = htons(PORT); // 填写使用的端口是 8088
    server_in.sin_addr.s_addr = INADDR_ANY; // 表示接收任何的地址

    // 这里打开一个socket 参数说明: (AF_INET表示: 使用ipv4, socket_stream表示面向连接的稳定数据传输, 即TCP 协议, 
    // protocol = 0 表示会自动选择type类型对应的默认协议)
    // 最后获得一个socket 描述符, 并将这个描述符赋值给server_fd.
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 使用bind函数， 将socket_fd描述符　和　server_in地址结构体　绑定在一起，　并进行异常处理
    if(bind(server_fd, (struct sockaddr*) &server_in, sizeof(server_in)) < 0) {
        fprintf(stderr, "bind error!\n");
        exit(1);
    }

    // 这里使用listen 函数来监听这个socket, 并使用第二个参数表示，　这个socket　可以排队的最大连接数
    if(listen(server_fd, 5) < 0) {
        fprintf(stderr, "listen error!\n");
        exit(1);
    }

    // 这里是提示用户server 程序已经开始
    cout << "begin" << endl;

    // 调用accept()函数取接收请求，这样连接就建立好了
    // 这里程序开始忙等待，　知道client端使用connect() 函数
    client_fd = accept(server_fd, (struct sockaddr*) &client_fd, &len);

    //　这里提示用户建立的连接的简单信息
    cout << "connected with" << client_in.sin_addr.s_addr << "::" << client_in.sin_port << endl;
    while(client_fd >= 0){
        while(read(client_fd, buf, 1024) != 1024);
        if(!strcmp(buf, "q\n")) {
            //client close
            cout << "client close!" << endl;
            close(client_fd);
            client_fd = -1; //to loop out of this connection
            break;
        }    
        cout << buf ;
        cout << ">>>";
        fgets(message, 1024, stdin); 
        while(write(client_fd, (void *)message, 1024*sizeof(char)) != 1024){
            // 发送发生异常, 重新输入
            cout << ">>>";
            fgets(message, 1024, stdin); 
        }
        if(!strcmp(message, "q\n")){
            //server close
            cout << "server close!" << endl;
            close(client_fd);
            client_fd = -1;
            break;
        }
    }
    close(server_fd);
    return 0;
}

