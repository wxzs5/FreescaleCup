#ifndef _key_int_H
#define _key_int_H

extern uint8 ccd_switch_flag;
extern float proportion ;

void Init_PORT(void);
void PORTB_IRQHandler(void);        //PORTD端口中断服务函数

void B0_Process();
void B1_Process();
void B2_Process();
void B3_Process();
void B4_Process();
#endif
