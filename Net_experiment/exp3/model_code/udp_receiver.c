#include "net_exp.h"

int main( int argc, char **argv )
{
	struct sockaddr_in recv_addr, clet_addr;
	int sin_len;
	char recv_buf[UDP_BUF_LENGTH];
	int sock_fd;
	int pkt_len;
	
	memset( &recv_addr,  );
	memset( &recv_addr,  );
	recv_addr.sin_family = ;
	recv_addr.sin_addr.s_addr = ;
	recv_addr.sin_port = ;
	
	if( ( sock_fd = socket(   ) == -1 )
	{
			
	}
	
	if( bind(   ) == -1 )
	{
			
	}
	while(1)
	{
		memset( recv_buf, sizeof(recv_buf), 0 );
		sin_len = sizeof( clet_addr );
		pkt_len = recvfrom(   );
		recv_buf[pkt_len] = '\0';
		printf( "[UDP_RECEIVER] receive msg[%d bytes]\n", pkt_len );
		printf( "\t%s\n", recv_buf );
	}
	
	close(   );
	return 0;
}

