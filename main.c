#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "stm32f4xx_conf.h"

static int delaytime = 30000;

static void LCD_display_task(void *pvParameters);
void RCC_Configuration(void);
void GPIO_Configuration(void);

int main(void)
{
	/* Create a task to display something in the LCD. */
  	xTaskCreate(LCD_display_task,
             (signed portCHAR *) "Liquid Crystal Display",
             512 /* stack size */, NULL,
             tskIDLE_PRIORITY + 5, NULL);

 	/* Start running the tasks. */
 	 vTaskStartScheduler();
  	return 0;
}
static void LCD_display_task(void *pvParameters)
{
	char display[]="0123456789";
	char *str;
	str=display;	

	RCC_Configuration();
	GPIO_Configuration();
	
	Init_LCD();         		
	Delay(delaytime);
	LCD_CMD(0x0080);			
	Delay(delaytime);
	while(*str!=0){
	LCD_DATA(*str++);
	Delay(delaytime);
	}     			
	str=display;
	while(1);
}


void RCC_Configuration(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef G;
	G.GPIO_Pin=0xffff;
	G.GPIO_Speed=GPIO_Speed_50MHz;
	G.GPIO_Mode=GPIO_Mode_OUT;
	G.GPIO_OType=GPIO_OType_PP;
	G.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&G);

}


void vApplicationTickHook()
{
}
