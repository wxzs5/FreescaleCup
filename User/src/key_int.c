#include "include.h"

uint8 mode_correct = 0;
uint8 ccd_switch_flag = 1;
float proportion = 0;




void Init_PORT(void)
{
  port_init(PTB18, ALT1 | IRQ_FALLING | PF | PULLUP);
  port_init(PTB20, ALT1 | IRQ_FALLING | PF | PULLUP);
  port_init(PTB21, ALT1 | IRQ_FALLING | PF | PULLUP );
  port_init(PTB22, ALT1 | IRQ_FALLING | PF | PULLUP );
  port_init(PTB23, ALT1 | IRQ_FALLING | PF | PULLUP );
  adc_init(ADC1_DM1);

  set_vector_handler(PORTB_VECTORn , PORTB_IRQHandler);
  enable_irq (PORTB_IRQn);
}


void PORTB_IRQHandler(void)
{
  PORT_FUNC(B, 18, B2_Process);
  PORT_FUNC(B, 20, B1_Process);
  PORT_FUNC(B, 21, B4_Process);
  PORT_FUNC(B, 22, B3_Process);
  PORT_FUNC(B, 23, B0_Process);
}


void B0_Process()
{
  Parameter_info.OLED_NoAction_Flag = 0;//按键已经有反应了
  DELAY_MS(20);
  if (gpio_get(PTB23) == 0)
  {
    switch (Menu.enter_exit)
    {
    case 1: Menu.choice_flag += 100; break;
    case 2: Menu.choice_flag += 10 ; break;
    }
    Menu.Clear = 1;
  }
}

void B1_Process()
{
  Parameter_info.OLED_NoAction_Flag = 0;//按键已经有反应了
  DELAY_MS(20);
  if (gpio_get(PTB20) == 0)
  {
    switch (Menu.enter_exit)
    {
    case 1: Menu.choice_flag -= 100; break;
    case 2: Menu.choice_flag -= 10 ; break;
    }
    Menu.Clear = 1;
  }
}

void B2_Process()
{
  Parameter_info.OLED_NoAction_Flag = 0;//按键已经有反应了
  DELAY_MS(20);
  if (gpio_get(PTB18) == 0)
  {
    switch (Menu.enter_exit_temp)
    {
    case 3: Menu.enter_exit = 2; Menu.enter_exit_temp = 2; Menu.choice_flag = Menu.choice_flag / 10 * 10; break;
    case 2: Menu.enter_exit = 1; Menu.enter_exit_temp = 1; Menu.choice_flag = Menu.choice_flag / 100 * 100; break;
    case 1: Menu.enter_exit = 1; Menu.enter_exit_temp = 1; break;
    }
    Menu.Clear = 1;
  }
}

void B3_Process()
{
  Parameter_info.OLED_NoAction_Flag = 0;//按键已经有反应了
  DELAY_MS(20);
  if (gpio_get(PTB22) == 0)
  {
    switch (Menu.enter_exit_temp)
    {
    case 0: Menu.enter_exit = 1; Menu.enter_exit_temp = 1; Menu.choice_flag = Menu.choice_flag / 10 * 10; break;
    case 1: Menu.enter_exit = 2; Menu.enter_exit_temp = 2; Menu.choice_flag = Menu.choice_flag / 100 * 100 + 10; break;
    case 2: Menu.enter_exit = 3; Menu.enter_exit_temp = 3; Menu.choice_flag += 1; break;
    }
    Menu.Clear = 1;
  }
}

void B4_Process()
{
  Parameter_info.OLED_NoAction_Flag = 0;//按键已经有反应了
  DELAY_MS(20);
  if (gpio_get(PTB21) == 0)
  {
    Menu.Clear = 1;
    stop_flag = !stop_flag;
  }
}

