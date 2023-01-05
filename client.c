#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
char buffer[1024];
int option;

int execute(char buffer[1024]){
	while(1){
		if(system(buffer) != 0){
			break;
		}
		fgets(buffer, 1024, stdin);
		
	
   }
return 0;
}



int main(int argc, char * argv[]){
 		  char *ip;
		  int port;

		  int sock;
		  struct sockaddr_in addr;
		  socklen_t addr_size;
		  char buffer[1024];
		  int n;
		  
		  if (argc<3)
		  {
		    printf("provide required command-line inputs as- <filename.c> <server_IP_addr> <port>");
		    exit(1);
		  }
		  port = atoi(argv[2]);
		  sock = socket(AF_INET, SOCK_STREAM, 0);
		  // check if socket is created properly
		  if (sock < 0){
		    perror("[-]Socket error");
		    exit(1);
		  }
		  printf("[+]TCP server socket created.\n");

		  //memset(&addr, '\0', sizeof(addr));
		  addr.sin_family = AF_INET;
		  addr.sin_port = htons(port);
		  addr.sin_addr.s_addr = inet_addr(argv[1]);

		  if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		  {
		    printf("Connection failed...!!!");
		    exit(1);
		  }
		  printf("Connected to the server.\n");

printf("################################################################");
printf("\nWelcome Client to NetApp");
printf("\nWHich feature do you want to use, select by number");

while(1){
	printf("\n1: Messaging\n2: Running Commands\n3: File Sharing\n4: Exit\n");
	scanf("%d", &option);
	if(option == 1){
		 
		  while(1)
		  {

		  bzero(buffer, 1024); // clear buffer
		  fgets(buffer, 1024, stdin);
		  //execute(buffer);
		  //strcpy(buffer, msg);
		 //printf("Client --> %s\n", buffer);
		  n = write(sock, buffer, strlen(buffer));
		  if (n <0)
		  {
		  	printf("Error in writing...");
		  	exit(1);
		  }

		  bzero(buffer, 1024); // clear buffer
		  n = read(sock, buffer, 1024);
		  if (n<0)
		  {
		  	printf("Error in reading...");
		  	exit(1);
		  }
		  printf("\nServer --> %s", buffer);
		  
		  if (!strncmp("end", buffer, 3))
		  	break;
		}

		  close(sock);
		  printf("Disconnected from the server.\n");

				   
			
	}
	else if(option == 2){
		printf("Enter a command\n");
		fgets(buffer, 1024, stdin);
		execute(buffer);
	
	}
	else if(option == 3){
		break;
	
	}
	else if(option == 4){
		break;
	}
	else{
		printf("\n %d is an invalid input\n", option);
	}



}








return 0;
}
