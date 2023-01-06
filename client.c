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
int option; //store the values of the menu

int execute(char buffer[1024]){
	while(1){
		if(system(buffer) != 0){       //ie what is in buffer is ran by the sys cmd in variable called buffer
			break;                   //if it executes and returnes value diff from zero implies failure hence break
		}
		fgets(buffer, 1024, stdin);     //collects from second input etc and executes here
		
	
   }
return 0;
}



int main(int argc, char * argv[]){
 		  char *ip;
		  int port;		//stores value of port number

		  int sock;
		  struct sockaddr_in addr;
		  socklen_t addr_size;
		  char buffer[1024];
		  int n;
		  
		  if (argc<3)		//stores filename? ip and port num indexes ie lenght of array
		  {
		    printf("provide required command-line inputs as- <filename.c> <server_IP_addr> <port>");
		    exit(1);
		  }
		  port = atoi(argv[2]);		 //atoi is predefined func ie at position 2 get port num
		  sock = socket(AF_INET, SOCK_STREAM, 0);             //default
		  // check if socket is created properly
		  if (sock < 0){			//ie if one of the parameters above is missing, error
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

while(1){		 //ensures you don't leave the application
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
		  n = write(sock, buffer, strlen(buffer));		//here client writes message to server
		  if (n <0)
		  {
		  	printf("Error in writing...");
		  	exit(1);
		  }

		  bzero(buffer, 1024); // clear buffer
		  n = read(sock, buffer, 1024);			//here client reads message from server
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
		fgets(buffer, 1024, stdin);		//very effective compared to scanf
		execute(buffer);
	
	}
	else if(option == 3){
		break;
	//enter code for file transfer
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
