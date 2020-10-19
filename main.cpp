#include "stm32f4xx.h"
#include "clockconfig.h"
#include <FreeRTOS.h>
#include <task.h>
#include <portmacro.h>

custom_libraries::clock_config system_clock;

extern "C" void led1_task(void* pvParameter){
  while(1){
    for(volatile int i = 0; i < 2000000; i++){}
    GPIOA->ODR ^= (1<<6);
  }
}

extern "C" void led2_task(void* pvParameter){
  while(1){
    for(volatile int i = 0; i < 2000000; i++){}
    GPIOA->ODR ^= (1<<7);
  }
}

int main(void) {
  
  system_clock.initialize();
  
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  GPIOA->MODER |= GPIO_MODER_MODER6_0;
  GPIOA->ODR |= GPIO_ODR_ODR_6;
  GPIOA->MODER |= GPIO_MODER_MODER7_0;
  GPIOA->ODR |= GPIO_ODR_ODR_7;

  xTaskCreate(led1_task,"led 1 controller",100,NULL,1,NULL);
  xTaskCreate(led2_task,"led 2 controller",100,NULL,1,NULL);
  vTaskStartScheduler();

  while(1){

  }
}
