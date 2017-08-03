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
 *  @note       ɽ������ͷ LCD ����ʵ��
 */
void  main(void)
{
    Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��
    Size_t imgsize  = {CAMERA_W, CAMERA_H};             //ͼ���С
    Size_t size;                   //��ʾ����ͼ���С

    LCD_init();

    size.H = LCD_H;
    size.W = LCD_W;

    camera_init(imgbuff);
    //�����жϸ�λ����
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //����LPTMR���жϸ�λ����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //����LPTMR���жϸ�λ����Ϊ PORTA_IRQHandler

    while(1)
    {
        camera_get_img();                                   //����ͷ��ȡͼ��

#if     ( CAMERA_COLOR == 1 )                               //�Ҷ�����ͷ
        LCD_Img_gray_Z  (site, size, imgbuff, imgsize);
#elif   ( CAMERA_COLOR == 0 )                               //�ڰ�����ͷ
        LCD_Img_Binary_Z(site, size, imgbuff, imgsize);
#endif

#if 0
        /******************** ����ͼ����λ�� ***********************/
        img_extract(img, imgbuff, CAMERA_SIZE);          //��ѹΪ�Ҷ�ͼ�񣬷��㷢�͵���λ����
        sendimg(img, CAMERA_W * CAMERA_H);                    //���͵���λ��
#endif

    }
}


/*!
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 29;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //ʹ�����ж�
    n = 28;
    if(flag & (1 << n))                                 //PTA28�����ж�
    {
        camera_href();
    }
#endif


}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}


//����ͼ����λ����ʾ
//��ͬ����λ������ͬ���������ʹ�� yy_����ͷ���ڵ��� ���
//���ʹ��������λ��������Ҫ�޸Ĵ���
void sendimg(uint8 *imgaddr, uint32 imgsize)
{
    uint8 cmd[4] = {0, 255, 1, 0 };    //yy_����ͷ���ڵ��� ʹ�õ�����

    uart_putbuff(VCAN_PORT, cmd, sizeof(cmd));    //�ȷ�������

    uart_putbuff(VCAN_PORT, imgaddr, imgsize); //�ٷ���ͼ��
}

//ѹ����ֵ��ͼ���ѹ���ռ� �� ʱ�� ��ѹ��
//srclen �Ƕ�ֵ��ͼ���ռ�ÿռ��С
void img_extract(uint8 *dst, uint8 *src, uint32 srclen)
{
    uint8 colour[2] = {255, 0}; //0 �� 1 �ֱ��Ӧ����ɫ
    //ע��ɽ�������ͷ 0 ��ʾ ��ɫ��1��ʾ ��ɫ
    uint8 tmpsrc;
    while(srclen --)
    {
        tmpsrc = *src++;
        *dst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
    }
}