#include "net_exp.h"

void usage( char **argv )
{
	printf( "wrong argument!\n" );
	printf( "usage: %s save_file_name\n",  argv[0] );
}

/*
	Go-Back-N 协议接收端接受函数
	输入参数：
		save_file_name： 保存文件名
		sock_fd：接受数据的socket
*/
int receive_file( char *save_file_name, int sock_fd )
{
	int client_addr_length;
	char reply_pkt_buf[RDT_PKT_LEN];
	int reply_pkt_len;
	
	char rdt_pkt[RDT_PKT_LEN];
	char rdt_data[RDT_DATA_LEN];
	uint32_t seq_net_order;
	int seq_num;
	int flag;
	int exp_seq_num;
	
	int total_recv_byte = 0;
	
	struct sockaddr_in client_addr;
	int i, j, sin_len, pkt_len, data_len;
	
	int counter = 1;
	FILE *fp;
	
	if( (fp = fopen( save_file_name, "w" )) == NULL )
	{
		printf( "open file : %s failed.\n",  save_file_name );
		return 1;
	}
	
	memset( &client_addr, 0, sizeof(client_addr) );
	sin_len = sizeof( client_addr );

	exp_seq_num = RDT_BEGIN_SEQ;
	
	//TODO
	while(1) //接收RDT数据包，直到所有数据全部接收完毕
	{			
		/*
			1.如果是RDT_CTRL_END的话, 分析发送端代码可知, 这里的包是直接用sendto函数
			  发的, 而不是用会丢包的udt_sendto, 而且发送端发送之后就直接关闭程序了, 故
			  接收端收到后也不用回复ack, 直接跳出循环然后结束程序即可.
			2.recvfrom()函数收到包并对包解析
			3.如果是要的包序号, 则写入文件,并且回复ack
			4.如果不是要的包序号, 不能返回ack,应该什么都不做, 然后等发送端超时.
		*/													
		if(flag == RDT_CTRL_END){
			// 发送端的数据已经结束
			// 跳出循环, 停止程序
				break;
		}

		pkt_len = recvfrom(sock_fd, (void *) rdt_pkt, RDT_PKT_LEN, 0, (struct sockaddr *) &client_addr, (socklen_t *) &client_addr_length);
		if (pkt_len < 0) {
			// 包残缺
			fprintf(stderr, "recvfrom wrong!\n");
		}

		data_len = unpack_rdt_pkt(rdt_data, rdt_pkt, RDT_PKT_LEN, &seq_num, &flag);
		if(seq_num == exp_seq_num){
			// 如果就是想要的包序号, 写入文件, 增加期望序号数, 回复ack
			if(fwrite((void *)rdt_data, sizeof(char), RDT_DATA_LEN, fp) != RDT_DATA_LEN) {
				fprintf(stderr, "file write error!\n");
			}
			printf("receive data is %s\n", rdt_data);
			printf("add to the file\n");
			printf("%d\n", data_len);
			total_recv_byte += data_len;
			printf("%d\n", total_recv_byte);
			exp_seq_num ++;
			reply_pkt_len = pack_rdt_pkt(NULL, reply_pkt_buf, 0, seq_num, RDT_CTRL_ACK);
			udt_sendto(sock_fd, reply_pkt_buf, reply_pkt_len, 0, (struct sockaddr *) &client_addr, client_addr_length);
		}

		// 注意这里如果不是想要的exp_seq_num 的话, 不能发送ack回去
	}
	printf( "\n\nreceive file succeed. write to file %s\ntotal recv %d byte\n", 
				save_file_name, total_recv_byte );
		
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
	
	srand ( time(NULL) );
	
	if( argc != 2 )
	{
		usage( argv );
		exit(0);
	}
	
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


