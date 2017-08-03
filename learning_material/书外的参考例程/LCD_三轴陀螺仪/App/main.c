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
 *  @note       ɽ������ ������ ����ʵ��
 */

#define XOUT    ADC1_DM0
#define YOUT    ADC0_SE16
#define ZOUT    ADC0_SE17

#define Gyro1   ADC1_SE16
#define Gyro2   ADC1_DP0
#define Ang     ADC0_SE18

void main()
{
    uint16 x,y,z,gyro1,gyro2,ang;                           //����ADCת�����
    
    Site_t site = {3,5};

    adc_init(XOUT);
    adc_init(YOUT);
    adc_init(ZOUT);
    adc_init(Gyro2);         //�Ǽ��ٶ�  Angular2
    adc_init(Gyro1);         //�Ǽ��ٶ�  Angular1
    adc_init(Ang);

    LCD_init();
    LCD_str(site,"XOUT",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    site.y += 20;
    LCD_str(site,"YOUT",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    site.y += 20;    
    LCD_str(site,"ZOUT",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    site.y += 20;  
    LCD_str(site,"Gyro1",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    site.y += 20;   
    LCD_str(site,"Gyro2",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    site.y += 20;
    LCD_str(site,"Ang",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    
    site.x = 3 + 6*8; 
    
    
    while(1)
    {
        site.y = 5;
        
        x = adc_once(XOUT,ADC_8bit);
        LCD_num_C (site, x , FCOLOUR , BCOLOUR);
        site.y += 20;  
        
        y = adc_once(YOUT,ADC_8bit);
        LCD_num_C (site, y , FCOLOUR , BCOLOUR);
        site.y += 20;    
        
        z = adc_once(ZOUT,ADC_8bit);
        LCD_num_C (site, z , FCOLOUR , BCOLOUR);
        site.y += 20;   
        
        gyro1 = adc_once(Gyro1,ADC_8bit);
        LCD_num_C (site, gyro1 , FCOLOUR , BCOLOUR);
        site.y += 20;   
        
        gyro2 = adc_once(Gyro2,ADC_8bit);
        LCD_num_C (site, gyro2 , FCOLOUR , BCOLOUR);
        site.y += 20; 
        
        ang = adc_once(Ang,ADC_8bit);
        LCD_num_C (site, ang , FCOLOUR , BCOLOUR);
    }

}