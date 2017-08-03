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

void PIT0_IRQHandler(void);

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       FTM �������� ����
 */
void main(void)
{
    printf("\n*****FTM �������� ����*****\n");

    FTM_QUAD_Init(FTM1);                                    //FTM1 ���������ʼ�������õĹܽſɲ� vcan_port_cfg.h ��

    pit_init_ms(PIT0, 500);                                 //��ʼ��PIT0����ʱʱ��Ϊ�� 1000ms
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϸ�λ����Ϊ PIT0_IRQHandler
    enable_irq (PIT0_IRQn);                                 //ʹ��PIT0�ж�

    while(1);
}

/*!
 *  @brief      PIT0�жϷ�����
 *  @since      v5.0
 */
void PIT0_IRQHandler(void)
{

    int16 val;
    val = FTM_QUAD_get(FTM1);          //��ȡFTM �������� ��������(������ʾ������)
    FTM_QUAD_clean(FTM1);

    if(val>=0)
    {
        printf("\n��ת��%d",val);
    }
    else
    {
        printf("\n��ת��%d",-val);
    }


    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
}