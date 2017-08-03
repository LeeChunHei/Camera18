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
 *  @brief      LPTMR��ʱִ�е��жϷ�����
 *  @since      v5.0
 *  @note       ���� KEY ��ʱɨ��
 */
void lptmr_hander(void)
{
    LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;         //���LPT�Ƚϱ�־λ

    //�������û����ʵ�ִ���
    key_IRQHandler();                           //�Ѱ���ɨ�������뵽��ʱ�жϸ�λ�������ʱִ��

}

char * keyname[KEY_MAX]={"KEY_U","KEY_D","KEY_L","KEY_R",
                        "KEY_A","KEY_B","KEY_START","KEY_START"};

char * keystatus[3]={"����","����","����"};

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ���� KEY ��ʱɨ��,��Ҫͨ�����ڲ鿴��������� ������ Ϊ VCAN_BAUD
 */
void main()
{
    KEY_MSG_t keymsg;

    printf("\n******* GPIO ������ʱ���� *******");

    key_init(KEY_MAX);

    lptmr_timing_ms(10);                                // LPTMR ��ʱ 10ms
    set_vector_handler(LPTMR_VECTORn,lptmr_hander);   // �����жϸ�λ�������ж���������
    enable_irq(LPTMR_IRQn);                           // ʹ��LPTMR�ж�

    while(1)
    {
        while(get_key_msg(&keymsg) == 1)
        {
            printf("\n����%s%s",keyname[keymsg.key],keystatus[keymsg.status]);
        }

        DELAY_MS(500);                                  //���� �� ��ʱʱ�䣬���� FIFO���������Ȼ�������©ʶ�𰴼�
    }
}


