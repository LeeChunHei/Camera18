/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ���ѧ��̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"

#define CAN_TX_MB       MB_NUM_7            //����MBs��������
#define DATA_LEN        8                   //can ���͵����ݳ��ȣ����Ϊ8


/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ��CAN �ڵ� A ���Ͳ���
 */
void  main(void)
{


    uint8           txbuff[10]      = {"wildvcan"};             //��Ҫ���͵�����
    CAN_USR_ID_t    can_tx_id       = {0x8F,0,0};               //����ID��

    printf("\n\nCAN �ڵ�A���Ͳ���");

    can_init(CAN1,CAN_BAUD_20K,CAN_NORMAL,CAN_CLKSRC_BUS);                     //��ʼ�� CAN1 �������� 20Kb/s �� ����ģʽ  ,bus  ʱ����Ϊʱ��Դ

    while(1)
    {
        can_tx(CAN1,CAN_TX_MB,can_tx_id,DATA_LEN, txbuff);  //CAN�������ݡ�������CAN_TX_MB������ID:tx_ID�����ݻ�����txbuff������ DATA_LEN

        DELAY_MS(1000);
    }
}


