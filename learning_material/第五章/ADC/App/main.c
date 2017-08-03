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
 *  @since      v5.1
 *  @note       ɽ�� ADC ʵ��
 */
void main()
{
    uint16 var;
    adc_init(ADC1_SE16);              //ADC��ʼ��

    while(1)
    {
        var = adc_once   (ADC1_SE16, ADC_8bit);
        printf("\nADC�������Ϊ:%d",var);
        printf("     ��Ӧ��ѹֵΪ%dmV",(3300*var)/((1<<8)-1));

        DELAY_MS(500);

    }
}