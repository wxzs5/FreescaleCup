#ifndef _Init_H
#define _Init_H


#define MAX_NUM 32

void Init_all();
void Init_uart4(void);
void uart4_test_handler(void);

void Init_uart1(void);
void uart1_handler(void);

void Init_PORT_C(void);
void PORTC_IRQHandler(void);
void stop_IRQProcess(void);
void Init_my_NRF(void);
void PORTE_IRQHandler(void);

void Queue_Init(Info_queue *queue);
void Info_Init();  //赛道信息队列初始化
void State_Init();

#endif

