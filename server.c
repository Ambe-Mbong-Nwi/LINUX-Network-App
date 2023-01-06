#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>
char buffer[1024];
int option;		//store the values of the menu
int execute(char buffer[1024]){
	while(1){
		if(system(buffer) != 0){		  //ie what is in buffer is ran by the sys cmd in variable called buffer
			break;				 //if it executes and returnes value diff from zero implies failure hence break
		}
		fgets(buffer, 1024, stdin);		//collects from second input etc and executes here
		
	
   }
return 0;
}


int main(int argc, char * argv[]){                //argv is array pointer, argc is variable
		  char *ip;
		  int port;               //stores value of port number

		  int server_sock, client_sock;
		  struct sockaddr_in server_addr, client_addr;  
		  socklen_t addr_size;
		  char buffer[1024];
		  pid_t childpid;     //stores parent and child pids
		  int n;
		  
		  if (argc<2)         //stores ip and port num indexes ie lenght of array
		  {
		    printf("provide required command line inputs as <filename.c> <server_IP_addr> <portno>");
		    exit(1);
		  }
		  port = atoi(argv[1]);       //atoi is predefined func ie at position 1 get port num
		  server_sock = socket(AF_INET, SOCK_STREAM, 0);      //default
		  if (server_sock < 0){           //ie if one of the parameters above is missing, error
		    perror("[-]Socket error");
		    exit(1);
		  }
		  printf("[+]TCP server socket created.\n");

		  //memset(&server_addr, '\0', sizeof(server_addr));
		  server_addr.sin_family = AF_INET;
		  server_addr.sin_port = htons(port);
		  server_addr.sin_addr.s_addr = INADDR_ANY;              //allows client input ip

		  n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));   //bind creates a duplex or tunnel between client and server
		  if (n < 0){
		    perror("[-]Bind error");
		    exit(1);
		  }
		  printf("[+]Bind to the port number: %d\n", port);
		  // listen to the client socket
		  listen(server_sock, 5);                      //listen takes the server socket and channel 5 for the communication to go through
		  printf("Listening...\n");
		  


printf("################################################################");
printf("\nWelcome Server to NetApp");
printf("\nWHich feature do you want to use, select by number");

while(1){       //ensures you don't leave the application
	printf("\n1: Messaging\n2: Running Commands\n3: File Sharing\n4: Exit\n");
	scanf("%d", &option);
	if(option == 1){
		  
		  while(1)                     
		{
			  
			  addr_size = sizeof(client_addr);   //so server gets size of address
			  client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);       //client socket accepts to talk via bind channel
			  printf("[+]Client connected\n");
			  // checking if the client socket is created properly
			  if (client_sock < 0)
			  {
			    printf("Error accepting request../");
			    	exit(1);
			  }
			  printf("[+]Client connected.\n");
			  // creating multiple clients
		 	  if((childpid = fork()) == 0){        
		 	  	close(server_sock);                 //blocks server port and permit client to talk first.
		 	  	while(1){
		 	  		if (!strncmp("end", buffer, 3))                 //end communication between client and server, stored in buffer, 3 characters long
		  				{
		  				   printf("[+]Client disconnected\n\n");
		  				   break;
		 	  		}else{
		 	  		
						   bzero(buffer, 1024);
						   n = read(client_sock, buffer, 1024);          //here server reads message from client
						   if (n < 0)
						   {
						      printf("Error in reading...");
						      exit(1);
						   }
						   //recv(client_sock, buffer, sizeof(buffer), 0);
						   printf("\nClient --> %s", buffer);
						   
						   
						  bzero(buffer, 1024);
						  fgets(buffer, 1024, stdin);
						  //execute(buffer);
						  n = write(client_sock, buffer, 1024);                //server writing to client
						  
						  if (n < 0)
						  {
						    printf("Error in writing...");
						    exit(1);
						  }
					}
				}
			}
		  //strcpy(buffer, "HI, THIS IS SERVER. HAVE A NICE DAY!!!");
		  
		 }
		  //printf("Server: %s\n", buffer);
		  //send(client_sock, buffer, strlen(buffer), 0);
		   close(client_sock);               //ends connections
		   close(server_sock);
		   
			
	}
	else if(option == 2){
		printf("Enter a command\n");
		fgets(buffer, 1024, stdin);    //very effective compared to scanf
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
