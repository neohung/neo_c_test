#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <string.h>
#include <arpa/inet.h>

#include "udp.h"

#define MAXNAME 1024
#define MAXDATA   1024

void* ReadFunc(void* ptr)
{
  char *message;
  message = (char *) ptr;
  printf("ReadFunc [%s]\n",message);
  pthread_exit((void *)1234);
}


//socket() -> bind() -> recvfrom() -> sendto()
udp create_udpserver(int SERV_PORT)
{
  udp u;
  if ((u.socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) <0) {
    perror ("socket failed");
    exit(EXIT_FAILURE);
  }
  memset((char *) &u.addr, 0, sizeof(u.addr));
  u.addr.sin_family = AF_INET;
  u.addr.sin_port = htons(SERV_PORT);
  u.addr.sin_addr.s_addr = htonl(INADDR_ANY);
  //bind socket to port
  if( bind(u.socket_fd , (struct sockaddr*)&u.addr, sizeof(u.addr) ) < 0)
  {
    perror ("bind failed\n");
    exit(EXIT_FAILURE);
  }
  
  char *message1 = "Thread 1";
  void *ret;
  pthread_create(&u.readtid, NULL, ReadFunc, (void*) message1);
  pthread_join( u.readtid, &ret);
  printf("return value from thread1 = %d\n",ret);
  return u;
}


int udpserver(int SERV_PORT)
{
 printf("%s\n",__func__);

 int socket_fd;  
struct sockaddr_in si_me;
 if ((socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) <0) {
                perror ("socket failed");
                exit(EXIT_FAILURE);
        }   

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(SERV_PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(socket_fd , (struct sockaddr*)&si_me, sizeof(si_me) ) < 0)
    {
	 perror ("bind failed\n");
                exit(1);
    }
	return socket_fd;
}

int udpserver_read(int socket_fd, char* buf, struct sockaddr_in* pclient_addr, socklen_t* plength)
{
 int nbytes; /* the number of read **/
 if ((nbytes = recvfrom(socket_fd, buf, MAXNAME, 0, (struct sockaddr*)pclient_addr, (socklen_t *)plength)) <0)
        {
            perror ("could not read datagram!!");
        }

 return nbytes;
}

int udpserver_send(int socket_fd, struct sockaddr_in* pclient_addr, socklen_t* plength, char* data, int ndata)
{
    if (sendto(socket_fd , data, ndata , 0 , (struct sockaddr*) pclient_addr, *plength)==-1)
        {
                perror("write to server error !");
                exit(1);
        }
  return 0;
}

//socket() -> sendto()/recvfrom()
int udpclient(void)
{
        int fd;     /* fd into transport provider */
        if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
                perror ("socket failed!");
                exit(1);
        }
	return fd;
}

int udpclient_send(int client_socket_fd, char* SERVER, int SERV_PORT, char* data, int ndata)
{
     struct sockaddr_in si_other;
     int slen=sizeof(si_other);
    //Change SERVER to sin_addr
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(SERV_PORT);   
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    if (sendto(client_socket_fd, data, ndata , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
                perror("write to server error !");
                exit(1);
        }
  return 0;
}

int udpclient_read(int client_socket_fd, char* buf)
{
  int nbytes; /* the number of read **/
 struct sockaddr server_addr; /* address of client    */
 int length = sizeof(server_addr); /* length of address structure      */
 if ((nbytes = recvfrom(client_socket_fd, buf, MAXNAME, 0, (struct sockaddr*)&server_addr, (socklen_t *)&length)) <0)
        {
            perror ("could not read datagram!!");
        }

 return nbytes;
}

