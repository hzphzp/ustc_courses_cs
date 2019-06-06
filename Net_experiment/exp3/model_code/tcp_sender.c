#include "net_exp.h"

int main( int argc, char **argv )
{
	struct sockaddr_in recv_addr;
	int sock_fd;
	char *msg = "hello";
	char recv_buf[TCP_BUF_LENGTH]; 
	int pkt_len = 0;
	
	memset( &recv_addr,  );
	recv_addr.sin_family =  ;
	recv_addr.sin_port =  ;
	recv_addr.sin_addr.s_addr =  ;
	
	if( ( sock_fd = socket(  ) ) == -1 )
	{
		  
	}
	
	if( connect(   ) == -1 )
	{
		  
	}
	
	send(   );
	pkt_len = recv(   );
	if( pkt_len == -1 ) /* error */
	{
		
	}
	
	if( pkt_len == 0 ) /* the remote side has closed the connection */
	{
		exit(1);
	}
	recv_buf[pkt_len] = '\0';
	printf( "[TCP SENDER] receive echo msg[%d bytes]\n", pkt_len );
	printf( "\t%s\n",  recv_buf );
	close( sock_fd );
	return 0;
}
