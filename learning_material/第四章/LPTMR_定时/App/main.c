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
extern void LPTMR_IRQHandler(void);

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� LPTMR ��ʱ�ж�ʵ��
 */
void main()
{
    led_init(LED0);                                         //��ʼ��LED0��LPTMR�ж��õ�LED0

    lptmr_timing_ms(1000);                                  //��ʼ��LPTMR����ʱʱ��Ϊ�� 1000ms
    set_vector_handler(LPTMR_VECTORn ,LPTMR_IRQHandler);    //����LPTMR���жϷ�����Ϊ LPTMR_IRQHandler
    enable_irq (LPTMR_IRQn);                                //ʹ��LPTMR�ж�

    while(1)
    {
        //���ﲻ��Ҫִ�����񣬵ȴ��ж�����˸LED0
    }
}

/*!
 *  @brief      LPTMR�жϷ�����
 *  @since      v5.0
 */
void LPTMR_IRQHandler(void)
{
    led_turn(LED0);           //��˸ LED0

    LPTMR_Flag_Clear();       //���жϱ�־λ
}