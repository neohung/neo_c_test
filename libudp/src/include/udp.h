#ifndef __UDP_U_
#define __UDP_H_


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct{
  int socket_fd;
  struct sockaddr_in addr;
  socklen_t addr_len;
  struct sockaddr_in client_addr;
  socklen_t client_addr_len;
  int port;
  char readbuf[1024];
  char* readbuf_point;
  int read_nbytes;
  char sendbuf[1024];
  char* sendbuf_point;
  int send_nbytes;
} udp;

int udpserver(int SERV_PORT);
//int udpserver_read(int socket_fd, char* buf, struct sockaddr* pclient_addr);
//int udpserver_send(int socket_fd, struct sockaddr client_addr, char* data, int ndata);
//int udpserver_send(int socket_fd, struct sockaddr* client_addr,int slen, char* data, int ndata);
int udpclient(void);
int udpclient_send(int client_socket_fd, char* SERVER, int SERV_PORT, char* data, int ndata);
int udpclient_read(int client_socket_fd, char* buf);

int udpserver_read(int socket_fd, char* buf, struct sockaddr_in* pclient_addr, socklen_t* plength);
int udpserver_send(int socket_fd, struct sockaddr_in* pclient_addr, socklen_t* plength, char* data, int ndata);

#endif
