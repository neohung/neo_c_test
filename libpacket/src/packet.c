#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <string.h>
#include <arpa/inet.h>

#include "packet.h"

unsigned char packet_calc_crc(packet *pkt)
{
  unsigned char i;
  unsigned char crc = 0;
  crc += pkt->start;
  crc += pkt->length;
  crc += pkt->type;
  //without start, length,type and crc 4 bytes
  for(i = 0; i < pkt->length - 4; i++) {
    crc += pkt->data[i];
  } 
	return crc;
}

int packet_check_crc(packet *pkt)
{
  if(packet_calc_crc(pkt) == pkt->crc) {
    return 1;
  }
  return 0;
}

int packet_send(packet *pkt)
{
 unsigned char  i;
 // check length
 if(pkt->length - 4 > PACKET_MAX_DATA) {
   return PACKET_STAT_ERR_LENGTH;
 }
 // write start byte
 packet_byte_to_send_queue(pkt->start);
 // write length
 packet_byte_to_send_queue(pkt->length);
 // write type
 packet_byte_to_send_queue(pkt->type);
 // write data
 for(i = 0; i < pkt->length - 4; i++) {	
   packet_byte_to_send_queue(pkt->data[i]); 
 }
 // write crc 
 packet_byte_to_send_queue(pkt->crc);
	 
 return PACKET_STAT_OK;
}
int packet_receive(packet *pkt, unsigned char start)
{
 unsigned char  i;
 // discard everything until start byte found in buffer
 while(packet_byte_from_recv_queue() != start);
 pkt->start = start;
 // read length
 pkt->length = packet_byte_from_recv_queue();	
 // check length
 if(pkt->length - 4 > PACKET_MAX_DATA) {
   return PACKET_STAT_ERR_LENGTH;
 }
 pkt->type = packet_byte_from_recv_queue();
 // read data
 for(i = 0; i < pkt->length - 4; i++) {	
   pkt->data[i] = packet_byte_from_recv_queue();
 }	
 // read crc 
 pkt->crc = packet_byte_from_recv_queue();
 // check crc
 if(!packet_check_crc(pkt)) {
   return PACKET_STAT_ERR_CRC;
 }
 return PACKET_STAT_OK;
}
