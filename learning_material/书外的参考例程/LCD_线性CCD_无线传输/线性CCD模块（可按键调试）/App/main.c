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

uint8  nrf_rx_buff[TSL1401_MAX*TSL1401_SIZE + 2*COM_LEN + DATA_PACKET];         //Ԥ��
uint8  nrf_tx_buff[TSL1401_MAX*TSL1401_SIZE + 2*COM_LEN + DATA_PACKET];         //Ԥ��
uint8 *ccdbuff0 = (uint8 *)(((uint8 *)&nrf_tx_buff) + COM_LEN);                 //ͼ���ַ
uint8 *ccdbuff1 = (uint8 *)(((uint8 *)&nrf_tx_buff) + COM_LEN + TSL1401_SIZE);     //ͼ���ַ
uint8 *ccdbuff2 = (uint8 *)(((uint8 *)&nrf_tx_buff) + COM_LEN + 2*TSL1401_SIZE);     //ͼ���ַ

//��������
void PIT0_IRQHandler();
void PORTE_IRQHandler();

uint8  var1 = 20, var2;
uint16 var3, var4;
uint32 var5, var6;


/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� ���ߵ��� ����ʵ��
 */
void  main(void)
{
    Site_t site1={0,70};                            //��ʾͼ�����Ͻ�λ��
    Site_t site2={0,90};                            //��ʾͼ�����Ͻ�λ��
    Site_t site3={0,110};                           //��ʾͼ�����Ͻ�λ��
    Size_t imgsize={TSL1401_SIZE,1};                //ͼ���С
    Size_t size={TSL1401_SIZE,15};                  //��ʾ�����С

    uint32 i;
    com_e     com;
    nrf_result_e nrf_result;

    /************************ ���� K60 �����ȼ�  ***********************/
    //K60 ��Ĭ�����ȼ� ��Ϊ 0
    //�ο����ӣ������ж�Ƕ�׵����� - ���ܳ������� - ɽ���ѧ123��̳
    //          http://www.vcan123.com/forum.php?mod=viewthread&tid=499&page=1#pid3270
    NVIC_SetPriorityGrouping(4);            //�������ȼ�����,4bit ��ռ���ȼ�,û�������ȼ�

    NVIC_SetPriority(PORTE_IRQn,0);         //�������ȼ�
    NVIC_SetPriority(PIT0_IRQn,1);          //�������ȼ�


    /************************ LCD Һ���� ��ʼ��  ***********************/
    LCD_init();

    /************************ ����ģ�� NRF ��ʼ��  ***********************/
    while(!nrf_init());
    //�����жϸ�λ����
    set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler);                //���� PORTE ���жϸ�λ����Ϊ PORTE_VECTORn
    enable_irq(PORTE_IRQn);
    nrf_msg_init();                                                     //����ģ����Ϣ��ʼ��

    //����CCDģ�飬��Ҫ ���� ������� ���԰�ģ�飬����������� ����ͼ��ʧ�ܶ�������������
    i = 20;
    while(i--)
    {
        nrf_msg_tx(COM_RETRAN,nrf_tx_buff);                              //���Ͷ�� �� �����ȥ��������� ���ն˵Ļ�������
    }

    /*********************** ������Ϣ ��ʼ��  ***********************/
    key_event_init();                                                   //������Ϣ��ʼ��
    //pit_init_ms(PIT0,10);                                             //pit ��ʱ�ж�(���ڰ�����ʱɨ��)
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);                  //���� PIT0 ���жϸ�λ����Ϊ PIT0_IRQHandler
    enable_irq(PIT0_IRQn);

    /************************ ����CCD ��ʼ��  ***********************/
    tsl1401_set_addrs(TSL1401_MAX,ccdbuff0,ccdbuff1,ccdbuff2);          //���òɼ�
    tsl1401_init(10);                                                   //��ʼ�� ����CCD ������ �ж�ʱ��Ϊ 10
    //tsl1401_led_en(TSL1401_MAX);                                        //ʹ��CCD �� �����

    //����CCD �� key ���� pit0 ��ʱ�ж�

    while(1)
    {
        /************************ ͼ��ɼ�����ʾ  ***********************/
        //�ɼ� ����CCD ͼ��
        tsl1401_get_img();

        //LCD ��ʾͼ��
        LCD_Img_gray_Z(site1,size,ccdbuff0,imgsize);
        LCD_Img_gray_Z(site2,size,ccdbuff1,imgsize);
        LCD_Img_gray_Z(site3,size,ccdbuff2,imgsize);

        /************************ ���߷��ͺͽ�������  ***********************/
        do
        {
            nrf_result = nrf_msg_rx(&com, nrf_rx_buff);
            if(nrf_result == NRF_RESULT_RX_VALID)
            {
                switch(com)
                {
                    case COM_CCD:
                        break;

                    case COM_VAR:

                        break;
                    default:
                        break;
                }
            }
        }while(nrf_result != NRF_RESULT_RX_NO);         //���ղ������� ���˳�

        //��ͼ�� ���ͳ�ȥ
        nrf_msg_tx(COM_CCD,nrf_tx_buff);

        while(nrf_tx_state() == NRF_TXING);             //�ȴ��������


        /*********************** ������Ϣ ����  ***********************/
        deal_key_event();

    }
}


/*!
 *  @brief      PORTE�жϷ�����
 *  @since      v5.0
 */
void PORTE_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    flag = PORTE_ISFR;
    PORTE_ISFR  = ~0;                                   //���жϱ�־λ

    n = 27;
    if(flag & (1 << n))                                 //PTE27�����ж�
    {
        nrf_handler();
    }
}


/*!
 *  @brief      PIT0�жϷ�����
 *  @since      v5.0
 */
void PIT0_IRQHandler()
{
    tsl1401_time_isr();
    key_IRQHandler();
    PIT_Flag_Clear(PIT0);
}

