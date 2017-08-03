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

volatile uint8 dmaflag = 0;

/*!
 *  @brief      DMAͨ��0�ж�
 *  @since      v5.0
 */
void dma_ch0_handler(void)
{
    DMA_IRQ_CLEAN(DMA_CH0);                  //���ͨ�������жϱ�־λ

    //DMA_DADDR(DMA_CH0) = BUFF;            //�ָ���ַ (���ڳ�ʼ��ʱ����Ϊ�ָ�Ŀ�ĵ�ַ������˴�����Ҫ)
    DMA_EN(DMA_CH0);                        //ʹ��ͨ��CHn Ӳ������

    printf("\nDMA�жϷ���");
    dmaflag = 1;
}

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

    port_init_NoALT(PTA7,DMA_FALLING );                 //Ĭ���������ش������˴��޸�Ϊ�½��ش���

    set_vector_handler(DMA0_VECTORn ,dma_ch0_handler);    //����DMA0���жϸ�λ����Ϊ dma_ch0_handler
    enable_irq (DMA0_IRQn);                                //ʹ��DMA0�ж�

    DMA_EN(DMA_CH0);                        //ʹ��DMA Ӳ������


    while(1)
    {
        if(dmaflag == 1)
        {
            dmaflag = 0;
            memset(BUFF,0,sizeof(BUFF));
            printf("\n��ʼ������BUFF����");
        }
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


