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
    uint32 timevar;
    while(1)
    {
        pit_time_start  (PIT0);                 //��ʼ��ʱ
        DELAY_MS(50);                           //��ʱһ��ʱ��(�������ִ����Ҫʱ�䣬���ʵ�ʵ���ʱʱ������һЩ)
        timevar = pit_time_get_us    (PIT0);    //��ȡ��ʱʱ��

        pit_time_close  (PIT0);

        printf("\n\n��ʱʱ��Ϊ��%dus",timevar); //��ӡ��ʱʱ��

        DELAY_MS(1000);
    }
}

