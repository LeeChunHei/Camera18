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

//����洢����CCDͼ�������
uint8 CCD_BUFF[TSL1401_MAX*3][TSL1401_SIZE];

void PIT0_IRQHandler();
void bin(uint8 *bin,uint8 * img,uint8 * difimg,uint16 len,uint8 maxdif);

void abs_diff(uint8 *dst,uint8 *src,uint16 len,uint8 * maxval,uint8 * avgval);
void maxvar(uint8 *buf,uint16 len,uint8  maxval);

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� ����CCD ����ʵ��
                �޸� PIT0 �Ķ�ʱʱ�伴���޸��ع�ʱ��
 */
void  main(void)
{
#define BIN_MAX 0x80
    uint8 time = 6;
    Site_t site1={0,0};                         //��ʾͼ�����Ͻ�λ��
    Site_t site1b={0,0+30};                     //��ʾͼ�����Ͻ�λ��
    Site_t site1max={TSL1401_SIZE+20,0};        //��ʾ�����ֵλ��

    Site_t site2={0,70};                        //��ʾͼ�����Ͻ�λ��
    Site_t site2b={0,70+30};                    //��ʾͼ�����Ͻ�λ��

    Site_t site3={0,140};                        //��ʾͼ�����Ͻ�λ��
    Site_t site3b={0,140+30};                    //��ʾͼ�����Ͻ�λ��


    Size_t imgsize={TSL1401_SIZE,1};            //ͼ���С
    Size_t size={TSL1401_SIZE,30};              //��ʾ�����С
    uint8  max[TSL1401_SIZE];
    uint8  avg[TSL1401_SIZE];


    LCD_init();                                 //��ʼ��

    //��ʼ�� ����CCD
    tsl1401_set_addrs(TSL1401_MAX,(uint8 *)&CCD_BUFF[0],(uint8 *)&CCD_BUFF[1],(uint8 *)&CCD_BUFF[2]);
    tsl1401_init(time);                         //��ʼ�� ����CCD ������ �ж�ʱ��Ϊ time
    //tsl1401_led_en(TSL1401_MAX);                //���������
    //tsl1401_led_dis(TSL1401_MAX);             //�رղ����

    //���� �жϺ��� �� ʹ���ж�
    set_vector_handler(PIT0_VECTORn,PIT0_IRQHandler);
    enable_irq(PIT0_IRQn);



    while(1)
    {
        //�ɼ� ����CCD ͼ��
        tsl1401_get_img();

        //LCD ��ʾͼ��
        LCD_Img_gray_Z(site1,size,(uint8 *)&CCD_BUFF[0],imgsize);
        LCD_Img_gray_Z(site2,size,(uint8 *)&CCD_BUFF[1],imgsize);
        LCD_Img_gray_Z(site3,size,(uint8 *)&CCD_BUFF[2],imgsize);

        //LCD ��ʾ����ͼ
        LCD_wave_display(site1,size,(uint8 *)&CCD_BUFF[0],BIN_MAX,BLUE );
        LCD_wave_display(site2,size,(uint8 *)&CCD_BUFF[1],BIN_MAX,BLUE );
        LCD_wave_display(site3,size,(uint8 *)&CCD_BUFF[2],BIN_MAX,BLUE );

        //�������ֵ
        maxvar((uint8 *)&CCD_BUFF[0],TSL1401_SIZE,BIN_MAX);
        maxvar((uint8 *)&CCD_BUFF[1],TSL1401_SIZE,BIN_MAX);
        maxvar((uint8 *)&CCD_BUFF[2],TSL1401_SIZE,BIN_MAX);

        //���β��
        abs_diff((uint8 *)&CCD_BUFF[TSL1401_MAX+0],(uint8 *)&CCD_BUFF[0],TSL1401_SIZE,&max[0],&avg[0]);
        abs_diff((uint8 *)&CCD_BUFF[TSL1401_MAX+1],(uint8 *)&CCD_BUFF[1],TSL1401_SIZE,&max[1],&avg[1]);
        abs_diff((uint8 *)&CCD_BUFF[TSL1401_MAX+2],(uint8 *)&CCD_BUFF[2],TSL1401_SIZE,&max[2],&avg[2]);

        //LCD ��ʾ���ͼ
        LCD_wave_display(site1,size,(uint8 *)&CCD_BUFF[TSL1401_MAX+0],max[0],GREEN);
        LCD_wave_display(site2,size,(uint8 *)&CCD_BUFF[TSL1401_MAX+1],max[1],GREEN);
        LCD_wave_display(site3,size,(uint8 *)&CCD_BUFF[TSL1401_MAX+2],max[2],GREEN);

        //���ݲ�ֲ��ζ�ֵ��ͼ��
        bin((uint8 *)&CCD_BUFF[2*TSL1401_MAX+0],(uint8 *)&CCD_BUFF[0],(uint8 *)&CCD_BUFF[TSL1401_MAX+0],TSL1401_SIZE,max[0]);
        bin((uint8 *)&CCD_BUFF[2*TSL1401_MAX+1],(uint8 *)&CCD_BUFF[1],(uint8 *)&CCD_BUFF[TSL1401_MAX+1],TSL1401_SIZE,max[1]);
        bin((uint8 *)&CCD_BUFF[2*TSL1401_MAX+2],(uint8 *)&CCD_BUFF[2],(uint8 *)&CCD_BUFF[TSL1401_MAX+2],TSL1401_SIZE,max[2]);

        //LCD ��ʾ��ֵ��ͼ
        LCD_Img_gray_Z(site1b,size,(uint8 *)&CCD_BUFF[2*TSL1401_MAX+0],imgsize);
        LCD_Img_gray_Z(site2b,size,(uint8 *)&CCD_BUFF[2*TSL1401_MAX+1],imgsize);
        LCD_Img_gray_Z(site3b,size,(uint8 *)&CCD_BUFF[2*TSL1401_MAX+2],imgsize);


        //��ʾ�����ֵ
        LCD_num_BC(site1max, max[0],3,FCOLOUR,BCOLOUR);




    }
}


