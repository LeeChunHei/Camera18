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

void PORTE_IRQHandler();

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       SPI ���� NRF24L01+
 */
void main(void)
{
    uint32 i=0;
    uint8 buff[DATA_PACKET];
    uint8 *str = "��ӭʹ��ɽ�� K60�����壡";

    printf("\n\n\n***********����ģ��NRF24L01+����************");

    while(!nrf_init())                  //��ʼ��NRF24L01+ ,�ȴ���ʼ���ɹ�Ϊֹ
    {
        printf("\n  NRF��MCU����ʧ�ܣ������¼����ߡ�\n");
    }
    set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler);    			//���� PORTE ���жϸ�λ����Ϊ PORTE_VECTORn
    enable_irq(PORTE_IRQn);

    printf("\n      NRF��MCU���ӳɹ���\n");

    while(1)
    {
        sprintf((char *)buff,"%s%d",str,i);         //��str��i�ϲ���һ���ַ�����buff��ٽ��з���
        nrf_tx(buff,DATA_PACKET);                   //����һ�����ݰ���buff����Ϊ32�ֽڣ�

        //�ȴ����͹����У��˴����Լ��봦������


        while(nrf_tx_state() == NRF_TXING);         //�ȴ��������


        if( NRF_TX_OK == nrf_tx_state () )
        {
            printf("\n���ͳɹ�:%d",i);
            i++;                                    //���ͳɹ����1������֤�Ƿ�©��
        }
        else
        {
            printf("\n����ʧ��:%d",i);
        }
        DELAY_MS(10);
    }
}

/*!
 *  @brief      PORTE�жϷ�����
 *  @since      v5.0
 */
void PORTE_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    flag = PORTE_ISFR;
    PORTE_ISFR  = ~0;                                   //���жϱ�־λ

    n = 27;
    if(flag & (1 << n))                                 //PTE27�����ж�
    {
        nrf_handler();
    }
}