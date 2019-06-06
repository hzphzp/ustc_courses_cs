#include "net_exp.h"

int main( int argc, char **argv )
{
	struct sockaddr_in recv_addr;
	int sock_fd;
	int counter = 0;
	char recv_buf[UDP_BUF_LENGTH];	
	
	if( ( sock_fd = socket(  ) ) == -1 )
	{
		 
	}
	memset( &recv_addr, 0, sizeof(recv_addr) );
	recv_addr.sin_family = ;
	recv_addr.sin_addr.s_addr = ;
	recv_addr.sin_port = ;

	while(1)
	{
		memset( recv_buf, sizeof(recv_buf), 0 );
		printf("sending data packet with #: %d\n", counter );
		sprintf( recv_buf, "data packet with #: %d.",  counter );
		sendto(  );
		counter++; 
		if (counter== ) break;
		sleep(1);
	}
	
	close(  );
	return 0;
}

