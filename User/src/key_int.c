#include "include.h"

uint8 mode_correct = 0;
uint8 ccd_switch_flag = 1;
float proportion = 0;

void Init_PORT(void)
{
  port_init(PTB0, ALT1 | IRQ_EITHER);
  port_init(PTB1, ALT1 | IRQ_EITHER);
  port_init(PTB2, ALT1 | IRQ_EITHER );
  port_init(PTB3, ALT1 | IRQ_EITHER );
  port_init(PTB4, ALT1 | IRQ_EITHER );
  port_init(PTB5, ALT1 | IRQ_EITHER );

  set_vector_handler(PORTB_VECTORn , PORTB_IRQHandler);
  enable_irq (PORTB_IRQn);

  B0_Process();
  B1_Process();
  B2_Process();
  B3_Process();
  B4_Process();
  B5_Process();
}


void PORTB_IRQHandler(void)
{
  PORT_FUNC(B, 0, B0_Process);
  PORT_FUNC(B, 1, B1_Process);
  PORT_FUNC(B, 2, B2_Process);
  PORT_FUNC(B, 3, B3_Process);
  PORT_FUNC(B, 4, B4_Process);
  PORT_FUNC(B, 5, B5_Process);

}


void B0_Process()
{
  if (PTB0_IN == 1)
  {
    ccd_switch_flag = 1;
  }
  else
  {
    ccd_switch_flag = 0;
  }
}

void B1_Process()
{
  if (PTB1_IN == 1)
  {
  }
  else
  {
  }
}

void B2_Process()
{
  if (PTB2_IN == 1)
  {

  }
  else
  {

  }
}

void B3_Process()
{
  if (PTB3_IN == 1)
  {

  }
  else
  {

  }
}

void B4_Process()
{
  if (PTB4_IN == 1)
  {

  }
  else
  {

  }
}

void B5_Process()
{
  if (PTB5_IN == 1)
  {

  }
  else
  {

  }
}
