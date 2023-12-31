#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 1024

void write_file(int sockfd, struct sockaddr_in addr){
  FILE *fp;
  char *filename = "recv.txt";
  int n;
  char buffer[SIZE];
  socklen_t addr_size;

  fp = fopen(filename, "w");

  while(1){

    addr_size = sizeof(addr);
    n = recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, &addr_size);

    if (strcmp(buffer, "END") == 0){
      break;
      return;
    }

    printf("receiving data: %s", buffer);
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);

  }

  fclose(fp);
  return;
}

int main(){
  char *ip = "127.0.0.1";
  int port = 8080;

  int server_sockfd;
  struct sockaddr_in server_addr, client_addr;
  char buffer[SIZE];
  int e;

  server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_sockfd < 0){
    perror("socket error");
    exit(1);
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (e < 0){
    perror("bind error");
    exit(1);
  }

  printf("Server started. \n");
  write_file(server_sockfd, client_addr);

  printf("Data transfer complete.\n");
  printf("Closing the server.\n");

  close(server_sockfd);

  return 0;
}
