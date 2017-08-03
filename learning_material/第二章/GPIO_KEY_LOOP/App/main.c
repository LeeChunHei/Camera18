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
 *  @note       ���� KEY ѭ��ɨ��
 */
void main()
{
    key_init(KEY_A);

    printf("\n******* GPIO ��ѯɨ�� �������� *******");

    while(1)
    {
        if(key_check(KEY_A) == KEY_DOWN) //���key״̬������ʱ������
        {
            printf("\n��������");       //ͨ���������ֲ鿴����ʾ��������

            DELAY_MS(500);              //���������ʱ�䣬�ᷢ�֣�ʱ��Խ����
                                        //����˫������û��ʶ��ڶ��βɼ�
        }
    }
}

