/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ݴ�����-��������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"  
#include "./lcd/bsp_ili9806g_lcd.h"
#include "./touch/gt5xx.h"
#include "./dwt_delay/core_delay.h"   
#include "./touch/palette.h"



/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main ( void )
{
	LED_GPIO_Config();
	ILI9806G_Init ();         //LCD ��ʼ��

	USART_Config();	

  /* ��ʼ���ں˶�ʱ�� */
  CPU_TS_TmrInit();
	
	//����0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�
	//���Ƽ�ʹ������ģʽ��ʾ����	����ģʽ��ʾ���ֻ��о���Ч��			
	//���� 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����  
  ILI9806G_GramScan ( 3 );	

	/* �趨��Һ��ɨ�跽����ٳ�ʼ���������������������Һ����ɨ�跽�����ƥ��Ĵ������� */
	/* ÿ���޸�Һ��ɨ�跽���Ӧ���µ���һ��GTP_Init_Panel�������´������� */
	GTP_Init_Panel(); 
    
	printf("\r\n ********** ����������� *********** \r\n"); 
	printf("\r\n ��������ʾ�����������Ķ������е�readme.txt�ļ�˵��������Ҫ���FLASH��ˢ��ģ����\r\n"); 
 
	
	//���ƴ����������
	Palette_Init(LCD_SCAN_MODE);
    
	while ( 1 )
	{
	}
	
	
}





/*********************************************END OF FILE**********************/

