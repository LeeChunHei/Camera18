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



//��������
extern void PIT0_IRQHandler(void);

/*! 
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� PIT ��ʱ�ж�ʵ��
 */
void main()
{
    led_init(LED0);                                         //��ʼ��LED0��PIT0�ж��õ�LED0
    
    pit_init_ms(PIT0, 1000);                                //��ʼ��PIT0����ʱʱ��Ϊ�� 1000ms
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϷ�����Ϊ PIT0_IRQHandler
    enable_irq (PIT0_IRQn);                                 //ʹ��PIT0�ж�

    while(1)
    {
        //���ﲻ��Ҫִ�����񣬵ȴ��ж�����˸LED0
    }
}

/*! 
 *  @brief      PIT0�жϷ�����
 *  @since      v5.0
 */
void PIT0_IRQHandler(void)
{
    led_turn(LED0);             //��˸ LED0
    
    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
}

