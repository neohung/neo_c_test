
#include "udp.h"
int main(void)
{
  int id = udpserver(1234);
  char buf[1024];
  struct sockaddr_in client_addr;
  socklen_t l;
  int c=0;
while(1){
  c++;
  int n =0;
  while (!n){
    n = udpserver_read(id, buf, &client_addr, &l);
  }
  buf[n] = '\0';
  printf("buf=[%s]\n",buf);
  printf("Received packet from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
  n = sprintf(buf,"SERVER say %d",c);
  udpserver_send(id, &client_addr, &l, buf, n);
}
  return 0;
}
