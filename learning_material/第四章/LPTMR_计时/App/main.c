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
 *  @note       ɽ�� LPTMR ��ʱʵ��
 */
void main()
{
    uint32 timevar;
    while(1)
    {
        lptmr_time_start_ms();                  //��ʼ��ʱ

        DELAY_MS(50);                           //��ʱһ��ʱ��(�������ִ����Ҫʱ�䣬���ʵ�ʵ���ʱʱ������һЩ)

        timevar = lptmr_time_get_ms();          //ֹͣ��ʱ����ȡ��ʱʱ��

        printf("\n\n��ʱʱ��Ϊ��%dms",timevar); //��ӡ��ʱʱ��

        DELAY_MS(1000);
    }
}

