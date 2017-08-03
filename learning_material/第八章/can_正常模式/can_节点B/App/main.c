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


#define CAN_RX_MB       MB_NUM_6            //����MBs��������


uint8           can_rx_flag     = 0;        //���յ����ݱ�־
uint8           can_rx_data[8+1];           //���յ�������
uint8           can_rx_len;                 //���յ������ݳ���
CAN_USR_ID_t    can_rx_id;                  //���յ���ID��

void can1_mb_handler(void);                 //���� CAN1���Ļ������жϷ�����



/*! 
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ��CAN���ز���ʵ��
 */
void  main(void)
{            
    CAN_USR_ID_t    can_my_id       = {0x85,0,0};               //����ID

    printf("\n\nCAN �ڵ�B���ղ���");
    
    can_init(CAN1,CAN_BAUD_20K,CAN_LOOPBACK,CAN_CLKSRC_BUS);                   //��ʼ�� CAN1 �������� 20Kb/s �� ����ģʽ  ,bus  ʱ����Ϊʱ��Դ

    can_rxbuff_enble(CAN1,CAN_RX_MB,can_my_id);                 //ʹ�ܽ��ջ�����

    set_vector_handler(CAN1_ORed_MB_VECTORn,can1_mb_handler);   //����CAN�����жϷ��������ж�������
    can_irq_en(CAN1,CAN_RX_MB);                                 //ʹ��can�����ж�
    
    while(1)
    {
        if(can_rx_flag )                                        //�ж��Ƿ����������ж�
        {
            
            can_rx_flag = 0;
            
            printf("\n\n���յ� CAN ����!");
            
            printf("\n���� ID  : 0x%X",*(uint32 *)&can_rx_id);  //��ӡ ���� ID

            printf("\n���ĳ��� : 0x%X",can_rx_len);             //��ӡ ���ݳ���

            can_rx_data[can_rx_len] = 0;                        //ȷ�������ַ������� 0 ��β

            printf("\n�������� : %s",can_rx_data);              //��ӡ ��������
            
        }

        
        DELAY_MS(1000);
        
    }
}



/*! 
 *  @brief      CAN1���Ļ������жϷ�����
 *  @since      v5.0
 */
void can1_mb_handler(void)
{   
    can_rx(CAN1,CAN_RX_MB,&can_rx_id,&can_rx_len,can_rx_data);  //CAN �� CAN_RX_MB �������� �����յ��� ID ������ can_rx_id ����ȱ����� can_rx_len�����ݱ����� can_rx_data
    
    if(can_rx_len != 0)
    {
        can_rx_flag = 1;
    }
    else
    {
        can_rx_flag = 0;
    }
    
    can_clear_flag(CAN1,CAN_RX_MB);                             //����������жϱ�־λ
}

