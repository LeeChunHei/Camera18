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
 *  @note       ɽ��LCD flexbus����ʵ��
 */
void  main(void)
{
    uint16  i = 0;
    Site_t site;
    LCD_init();            //��ʼ��

    site.x = 10;
    site.y = 10;
    LCD_str(site, "WildFire", BLUE, RED);
    
    site.y = 30;
    LCD_str(site, "www.vcan123.com", BLUE, RED);

    site.y = 50;
    LCD_num(site, 20130901, BLUE, RED);
    
    site.y = 70;
        
    while(1)
    {
        LCD_num_C(site, i++, BLUE, RED);
    }
}
