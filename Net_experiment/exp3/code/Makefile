all: udp_server.cpp udp_client.cpp server.cpp client.cpp
	g++ -Wall -g udp_server.cpp -o udp_server
	g++ -Wall -g udp_client.cpp -o udp_client
	g++ -Wall -g server.cpp -o server
	g++ -Wall -g client.cpp -o client

.PHONY: clean
clean:
	rm udp_server udp_client server client udp_server_data

udp_server: udp_server.cpp
	g++ -Wall -g udp_server.cpp -o udp_server

udp_client: udp_client.cpp
	g++ -Wall -g udp_client.cpp -o udp_client

server: server.cpp
	g++ -Wall -g server.cpp -o server

client: client.cpp
	g++ -Wall -g client.cpp -o client
