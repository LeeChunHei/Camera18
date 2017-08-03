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
#include "math.h"

/*! 
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� DAC ������Ҳ� ʵ��
 */
void main()
{
    float val = 0;
    uint16 result;
    
    
    dac_init(DAC1);

    while(1)
    {
        result =(uint16) (
                            ((sin(val)+1.0)/2.0 )   //sin ��ȡֵ��Χ�� -1 ~ 1 ����1 ���� 0~2 ,�� ���� 2 ȷ����Χ�� 0~1 ֮��
                                *((1<<12) - 1)      //DAC �� 12bit
                         );

        dac_out(DAC1, result);                      //��� DAC ����ͨ��ʾ�����������Ҳ�
        
        val += 0.1;
    }
}