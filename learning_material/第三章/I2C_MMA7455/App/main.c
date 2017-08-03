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
 *  @note       I2C ���� MMA7455
 */
void main(void)
{
    printf("\n\n\n***********������ٶȲ���************");
    
    mma7455_init();
    
    while(1)
    {          
        //ע�⣺��ȡ�Ľ����ҪУ׼�ģ�����׼�ġ�
        //У׼�����뿴�ĵ����˴�������ͨ������
        printf("\n\nx:%d,y:%d,z:%d"
               ,(int8)mma7455_read_reg(MMA7455_XOUT8)       //��ȡx�����
               ,(int8)mma7455_read_reg(MMA7455_YOUT8)       //��ȡy�����
               ,(int8)mma7455_read_reg(MMA7455_ZOUT8)       //��ȡz�����
               );
        
        DELAY_MS(500);
    }
}

