#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char * argv[]){

  char *ip;
  int port;

  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  char buffer[1024];
  int n;
  
  if (argc<2)
  {
    printf("provide required command line inputs as <filename.c> <server_IP_addr> <portno>");
    exit(1);
  }
  port = atoi(argv[1]);
  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");

  //memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0){
    perror("[-]Bind error");
    exit(1);
  }
  printf("[+]Bind to the port number: %d\n", port);
  // listen to the client socket
  listen(server_sock, 5);
  printf("Listening...\n");

  
  addr_size = sizeof(client_addr);
  client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
  printf("[+]Client connected.\n");
  // checking if the client socket is created properly
  if (client_sock < 0)
  {
    printf("Error accepting request../");
    	exit(1);
  }
  printf("[+]Client connected.\n");
  while(1)
{
   bzero(buffer, 1024);
   n = read(client_sock, buffer, 1024);
   if (n < 0)
   {
      printf("Error in reading...");
      exit(1);
   }
   //recv(client_sock, buffer, sizeof(buffer), 0);
   printf("\nClient --> %s", buffer);
   
  bzero(buffer, 1024);
  fgets(buffer, 1024, stdin);
  n = write(client_sock, buffer, 1024);
  
  if (n < 0)
  {
    printf("Error in writing...");
    exit(1);
  }
  //strcpy(buffer, "HI, THIS IS SERVER. HAVE A NICE DAY!!!");
  if (!strncmp("end", buffer, 3))
  {
  	break;
  }
 }
  //printf("Server: %s\n", buffer);
  //send(client_sock, buffer, strlen(buffer), 0);
   close(client_sock);
   close(server_sock);
   printf("[+]Client disconnected.\n\n");

  

  return 0;
}
