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
 *  @note       ���Ź����Դ���
 */
void main(void)
{
    printf("\n*****���Ź�����*****\n");

    wdog_init_ms(1000) ;        //��ʼ�����Ź������������ʱ�䣬����ÿ�θ�λ��ʱ���Ƿ����趨����ͬ�����ʱ��̫�̣���λʱ��ʼ��ʱ��Ƚϳ������Ƚϴ��
    while(1)
    {
        DELAY_MS(500);
        wdog_feed();  printf("ι���ˣ�����~~\n\n");     //ע����ûע�ͣ����Կ�����λ��û��λ�ģ�ͨ���������֣�

    }
}

