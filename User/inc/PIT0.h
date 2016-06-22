#ifndef _PIT_H
#define _PIT_H


/*************************
设置系统时间变量
*************************/
extern uint8 TIME0flag_2ms   ;                    //PTI0 5ms标志位
extern uint8 TIME0flag_5ms   ;                    //PTI0 5ms标志位
extern uint8 TIME0flag_10ms  ;                    //PTI0 10ms标志位
extern uint8 TIME0flag_15ms  ;                    //PTI0 15ms标志位
extern uint8 TIME0flag_20ms  ;                    //PTI0 20ms标志位
extern uint8 TIME0flag_25ms ;                     //PTI0 80ms标志位
extern uint8 TIME0flag_100ms ;                     //PTI0 100ms标志位

void Init_PIT0();
void PIT0_IRQHandler(void);



#endif
