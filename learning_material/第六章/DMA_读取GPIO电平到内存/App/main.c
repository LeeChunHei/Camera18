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
#include "math.h"

#define DMA_COUNT   10

uint8 BUFF[DMA_COUNT + 1];     //�������飬Ԥ��һ��

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� DMA ʵ�� ����Ҫ�̽� PTA6 �� PTA7 ���������ַ������ݿ��ƴ���
 */
void  main(void)
{
    uint8 i;
    char command;

    gpio_init  (PTA6, GPO, LOW);                        //��ʼ�� PTA6 Ϊ����͵�ƽ

    dma_portx2buff_init (DMA_CH0, (void *)&PTB_B0_IN, BUFF, PTA7, DMA_BYTE1, DMA_COUNT, DADDR_RECOVER);
            //DMA��ʼ����Դ��ַ��PTB_B0_IN��Ŀ�ĵ�ַ��buff,PTA7����(Ĭ��������)��ÿ�δ���1�ֽڣ������� DMA_COUNT �� �����������ָ���ַ

    port_init_NoALT(PTA7,DMA_FALLING );

    DMA_EN(DMA_CH0);                        //ʹ��DMA Ӳ������

    while(1)
    {
        uart_getchar(VCAN_PORT,&command);   //ͨ������������PTA6���������PTA7������

        //��������
        PTA6_T = 1;           //ȡ��
        DELAY_MS(1);
        PTA6_T = 1;           //ȡ��


        //��ӡ BUFF �Ļ���������(�����û������������ݵı仯)
        printf("\nDMA������ BUFF[%d]={",DMA_COUNT);
        for(i = 0;i < DMA_COUNT ; i++)
        {
            printf("%d,",BUFF[i]);
        }
        printf("%d};",BUFF[DMA_COUNT]);

    }
}