/*!
 *  @brief      PIT0�жϷ�����
 *  @since      v5.0
 *  @note       ���� TSL1401_INT_TIME ���� Ϊ PIT0 �����ʹ�� PIT0
 */
void PIT0_IRQHandler()
{
    tsl1401_time_isr();
    PIT_Flag_Clear(PIT0);
}

void maxvar(uint8 *buf,uint16 len,uint8  maxval)
{
    while(len--)
    {
        if(buf[len] > maxval)
        {
            buf[len]= maxval;
        }
    }

}


/*!
 *  @brief      �����־���ֵ
 *  @since      v5.0
 *  @note       ɽ���ַ�����˵����������ֵmaxval �� ���ƽ��ֵavgval ������
                ������Ϊ�˱��ڶ���ȷ����ֵ������ģ���ɾ�������ƽ��ֵ��һ�㷵�ؽ��
                ���ǳ�С����˶����ò��ϣ�����ɾ�����˴�������Ϊ�˸������֤��
 */
void abs_diff(uint8 *dst,uint8 *src,uint16 len,uint8 * maxval,uint8 * avgval)
{
    int8 tmp;
    uint8 max = 0;
    uint32 sum = 0;
    uint16 lentmp = len;
    while(--lentmp)                 //��ѭ�� len-1 ��
    {
        tmp = *(src+1)- *src;
        tmp = ABS(tmp) ;
        if(tmp > max )
        {
             max = tmp;
        }

        sum += tmp;
        *dst = tmp;
        src++;
        dst++;
    }
    *dst = 0;               // ���һ�� ������Ϊ 0
    *maxval = max;           // ���������Բ�ֵ
    *avgval = (uint8)(sum/(len-1));  //ǰ len -1 ������ƽ��ֵ
}

/*!
 *  @brief      �򵥵�һ����ֵ�� �㷨�����ȶ�,�����ԣ�
 *  @since      v5.0
 */
// diff_threshold �����ֵ ,��ͬ�ĽǶȣ���ͬ�Ļ�����������ͬ
//�ɸ��� maxdif �����ֵ�����ã�����ֱ�ӹ̶���ֵ
#define diff_threshold    ((maxdif> 12) ? ((maxdif*80)/100) :10)     // �����ֵ
//#define diff_threshold    10
#define safe_isolation    3
void bin(uint8 *bin,uint8 * img,uint8 * difimg,uint16 len,uint8 maxdif)
{
    uint16 tmplen = len;
    uint8  thldnum = 0;        //��ֵ����
    uint8  thresholdimg;
    uint8  tmpnum;

    memset(bin,0xFF,len);  //ȫ������

    while(tmplen--)
    {
        if((tmplen == 0)|| (tmplen > len))
        {
            return;
        }

        if(difimg[tmplen] > diff_threshold)                  //�ҵ� �����ֵ
        {
            thldnum++;

            //Ѱ���������ֵ
            while(tmplen--)
            {
                if((tmplen == 0)|| (tmplen > len))
                {
                    return;
                }

                if(difimg[tmplen] < difimg[tmplen+1] )    //tmplen+1 Ϊ�����ֵ
                {
                     break;
                }
            }

            //tmplen + 1 �� ������ֵ ���л��� ��ɫɨ��
            if((img[tmplen] <= img[tmplen+1]) ||(img[tmplen+1] <= img[tmplen+2]) )  // ǰ�� ��ɫ ������ ��ɫ
            {
                //ѡ�� ���ֵ���ֵ��ǰһ�� ��Ϊ ��ֵ
                thresholdimg = (img[tmplen+1] + img[tmplen+2])/2;

                //ɨ����һ�� ���� ����ֵ (�ȴ˵����)
                while(img[tmplen] <= thresholdimg)
                {
                    bin[tmplen] = 0;                //��ɫ
                    tmplen--;
                    if(tmplen == 0)      //��β�� ,ֱ���˳�
                    {
                        if(img[tmplen] <= thresholdimg)
                        {
                             bin[tmplen] = 0;                //��ɫ
                        }
                        return ;
                    }
                    else if (tmplen > len)
                    {
                         return;
                    }
                }
                tmplen -= safe_isolation;
                if((tmplen == 0)|| (tmplen > len))
                {
                    return;
                }

                //�ȴ����ֵ����
                while(difimg[tmplen] > diff_threshold)
                {
                    tmplen--;
                    if((tmplen == 0)|| (tmplen > len))
                    {
                        return;
                    }
                }
            }
            else
            {
                //ǰ�� �� ��
                if(thldnum == 1)
                {
                    //����� ���ݶ��� ��ɫ��
                    tmpnum  = tmplen + 1;
                    while(tmpnum < len)
                    {
                        bin[tmpnum] = 0;                //��ɫ
                        tmpnum ++;
                    }
                }
            }


        }
    }
}






