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
extern void SysTick_IRQHandler(void);

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� �δ�ʱ��systick ��ʱ�ж�ʵ��
 */
void main()
{
    led_init(LED0);                                             //��ʼ��LED0��PIT0�ж��õ�LED0

    systick_timing_ms(100);                                     //��ʼ���δ�ʱ������ʱʱ��Ϊ�� 100ms
    set_vector_handler(SysTick_VECTORn ,SysTick_IRQHandler);    //���õδ�ʱ�����жϷ�����Ϊ SysTick_IRQHandler

    while(1)
    {
        //���ﲻ��Ҫִ�����񣬵ȴ��ж�����˸LED0
    }
}

/*!
 *  @brief      �δ�ʱ��SysTick�жϷ�����
 *  @since      v5.0
 */
void SysTick_IRQHandler(void)
{
    led_turn(LED0);             //��˸ LED0
}

