#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "simple_socket.h"

int main(int argc, char * argv[]){

	/* Communication */
	char buffer[1024];
	ssize_t message_size;
	int end = 0;
	char * address = argv[1];
	int port = atoi(argv[2]);
	printf("[+] Waiting connection at %s:%d\n", address, port);
	int socket_1 = server(address, port);
	while (!end){
	
		/* Cleans the buffer */
		for (int c = 0; c < 1024; c++){
			buffer[c] = '\0';
		}
		
		/* Receives and prints all the messages */
		message_size = read(socket_1, &buffer, 1024-1);
		if (message_size != -1){	
			printf("Message size: %d\n", message_size);
			printf("Message: %s\n", buffer);
			end = buffer[0] == 'e' && buffer[1] == 'n' && buffer[2] == 'd';
		}
	}


	/* Liberates socket file descriptor */
	close(socket_1);
	return 0;
}
