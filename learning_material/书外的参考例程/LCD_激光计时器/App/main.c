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

#if 0
/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ��LCD ���������
 */
void  main(void)
{
    uint16 ms;

    LCD_ui_time_init();

    while(1)
    {
        LCD_ui_time(ms++);
    }
}

#else

#define     DISTURB_TIME    1000        // ����ʱ��
#define     TIME_MAX        60000       // ����ʱʱ��

uint32 time_ms = 0;
uint8  timemode = 0;        //��ʱģʽ ��0 �� ֹͣ����״̬ �� 1 �� ���ڼ���״̬��2 ��ʾ С���ڶ��δ�����

void PIT0_IRQHandler(void);
void PORTA_IRQHandler(void);

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ��LCD ��������� ,lptmr �� ��ʱ�� ���ɼ�ʱ 65535 ms ���������ܳ��� 60s����
 */
void  main(void)
{
    KEY_MSG_t keymsg;

    key_init(KEY_MAX);        // ��ʼ�� KEY_START ������������Ϊ ���� ���� ��ͣ ����

    pit_init_ms(PIT0,10);
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϸ�λ����Ϊ PIT0_IRQHandler
    enable_irq (PIT0_IRQn);                                 //ʹ��PIT0�ж�

    LCD_ui_time_init();

    led_init(LED0);
    gpio_init(PTA7,GPI,0);

    //������� ��ʼ��
    FTM_PWM_init(FTM0, FTM_CH3,180000,80);  //��ʼ�� FTM PWM ��ʹ�� FTM0_CH3��Ƶ��Ϊ180k ��ռ�ձ�Ϊ 80 / 100
                                            // vcan_port_cfg.h �� ���� FTM0_CH3 ��ӦΪ PTA7

    port_init(PTA7, ALT1 | IRQ_RISING |  PF );          //��ʼ�� PTA7 �ܽţ����ù���ΪGPIO �������ش����жϣ���������
    set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //����PORTA���жϸ�λ����Ϊ PORTA_IRQHandler
    PORTA_ISFR  = (1 << 7);                 //д1���жϱ�־λ
    enable_irq (PORTA_IRQn);                //ʹ��PORTA�ж�


    while(1)
    {
        led(LED0,GPIO_GET(PTA7));           //LED ��ʾ ״̬
        if(timemode == 1)
        {
            time_ms =  lptmr_time_get_ms();
            if(time_ms >= TIME_MAX)         //����ʱ TIME_MAX ��
            {

                //ʱ�䵽
                disable_irq (PORTA_IRQn);   //��ֹPORTA�ж�
                timemode = 0;
                LCD_ui_time(TIME_MAX);      //��ʾʱ��

            }
            else
            {
                LCD_ui_time(time_ms);       //��ʾʱ��
            }
        }
        else if(timemode == 2)
        {
            timemode = 0;
            LCD_ui_time(time_ms);               //��ʾʱ��
            while(get_key_msg(&keymsg) == 1);   //��հ�����Ϣ
        }

        while(get_key_msg(&keymsg) == 1)
        {
            if((keymsg.key == KEY_START) && (keymsg.status == KEY_DOWN))      //����KEY_START����
            {
                //  timemode == 1 ,�� �� �ж� ����
                if(timemode == 1)       // �� 1 �� 0 ����ʾ ��λ �� �ֹ���ͣ
                {
                    disable_irq (PORTA_IRQn);        //��ֹPORTA�ж�
                    timemode = 0;
                }else  if(timemode == 0)                   // 0 ��ֹͣ���������ʱ���� 0
                {
                    PORTA_ISFR  = (1 << 7);         //д1���жϱ�־λ
                    enable_irq (PORTA_IRQn);        //ʹ��PORTA�ж�
                    LCD_ui_time(0);                 //��ʾʱ��Ϊ 0
                }
            }
        }
    }
}

/*!
 *  @brief      PIT0�жϷ�����
 *  @since      v5.0
 */
void PIT0_IRQHandler(void)
{
    PIT_Flag_Clear(PIT0);       //���жϱ�־λ

    //�������û����ʵ�ִ���
    key_IRQHandler();                           //�Ѱ���ɨ�������뵽��ʱ�жϸ�λ�������ʱִ��
}

/*!
 *  @brief      PORTA�˿��жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler(void)
{
    uint8  n ;    //���ź�

    n = 7;
    if(PORTA_ISFR & (1 << n))           //PTA7 �����ж�
    {
        /*  ����Ϊ�û�����  */
        if(timemode == 0)               // 0 ��ֹͣ״̬������� ��ʱ״̬
        {
            lptmr_time_start_ms();      //��ʼ��ʱ(ms)
            timemode = 1;
            time_ms = 0;
        }
        else /*if(timemode == 1) */     // ��ʱ���ٴν��� ��ʱ
        {
            time_ms =  lptmr_time_get_ms(); //��ȡʱ��

            if(time_ms > DISTURB_TIME)
            {
                disable_irq (PORTA_IRQn);                                //ʹ��PORTA�ж�
                timemode = 2;               //��������ʱ�����Ϊȷ�� ʱ�䵽��
                lptmr_time_close();         //�رռ�ʱ��
            }
        }




        /*  ����Ϊ�û�����  */

        PORTA_ISFR  = (1 << n);         //д1���жϱ�־λ
    }

}


#endif

