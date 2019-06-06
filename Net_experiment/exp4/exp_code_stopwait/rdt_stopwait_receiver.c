#include "net_exp.h"

void usage( char **argv )
{
	printf( "wrong argument!\n" );
	printf( "usage: %s save_file\n",  argv[0] );
}

/*
	停等协议接收端接收函数
	输入参数：
		save_file_name： 保存文件名
		sock_fd：接收数据的socket
*/
int receive_file( char *save_file_name, int sock_fd )
{
	char reply_pkt_buf[RDT_PKT_LEN];
	int reply_pkt_len;
	
	char rdt_pkt[RDT_PKT_LEN];
	char rdt_data[RDT_DATA_LEN];
	int seq_num;
	int flag;
	int exp_seq_num; //当前接收端需要的数据包序列号
	
	int total_recv_byte = 0;
	
	struct sockaddr_in client_addr;
	int i, j, sin_len, pkt_len, data_len;
	
	FILE *fp; //将收到的RDT数据包按顺序写到此文件中
	if( (fp = fopen( save_file_name, "w" )) == NULL )
	{
		printf( "open file : %s failed.\n",  save_file_name );
		return 1;
	}
	
	memset( &client_addr, 0, sizeof(client_addr) );
	sin_len = sizeof( client_addr );
	
	exp_seq_num = RDT_BEGIN_SEQ;
	
	///TODO
	while(1) //接收RDT数据包，直到所有数据全部接收完毕
	{			
		/*
			step 1. 接收RDT数据包 :	recvfrom()
			step 2. 解封装RDT数据包 : unpack_rdt_pkt()
			step 3. 如果是RDT_CTRL_END, 返回ack后开启一个计时器, 如果计时器超时没有收到消息, 认为发送端收到这个ack
					接收端可以放心跳出循环, 程序了
			step 4. 检查此数据包是否为期待的数据包 : seq_num==exp_seq_num
					封装一个新的RDT数据包(ACK包) : pack_rdt_pkt()
					调用不可靠数据传输发送新的RDT数据包(ACK包): udt_sendto()
			step 5. 如果不是想要的包序号, 则数据不存入文件, 但是还是要返回ack(ack中的序号是 发送过来的那个序号) 
					这样来是发送端对seq_num进行更新

		*/
		pkt_len = recvfrom(sock_fd, rdt_pkt, RDT_PKT_LEN, 0, (struct sockaddr *) &client_addr, (socklen_t *) &sin_len);
		if(pkt_len < 0){
			//传输过程中包受损, 直接不做相应
			fprintf(stderr, "pkt recvfrom client error!\n");
			continue;
		}
		data_len = unpack_rdt_pkt((char *)rdt_data, (char *)rdt_pkt, RDT_PKT_LEN, &seq_num, &flag);
		if(flag == RDT_CTRL_END){
		label:
			//发送端的数据已经结束
			reply_pkt_len = pack_rdt_pkt(NULL, reply_pkt_buf, 0, exp_seq_num, RDT_CTRL_ACK);
			udt_sendto(sock_fd, reply_pkt_buf, reply_pkt_len, 0, (struct sockaddr *) &client_addr, sin_len);
			struct timeval timeout={5,0}; //set timeout for 2 seconds

			/* set receive UDP message timeout */

			setsockopt(sock_fd,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));

			/* Receive UDP message */
			pkt_len = recvfrom(sock_fd, rdt_pkt, RDT_PKT_LEN, 0, (struct sockaddr *)&client_addr, (socklen_t *) &sin_len);
			if (pkt_len > 0) {
				// 收到消息(RDT_CTRL_ACK)
				goto label;

			}
			else{
				// 没有在计时器时间内再次收到END消息, 认为发送端已经收到ACK, 并且关闭程序
				// 接收端也跳出循环, 关闭程序
				break;
			}
		}
		if(seq_num == exp_seq_num){
			// 是接收端期望的包序号
			// TODO: 这里怎么没有校验帧的正确性?

			// 写入文件
			if(fwrite((void *)rdt_data, sizeof(char), RDT_DATA_LEN, fp) != RDT_DATA_LEN) {
				fprintf(stderr, "file write error!\n");
			}
			printf("receive data is %s\n", rdt_data);
			printf("add to the file\n");
			printf("%d\n", data_len);
			total_recv_byte += data_len;
			printf("%d\n", total_recv_byte);
			
			// 更新数据包序号
			exp_seq_num ++;

			// 回复ACK
			reply_pkt_len = pack_rdt_pkt(NULL, reply_pkt_buf, 0, seq_num, RDT_CTRL_ACK);
			udt_sendto(sock_fd, reply_pkt_buf, reply_pkt_len, 0, (struct sockaddr *) &client_addr, sin_len);
		}
		else{
			//不是期望的包序号
			//返回还是ack(n), 但是不写入file
			printf("not the same seq num\n");
			printf("need #%d\n", exp_seq_num);
			printf("but receive #%d\n", seq_num);
			reply_pkt_len = pack_rdt_pkt(NULL, reply_pkt_buf, 0, seq_num, RDT_CTRL_ACK);
			udt_sendto(sock_fd, reply_pkt_buf, reply_pkt_len, 0, (struct sockaddr *) &client_addr, sin_len);
		}
	}
	
		
	printf( "\n\nreceive file succeed. write to file %s\ntotal recv %d byte\n", save_file_name, total_recv_byte );
		
	fflush( fp );
	fclose( fp );
	return 0;
}

int main( int argc, char **argv )
{
	struct sockaddr_in recv_addr;
	int sin_len;
	int sock_fd;
	int pkt_len;
	
	if( argc != 2 )
	{
		usage( argv );
		exit(0);
	}
	
	srand ( time(NULL) );
	
	memset( &recv_addr, 0, sizeof(recv_addr) );
	recv_addr.sin_family = AF_INET;
	recv_addr.sin_addr.s_addr = htonl( INADDR_ANY );
	recv_addr.sin_port = htons( RDT_RECV_PORT );
	
	if( ( sock_fd = socket( AF_INET, SOCK_DGRAM, 0 ) ) == -1 )
	{
		printf( "error! information: %s\n", strerror(errno) );
		exit(1);	
	}
	
	if( bind( sock_fd, (struct sockaddr *)&recv_addr, sizeof(recv_addr) ) == -1 )
	{
		close( sock_fd );
		printf( "error! information: %s\n", strerror(errno) );
		exit(1);	
	}
	
	if( receive_file( argv[1], sock_fd ) != 0 )
	{
		printf( "receive file %s failed.\n", argv[1] );
		close( sock_fd );
		exit(1);
	}
	
	close( sock_fd );
	return 0;
}

