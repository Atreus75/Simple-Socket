#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>


/* Returns the socket file descriptor if a connection is succesfully done */
int simple_client(char * address, int port){
	int sock_fd, connection_fd;
	/* Sets file descriptor for the socket */
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		return -1;
	}

	/* Sets primary IP address and port informations */
	struct sockaddr_in addr_info;
	if ((inet_pton(AF_INET, address, &addr_info.sin_addr)) <=0){
		return -2;
	}
	addr_info.sin_port = htons(port);
	addr_info.sin_family = AF_INET;
	socklen_t address_size = sizeof(addr_info);

	/* Connects to the target */
	int status;
	if ((status = connect(sock_fd, (struct sockaddr *)&addr_info, address_size)) < 0){
		return -3;
	}
	return sock_fd;

}


/* Returns the connection file descriptor if a connection is succesfully done. At this moment, the servers only handle 1 connection per port. */
int server(char * address, int port){
	/* Sets file descriptors for the socket. */
	int sock_fd, connection_fd;
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		return -1;
	}

	/* Sets primary IP address and port informations */
	struct sockaddr_in addr_info;
	if (inet_pton(AF_INET, address, &addr_info.sin_addr) <= 0){
		return -2;
	}
	addr_info.sin_family = AF_INET;
	addr_info.sin_port = htons(port);
	socklen_t addr_size = sizeof(addr_info);
	
	/* Binds to the specified address and port. */
	if ((bind(sock_fd, (struct sockaddr*)&addr_info, addr_size)) == -1){
		return -3;
	}

	/* Listens until a connection is done. */
	listen(sock_fd, 1);
	connection_fd = accept(sock_fd, (struct sockaddr*)&addr_info, &addr_size);
	return connection_fd;
}
