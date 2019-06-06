#ifndef NETEXP_H
#define NETEXP_H


#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>


#define		TCP_SERVER_ADDRESS		"127.0.0.1"
#define 	TCP_SERVER_PORT			8001
#define		TCP_BUF_LENGTH			1000
#define 	CONN_NUM			10

#define		UDP_SERVER_ADDRESS		"127.0.0.1"
#define		UDP_SERVER_PORT			8002 
#define		UDP_BUF_LENGTH			1000

#define		RDT_SERVER_ADDRESS		"127.0.0.1"
#define		RDT_SEND_LFILE_NAME		"data_long_send.mp4"
#define 	RDT_RECV_LFILE_NAME		"data_long_recv.mp4"
#define		RDT_SEND_SFILE_NAME		"abc_send.pdf"
#define 	RDT_RECV_SFILE_NAME		"abc_recv.pdf"
#define		RDT_ACK_MSG				"SUCC"
#define		RDT_NACK_MSG			"FAIL"		
#define 	RDT_RECV_PORT			8003
#define		RDT_SEND_PORT			8004
#define		RDT_BEGIN_SEQ			1
#define		RDT_SENDWIN_LEN			10

#define		RDT_PKT_LOSS_RATE		10
#define		RDT_TIME_OUT			50000
#define		RDT_HEADER_LEN			(4 + 4)
#define 	RDT_DATA_LEN			1000
#define		RDT_PKT_LEN			( RDT_DATA_LEN + RDT_HEADER_LEN )

#define		RDT_CTRL_BEGN			0
#define		RDT_CTRL_DATA			1
#define 	RDT_CTRL_ACK			2
#define		RDT_CTRL_END			3



typedef struct _STATE_PKT
{
	struct timeval send_time;
	int pkt_seq;
	int pkt_len;
	int state; //init 0 , sent 1 , acked 2 , timeout 3 , empty 4
	char rdt_pkt[RDT_PKT_LEN];
}STATE_PKT;

typedef struct _SLD_WIN
{
	//[send_left, send_right) sequence number
	int win_len;
	int send_left;
	int send_right;
	STATE_PKT rdt_pkts[RDT_SENDWIN_LEN];
	pthread_mutex_t lock;
}SLD_WIN;


int pack_rdt_pkt( char *data_buf, char *rdt_pkt, int data_len, int seq_num, int flag );
int unpack_rdt_pkt( char *data_buf, char *rdt_pkt, int pkt_len, int *seq_num, int *flag );
void udt_sendto( int sock_fd, char *pkt, int pkt_len, int flags, struct sockaddr *recv_addr, int addr_len );
int time_out( struct timeval time_1, struct timeval time_2 );


#endif
