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
 *  @note       ���Բ�ѯ�����뷢����صĲ��ִ���
 */
void main()
{
    char ch;

    //uart_init(UART3,115200);     //��ʼ������(���� printf ���� ���õĶ˿ھ��� UART3���Ѿ���ʼ���ˣ���˴˴�����Ҫ�ٳ�ʼ��)

    printf("\nɽ���ѧ123��̳:www.vcan123.com");

    uart_putstr    (UART3 , "\n\n\n�������ݣ������з���:");         //�����ַ���

    while(1)
    {
        if(uart_query (UART3) != 0)                                 //��ѯ�Ƿ���յ�����
        {
            uart_getchar (UART3,&ch);                               //�ȴ�����һ�����ݣ����浽 ch��
            uart_putchar(UART3, ch);                                //����1���ֽ�
        }

        if(uart_querychar (UART3, &ch) != 0)                        //��ѯ����1���ַ�
        {
            uart_putchar(UART3, ch);                                //����1���ֽ�
        }

        //ע���������� if ��ʵ�ֹ��ܶ���һ���ġ�

        //uart_getchar �� uart_querychar ���������� ��ǰ�� ��Ҫ�ȴ����յ����ݣ����߲�ѯ�Ƿ���յ������յ��ͽ��գ����ղ������˳�
    }
}
