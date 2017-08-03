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

uint8  nrf_rx_buff[CAMERA_SIZE + 2*COM_LEN + DATA_PACKET];         //Ԥ��
//uint8  nrf_tx_buff[CAMERA_SIZE + 2*COM_LEN + DATA_PACKET];         //Ԥ��
uint8 *imgbuff = (uint8 *)(((uint8 *)&nrf_rx_buff) + COM_LEN);     //ͼ���ַ


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
    Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��
    Size_t imgsize  = {CAMERA_W, CAMERA_H};             //ͼ���С
    Size_t size     = {80, 60}; //{LCD_W, LCD_H};       //��ʾ����ͼ���С
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


    /*********************** ������Ϣ ��ʼ��  ***********************/
    key_event_init();                   //������Ϣ��ʼ��
    pit_init_ms(PIT0,10);               //pit ��ʱ�ж�(���ڰ�����ʱɨ��)
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);    //���� PIT0 ���жϸ�λ����Ϊ PIT0_IRQHandler
    enable_irq(PIT0_IRQn);

    while(1)
    {
        /*********************** ������Ϣ ����  ***********************/
        deal_key_event();

        /************************ ���߷��ͺͽ�������  ***********************/
        do
        {
            nrf_result = nrf_msg_rx(&com, nrf_rx_buff);
            if(nrf_result == NRF_RESULT_RX_VALID)
            {
                switch(com)
                {
                    case COM_IMG:
                        //��ʾ �� ��Ļ��
#if     ( CAMERA_COLOR == 1 )                                       //�Ҷ�����ͷ
                        LCD_Img_gray_Z(site,size, imgbuff,imgsize);
#elif   ( CAMERA_COLOR == 0 )                                       //�ڰ�����ͷ
                        LCD_Img_Binary_Z(site,size, imgbuff,imgsize);
#endif
                        break;

                    case COM_VAR:

                        break;
                    default:
                        break;
                }
            }
        }while(nrf_result != NRF_RESULT_RX_NO);

        /************************ �ֶ�����ͬ������  ***********************/
        //���� ������ ���� FIFO ����ʾ �� ���յ����ݣ��Ž��� ͬ��
        //�������Լ��� �Է��ڷ����У����ҷ�Ҳ���з��ͣ��Ӷ��������ݶ�ʧ������
        //��Ȼ��Ҳ���׳�ʱ�䷢��
        i++;
        if(i > 0xffff)
        {
            i = 0;

            //�޸ı��������ַ�����(ͨ������������)
            //ע�⣬�Ա������и�ֵ���ǲ����� ���ֵ����Сֵ�ģ�
#if 1
            //����1
            var1++;
            updata_var(VAR1);
#else
            //����2
            save_var(VAR1,var1 +1);
#endif
            if(var_syn(VAR1) == 0)
            {
                //printf("\nͬ��ʧ��");
            }
            else
            {
                //printf("\nͬ���ɹ�");
            }
            var_display(VAR1);
        }
    }
}

/*

֪ʶ�� ����;

1.ӥ�� ����ͷ �ɼ�������ͼ���� ѹ��ͼ����Ҫ���н�ѹ���ο����� ����:
        ӥ��ͼ���ѹ��תΪ ��ά���� - ���ܳ������� - ɽ���ѧ123��̳
        http://www.vcan123.com/forum.php?mod=viewthread&tid=17


2.ͼ�� ��ַ ת��Ϊ ��ά���顣
        ����� ӥ�ۣ��ο� ��1��֪ʶ��˵��

        ��������� �Ҷ�ͼ������ͷ���޸����´���:
        uint8 *imgbuff = (uint8 *)(((uint8 *)&nrf_buff) + COM_LEN);     //ͼ���ַ
        ��Ϊ
        uint8 (*imgbuff)[CAMERA_H][CAMERA_W] =   (uint8 (*)[CAMERA_H][CAMERA_W])(((uint8 *)&nrf_buff) + COM_LEN);     //ͼ���ַ
        ʵ���� ����ǿ�� ����ת����

3.����ͷ�Ĳɼ���ַ ���� ����ͷ��ʼ���Ǵ��ݽ�ȥ�ģ��˺��ͼ�񶼲ɼ����õ�ַ�ϡ�
        camera_init(imgbuff);                                   //����ͷ��ʼ������ͼ��ɼ��� imgbuff ��ַ

4.����ģ�飬������ݽ��պ󣬲Ž��� ���ͣ��������Ծ������� ����ģ��ͬʱ���� ����״̬��

5.Ƕ���жϵ����⣬�ο���������:
        �����ж�Ƕ�׵����� - ���ܳ������� - ɽ���ѧ123��̳
        http://www.vcan123.com/forum.php?mod=viewthread&tid=499&page=1#pid3270

6.����ɨ�裬�ǲ��ö�ʱɨ�跽ʽ����ɨ���


*/

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
    key_IRQHandler();

    PIT_Flag_Clear(PIT0);
}

