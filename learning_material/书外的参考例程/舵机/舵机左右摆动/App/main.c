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



#define S3010_FTM   FTM1
#define S3010_CH    FTM_CH0
#define S3010_HZ    (100)


/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� S3010��� ����ʵ�� ,ɽ�� �ṩ�� �������ģ�飬�ܽŶ����� MOS �ܸ��룬�ź��Ƿ���ġ�
                ���糣��� �ߵ�ƽ ʹ��
 */
void main()
{
    uint8 i;
    FTM_PWM_init(S3010_FTM, S3010_CH,S3010_HZ,100);      //��ʼ�� ��� PWM

    while(1)
    {

        for(i = 13;i<25;i++)
        {
            FTM_PWM_Duty(S3010_FTM, S3010_CH,100-i);
            DELAY_MS(200);
        }

        for(;i>13;i--)
        {
            FTM_PWM_Duty(S3010_FTM, S3010_CH,100-i);
            DELAY_MS(200);
        }


    }

}