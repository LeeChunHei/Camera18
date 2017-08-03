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


void PORTD_IRQHandler(void);        //PORTD�˿��жϷ�����
void key_handler(void);             //�������µĲ����жϸ�λ����

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ���� port ���ù��ܣ���Ҫ�Ӵ�����������Ч��
                ����һ�˽� PTD7 ����һ�˽ӵ�
                ��������ʱ��PTD7 �ӵ�
                ����û�е���ʱ��PTD7 ���գ������Ҫ�����������ѵ�ƽ����
 */
void main()
{
    printf("\n*****��������*****\n");

    port_init(PTD7, ALT1 | IRQ_FALLING | PULLUP );          //��ʼ�� PTD7 �ܽţ����ù���ΪGPIO ���½��ش����жϣ���������

    set_vector_handler(PORTD_VECTORn ,PORTD_IRQHandler);    //����PORTE���жϸ�λ����Ϊ PORTE_IRQHandler
    enable_irq (PORTD_IRQn);                                //ʹ��PORTE�ж�

    while(1)
    {
        //disable_irq(PORTD_IRQn);
    }
}


/*!
 *  @brief      PORTD�˿��жϷ�����
 *  @since      v5.0
 */
void PORTD_IRQHandler(void)
{

#if 0       // �������룬���ַ����ɹ�ѡ��

    uint8  n = 0;    //���ź�
    n = 7;
    if(PORTD_ISFR & (1 << n))           //PTD7 �����ж�
    {
        PORTD_ISFR  = (1 << n);        //д1���жϱ�־λ

        /*  ����Ϊ�û�����  */

        key_handler();

        /*  ����Ϊ�û�����  */
    }
#else
    PORT_FUNC(D,7,key_handler);
#endif
}

/*!
 *  @brief      �������µĲ����жϸ�λ����
 *  @since      v5.0
 */
void key_handler(void)
{
    printf("\n���°���\n");
}
