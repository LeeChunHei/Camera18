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

uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
uint8 img[CAMERA_W*CAMERA_H];

//��������
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void sendimg(uint8 *imgaddr, uint32 imgsize);
void img_extract(uint8 *dst, uint8 *src, uint32 srclen);


/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ��LCD BMP ͼ�����ʵ��
 */
void  main(void)
{
    Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��

    LCD_init();

    //Ŀǰ BMP ���� ֧�� 24λ���ɫ �� 16λ RGB555 ��ǿ��ɫ ��1λ��ɫ ͼƬ
    //��֧��������ʾ
    SD2LCD_BMP("0:/vcan_bit.bmp",site);                 //��ʾ BMP ͼ��

    while(1)
    {


    }
}