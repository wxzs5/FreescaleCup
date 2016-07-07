#ifndef _Init_H
#define _Init_H


#define IIC_ENABLE 1


#define MAX_NUM 32


#define Bell_On gpio_set(PTC3,0)
#define Bell_Off gpio_set(PTC3,0)

void Init_all();
void Init_uart4(void);
void uart4_test_handler(void);

void Init_PORT_C(void);
void PORTC_IRQHandler(void);
void stop_IRQProcess(void);
void PORTE_IRQHandler(void);

#endif

