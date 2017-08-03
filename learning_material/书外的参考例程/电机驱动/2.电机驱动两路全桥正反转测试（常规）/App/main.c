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

//��ɽ��������������Ȩ�������ƣ���ԭ��·�ı�ɫ��
//ע�⣺ɽ�������� �� ���� MOS �� ���뷴��ģ�IO ��� �͵�ƽ������ MOS �ܺ�ᷴ�࣬��� �ߵ�ƽ��������Ȼ��


//����ģʽ: PWM ���� IN �ܽ� ,IO���� INH ��ʹ�� ��
// INH ����Ϊ �ߵ�ƽ ��ʹ�� BTN7971
// IN  ����Ϊ �ߵ�ƽ , ���� �� IN ����Ϊ �͵�ƽ��ɲ����ע�⣬��ɲ�������ǽ�����ô�򵥣�
//����ģʽ �� ��ͣ���٣�INΪ�ߣ���Ȼ����٣�INΪ�ͣ����Ƿ�˼�������ܳ�������õķ���
//Ч����Σ� һ�߲� ���� ��һ�߲� ɲ��  ��������أ�

//���ɹ���ģʽ: PWM ���� INH �ܽ� ���� �Ƿ�ʹ�� ��IO ���� IN �ܽ�
// IN ����Ϊ �ߵ�ƽ  �� ����
// INH ����Ϊ �ߵ�ƽ , ʹ��оƬ������ȫ��״̬ �� INH ����Ϊ �͵�ƽ ������оƬ������ ������״̬
//���ɹ���ģʽ �� һʱ���ͣ�һʱ�ɿ����������������ٶ���ǰ������
//Ч����Σ� ���� BTN7971 ��ʵ���� ����Ϊ �ı� ��ѹֵ ���Ӷ� �ﵽ ���� ������ ��Ŀ�� ��оƬ�����������٣���������


//��ɱģʽ��PWM ���� INH �ܽ� ���� �Ƿ�ʹ�� ��IO ���� IN �ܽ�
// IN ����Ϊ �͵�ƽ  �� ɲ��
// INH ����Ϊ �ߵ�ƽ , ʹ��оƬ������ɲ��״̬ �� INH ����Ϊ �͵�ƽ ������оƬ������ ������״̬
//���һֱ���� ɲ��״̬���ᱧ��������Ӷ�ʹ�� С�� �򻬣������������ Ư�ơ�
//���һֱ���� ������״̬ ����� ����С���Ĺ���һֱ��������Ȼ�������֮���Ǿ�Ħ�������ﲻ�����Ħ������Ч���������ҪPWM����ռ�ձ�����ɱ


#define MOTOR1_IO   PTD15
#define MOTOR2_IO   PTA19
#define MOTOR3_IO   PTA5
#define MOTOR4_IO   PTA24

#define MOTOR_FTM   FTM0
#define MOTOR1_PWM  FTM_CH3
#define MOTOR2_PWM  FTM_CH4
#define MOTOR3_PWM  FTM_CH5
#define MOTOR4_PWM  FTM_CH6

#define MOTOR1_PWM_IO  FTM0_CH3
#define MOTOR2_PWM_IO  FTM0_CH4
#define MOTOR3_PWM_IO  FTM0_CH5
#define MOTOR4_PWM_IO  FTM0_CH6

#define MOTOR_HZ    50//(20*1000)
#define MOTOR_DUTY  80

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� ��� ����ʵ�� ,ɽ�� �ṩ�� �������ģ�飬�ܽŶ����� MOS �ܸ��룬�ź��Ƿ���ġ�
                ���糣��� �ߵ�ƽ ʹ��
 */
void main()
{
    printf("\n*****FTM ������� ����*****\n");

    FTM_PWM_init(MOTOR_FTM, MOTOR1_PWM,MOTOR_HZ,50);      //��ʼ�� ��� PWM
#if 0
    FTM_PWM_init(MOTOR_FTM, MOTOR2_PWM,MOTOR_HZ,100);      //��ʼ�� ��� PWM
    FTM_PWM_init(MOTOR_FTM, MOTOR3_PWM,MOTOR_HZ,100);      //��ʼ�� ��� PWM
    FTM_PWM_init(MOTOR_FTM, MOTOR4_PWM,MOTOR_HZ,100);      //��ʼ�� ��� PWM

    //IO�ܽ�����
    gpio_init(MOTOR1_IO,GPO,LOW);
    gpio_init(MOTOR2_IO,GPO,LOW);
    gpio_init(MOTOR3_IO,GPO,LOW);
    gpio_init(MOTOR4_IO,GPO,LOW);
#endif

    while(1)
    {


#if 0
        FTM_PWM_Duty(MOTOR_FTM, MOTOR1_PWM,100);
        FTM_PWM_Duty(MOTOR_FTM, MOTOR2_PWM,70);
        FTM_PWM_Duty(MOTOR_FTM, MOTOR3_PWM,70);
        FTM_PWM_Duty(MOTOR_FTM, MOTOR4_PWM,100);
        DELAY_MS(1000);


        FTM_PWM_Duty(MOTOR_FTM, MOTOR1_PWM,70);
        FTM_PWM_Duty(MOTOR_FTM, MOTOR2_PWM,100);
        FTM_PWM_Duty(MOTOR_FTM, MOTOR3_PWM,100);
        FTM_PWM_Duty(MOTOR_FTM, MOTOR4_PWM,70);
        DELAY_MS(1000);
#endif
    }

}