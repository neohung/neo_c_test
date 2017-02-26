#ifndef __PACKET_H_
#define __PACKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <string.h>
#include <arpa/inet.h>

/**
 * Maximum size of packet data
 */
#define PACKET_MAX_DATA 64	
#define PACKET_STAT_OK 0
#define PACKET_STAT_ERR_LENGTH -1
#define PACKET_STAT_ERR_CRC -2
#define PACKET_STAT_ERR_UNKPACK -3
#define PACKET_STAT_ERR_DATA -4

typedef struct{
  /**
   * 封包開始欄位
   */
  unsigned char  start;
  /**
   * 封包總長度
   */
  unsigned char  length;
  /**
   * 封包類別編號
   */
  unsigned char  type;
  /**
   * 封包內容
   */
  unsigned char  data[PACKET_MAX_DATA];
  /**
   * CRC
   */

  unsigned char  crc;
} packet;

typedef struct{
  /**
   * 封包類別編號
   */
  unsigned char  type;
  /**
   * 回呼函數
   */ 
  int (*callback_func)(unsigned char* data, unsigned char ndata);
} packet_recv_handler;

typedef struct{
  /**
   * packet_recv_handler數量
   */
   unsigned char count;
   /**
    * packet_recv_handler矩陣
    */
   packet_recv_handler handlers[];
} packet_recv_handlers;

/**
 *  @brief 計算packet內的crc
 *  @param[in] *pke為指針指向要計算的packet封包
 *  @return    傳回CRC值
 */
unsigned char packet_calc_crc(packet *pkt);
/**
 *  @brief 用packet_calc_crc計算packet內的crc後比對是否跟pkt->crc內容一致
 *  @param[in] *pke為指針指向要檢查的packet封包的
 *  @return    傳回1表示正確, 0表示錯誤
 */
int packet_check_crc(packet *pkt);

/**
 *  @brief 實作傳送封包置入queue的函數
 *  @param[in] pkt_byte為要置入queue的byte內容
 *  @return    無
 */
void packet_byte_to_send_queue(unsigned char pkt_byte);

/**
 *  @brief 實作從queue讀出接收封包的函數
 *  @param[in] *pke為指針指向要回傳的packet封包 
 *  @return    
 */
unsigned char packet_byte_from_recv_queue(void);


int packet_send(packet *pkt);
int packet_receive(packet *pkt, unsigned char start);

#endif
