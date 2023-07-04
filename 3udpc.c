#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SIZE 1024

void send_file_data(FILE *fp, int sockfd, struct sockaddr_in addr){
  int n;
  char buffer[SIZE];


  while(fgets(buffer, SIZE, fp) != NULL){
    printf("sending data: %s", buffer);

    n = sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
    if (n == -1){
      perror("error sending data to the server.");
      exit(1);
    }
    bzero(buffer, SIZE);

  }

  strcpy(buffer, "END");
  sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));

  fclose(fp);
  return;
}

int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int server_sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  char *filename = "send.txt";

  server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_sockfd < 0){
    perror("socket error");
    exit(1);
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  fp = fopen(filename, "r");
  if (fp == NULL){
    perror("error reading the file");
    exit(1);
  }

  send_file_data(fp, server_sockfd, server_addr);

  printf("Data transfer complete.\n");
  printf("Disconnecting from the server.\n");

  close(server_sockfd);
  return 0;
}
