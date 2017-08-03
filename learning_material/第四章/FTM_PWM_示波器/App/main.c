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
 *  @brief      main����
 *  @since      v5.0
 *  @note       FTM PWM ����
 */
void main(void)
{
    printf("\n*****FTM PWM ����*****\n");

    FTM_PWM_init(FTM0, FTM_CH3,200*1000,30);        //��ʼ�� FTM PWM ��ʹ�� FTM0_CH3��Ƶ��Ϊ200k ��ռ�ձ�Ϊ 30 / FTM0_PRECISON
                                                    // vcan_port_cfg.h �� ���� FTM0_CH3 ��ӦΪ PTA6

    while(1)
    {
        DELAY_MS(500);
        FTM_PWM_Duty(FTM0, FTM_CH3,30);     //����ռ�ձ� Ϊ 30 / FTM0_PRECISON
        DELAY_MS(500);
        FTM_PWM_Duty(FTM0, FTM_CH3,60);     //����ռ�ձ�   60 / FTM0_PRECISON
    }
}
