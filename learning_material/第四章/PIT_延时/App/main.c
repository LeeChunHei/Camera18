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
 *  @note       ɽ�� PIT ��ʱʵ��
 */
void main()
{
    led_init(LED0);                                         //��ʼ��LED

    while(1)
    {
        led_turn(LED0);                                     //��ת LED0 ״̬��ʹ��LED0��˸

        pit_delay_ms(PIT0, 1000);                           //ʹ��PIT0��ʱ�� 1000ms
    }
}

