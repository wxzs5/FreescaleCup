#ifndef _CCD_H
#define _CCD_H

#define CCD1_SI_SetVal()   gpio_set(PTE28,1)
#define CCD1_SI_ClrVal()   gpio_set(PTE28,0)
#define CCD1_CLK_ClrVal()  gpio_set(PTE26,0)
#define CCD1_CLK_SetVal()  gpio_set(PTE26,1)

#define CCD2_SI_SetVal()   gpio_set(PTE24,1)
#define CCD2_SI_ClrVal()   gpio_set(PTE24,0)
#define CCD2_CLK_ClrVal()  gpio_set(PTE25,0)
#define CCD2_CLK_SetVal()  gpio_set(PTE25,1)


void CCD1_init(void) ;
void CCD2_init(void) ;

void CCD1_StartIntegration(void) ;
void CCD2_StartIntegration(void) ;

void CCD1_ImageCapture(uint8 * ImageData) ;
void CCD2_ImageCapture(uint8 * ImageData) ;

void SamplingDelay(void) ;
void SendHex(uint8 hex) ;
void SendImageData(uint8 * ImageData) ;



#endif
