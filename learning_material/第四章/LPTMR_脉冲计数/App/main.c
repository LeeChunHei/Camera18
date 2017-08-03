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
 *  @note       ɽ�� LPTMR �������ʵ�飬��Ҫ�̽� PTA7 �� PTA19
 */
void  main(void)
{
#define INT_COUNT  0xFFFF          //LPT �����жϵļ�������

    uint16 count;

    FTM_PWM_init(FTM0, FTM_CH4, 10000, 50);                       //FTMģ�����PWM���� FTM0_CH4 ���� PTA7 ��Ƶ��Ϊ 100��ռ�ձ� 50%
                                                                //�޸�Ƶ�ʣ���֤ ��ͬPWM�¼���ֵ�Ƕ��١�

    lptmr_pulse_init(LPT0_ALT1, INT_COUNT, LPT_Rising);         //��ʼ���������������LPT0_ALT1����PTA19���룬ÿ��INT_COUNT�����жϣ���Ҫ���жϲ��ܲ����жϣ��������ش���

    while(1)
    {
        lptmr_pulse_clean();                                    //����������������ֵ��������գ��������ܱ�֤����ֵ׼ȷ��

        DELAY_MS(1000);                                         //���� ��ʱʱ�䣬LPTMRģ����� ���㣬�ۼ� FTM ������PWM����

        count           =   lptmr_pulse_get();                  //�����������������ֵ

        printf("LPTMR�������Ϊ:%d\n",   count);                 //��ӡ����ֵ
    }
}

