
#include "udp.h"
int main(void)
{
  int i;
  int id = udpclient();
for(i=0;i<10;i++){
  udpclient_send(id, "127.0.0.1", 1234, "neo", 3);
  int n = 0;
  char buf[1024];
  n = udpclient_read(id, buf);
  buf[n] = '\0';
  printf("Client got [%s]\n",buf);
}
  return 0;
}

