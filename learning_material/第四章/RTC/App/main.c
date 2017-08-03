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
 * @version    v5.1
 * @date       2014-01-12
 */

#include "common.h"
#include "include.h"


/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� RTC ʵ��
 */
void main()
{
    time_s time = {2013,9,1,0,0,0}; //2013-09-01 00ʱ00��00��
    uint32 sec;

    rtc_init();                     //RTC��ʼ��

    sec = time2sec( time);          //��������ʱ�����ʽת����������

    rtc_set_time(sec);              //���� RTC ʱ��

    while(1)
    {
        sec = rtc_get_time();       //��ȡʱ��

        sec2time(sec,& time);       //ת����������Ϊ������ʱ��������

        printf("\n����ʱ���ǣ�%d-%02d-%02d %02d:%02d:%02d",time.year,time.mon,time.day,time.hour,time.min,time.sec);
                                    //ͨ�����ڴ�ӡʱ��

        DELAY_MS( 1000);            //��ʱ�� 1000ms
    }
}