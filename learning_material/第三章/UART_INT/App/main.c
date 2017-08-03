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

/*!
 *  @brief      UART3�жϷ�����
 *  @since      v5.0
 */
void uart3_handler(void)
{
    char ch;
    UARTn_e uratn = UART3;

    if(UART_S1_REG(UARTN[uratn]) & UART_S1_RDRF_MASK)   //�������ݼĴ�����
    {
        //�û���Ҫ�����������
        uart_getchar   (UART3, &ch);                    //���޵ȴ�����1���ֽ�
        uart_putchar   (UART3 , ch);                    //�����ַ���
    }
}

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       �����жϽ��ղ���
 */
void main()
{
    //uart_init(UART3,115200);     //��ʼ������(UART3 �ǹ���������Ϊprintf��������˿ڣ����Ѿ����г�ʼ��)

    uart_putstr   (UART3 ,"\n\n\n�����жϲ��ԣ�");           //�����ַ���

    set_vector_handler(UART3_RX_TX_VECTORn,uart3_handler);   // �����жϸ�λ�������ж���������

    uart_rx_irq_en (UART3);                                 //�����ڽ����ж�

    while(1)
    {

    }
}

