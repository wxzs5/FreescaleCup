/**
  ******************************************************************************
  * @file    dma.h
  * @author  YANDLD
  * @version V2.5
  * @date    2014.3.26
  * @brief   www.beyondcore.net   http://upcmcu.taobao.com 
  * @note    此文件为芯片DMA模块的底层功能函数
  ******************************************************************************
  */
#ifndef __CH_DMA_H__
#define __CH_DMA_H__
  
#include <stdint.h>
#include <stdbool.h>
#include "common.h"
#include "include.h"

#define ARRAY_SIZE(x)   (sizeof(x) / sizeof((x)[0]))
/* ----------------------------------------------------------------------------
   -- DMA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup DMA_Peripheral_Access_Layer DMA Peripheral Access Layer
 * @{
 */

/** DMA - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR;                                /**< Control Register, offset: 0x0 */
  __I  uint32_t ES;                                /**< Error Status Register, offset: 0x4 */
       uint8_t RESERVED_0[4];
  __IO uint32_t ERQ;                               /**< Enable Request Register, offset: 0xC */
       uint8_t RESERVED_1[4];
  __IO uint32_t EEI;                               /**< Enable Error Interrupt Register, offset: 0x14 */
  __O  uint8_t CEEI;                               /**< Clear Enable Error Interrupt Register, offset: 0x18 */
  __O  uint8_t SEEI;                               /**< Set Enable Error Interrupt Register, offset: 0x19 */
  __O  uint8_t CERQ;                               /**< Clear Enable Request Register, offset: 0x1A */
  __O  uint8_t SERQ;                               /**< Set Enable Request Register, offset: 0x1B */
  __O  uint8_t CDNE;                               /**< Clear DONE Status Bit Register, offset: 0x1C */
  __O  uint8_t SSRT;                               /**< Set START Bit Register, offset: 0x1D */
  __O  uint8_t CERR;                               /**< Clear Error Register, offset: 0x1E */
  __O  uint8_t CINT;                               /**< Clear Interrupt Request Register, offset: 0x1F */
       uint8_t RESERVED_2[4];
  __IO uint32_t INT;                               /**< Interrupt Request Register, offset: 0x24 */
       uint8_t RESERVED_3[4];
  __IO uint32_t ERR;                               /**< Error Register, offset: 0x2C */
       uint8_t RESERVED_4[4];
  __IO uint32_t HRS;                               /**< Hardware Request Status Register, offset: 0x34 */
       uint8_t RESERVED_5[200];
  __IO uint8_t DCHPRI3;                            /**< Channel n Priority Register, offset: 0x100 */
  __IO uint8_t DCHPRI2;                            /**< Channel n Priority Register, offset: 0x101 */
  __IO uint8_t DCHPRI1;                            /**< Channel n Priority Register, offset: 0x102 */
  __IO uint8_t DCHPRI0;                            /**< Channel n Priority Register, offset: 0x103 */
  __IO uint8_t DCHPRI7;                            /**< Channel n Priority Register, offset: 0x104 */
  __IO uint8_t DCHPRI6;                            /**< Channel n Priority Register, offset: 0x105 */
  __IO uint8_t DCHPRI5;                            /**< Channel n Priority Register, offset: 0x106 */
  __IO uint8_t DCHPRI4;                            /**< Channel n Priority Register, offset: 0x107 */
  __IO uint8_t DCHPRI11;                           /**< Channel n Priority Register, offset: 0x108 */
  __IO uint8_t DCHPRI10;                           /**< Channel n Priority Register, offset: 0x109 */
  __IO uint8_t DCHPRI9;                            /**< Channel n Priority Register, offset: 0x10A */
  __IO uint8_t DCHPRI8;                            /**< Channel n Priority Register, offset: 0x10B */
  __IO uint8_t DCHPRI15;                           /**< Channel n Priority Register, offset: 0x10C */
  __IO uint8_t DCHPRI14;                           /**< Channel n Priority Register, offset: 0x10D */
  __IO uint8_t DCHPRI13;                           /**< Channel n Priority Register, offset: 0x10E */
  __IO uint8_t DCHPRI12;                           /**< Channel n Priority Register, offset: 0x10F */
  __IO uint8_t DCHPRI19;                           /**< Channel n Priority Register, offset: 0x110 */
  __IO uint8_t DCHPRI18;                           /**< Channel n Priority Register, offset: 0x111 */
  __IO uint8_t DCHPRI17;                           /**< Channel n Priority Register, offset: 0x112 */
  __IO uint8_t DCHPRI16;                           /**< Channel n Priority Register, offset: 0x113 */
  __IO uint8_t DCHPRI23;                           /**< Channel n Priority Register, offset: 0x114 */
  __IO uint8_t DCHPRI22;                           /**< Channel n Priority Register, offset: 0x115 */
  __IO uint8_t DCHPRI21;                           /**< Channel n Priority Register, offset: 0x116 */
  __IO uint8_t DCHPRI20;                           /**< Channel n Priority Register, offset: 0x117 */
  __IO uint8_t DCHPRI27;                           /**< Channel n Priority Register, offset: 0x118 */
  __IO uint8_t DCHPRI26;                           /**< Channel n Priority Register, offset: 0x119 */
  __IO uint8_t DCHPRI25;                           /**< Channel n Priority Register, offset: 0x11A */
  __IO uint8_t DCHPRI24;                           /**< Channel n Priority Register, offset: 0x11B */
  __IO uint8_t DCHPRI31;                           /**< Channel n Priority Register, offset: 0x11C */
  __IO uint8_t DCHPRI30;                           /**< Channel n Priority Register, offset: 0x11D */
  __IO uint8_t DCHPRI29;                           /**< Channel n Priority Register, offset: 0x11E */
  __IO uint8_t DCHPRI28;                           /**< Channel n Priority Register, offset: 0x11F */
       uint8_t RESERVED_6[3808];
  struct {                                         /* offset: 0x1000, array step: 0x20 */
    __IO uint32_t SADDR;                             /**< TCD Source Address, array offset: 0x1000, array step: 0x20 */
    __IO uint16_t SOFF;                              /**< TCD Signed Source Address Offset, array offset: 0x1004, array step: 0x20 */
    __IO uint16_t ATTR;                              /**< TCD Transfer Attributes, array offset: 0x1006, array step: 0x20 */
    union {                                          /* offset: 0x1008, array step: 0x20 */
      __IO uint32_t NBYTES_MLNO;                       /**< TCD Minor Byte Count (Minor Loop Disabled), array offset: 0x1008, array step: 0x20 */
      __IO uint32_t NBYTES_MLOFFNO;                    /**< TCD Signed Minor Loop Offset (Minor Loop Enabled and Offset Disabled), array offset: 0x1008, array step: 0x20 */
      __IO uint32_t NBYTES_MLOFFYES;                   /**< TCD Signed Minor Loop Offset (Minor Loop and Offset Enabled), array offset: 0x1008, array step: 0x20 */
    };
    __IO uint32_t SLAST;                             /**< TCD Last Source Address Adjustment, array offset: 0x100C, array step: 0x20 */
    __IO uint32_t DADDR;                             /**< TCD Destination Address, array offset: 0x1010, array step: 0x20 */
    __IO uint16_t DOFF;                              /**< TCD Signed Destination Address Offset, array offset: 0x1014, array step: 0x20 */
    union {                                          /* offset: 0x1016, array step: 0x20 */
      __IO uint16_t CITER_ELINKNO;                     /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x1016, array step: 0x20 */
      __IO uint16_t CITER_ELINKYES;                    /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x1016, array step: 0x20 */
    };
    __IO uint32_t DLAST_SGA;                         /**< TCD Last Destination Address Adjustment/Scatter Gather Address, array offset: 0x1018, array step: 0x20 */
    __IO uint16_t CSR;                               /**< TCD Control and Status, array offset: 0x101C, array step: 0x20 */
    union {                                          /* offset: 0x101E, array step: 0x20 */
      __IO uint16_t BITER_ELINKNO;                     /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x101E, array step: 0x20 */
      __IO uint16_t BITER_ELINKYES;                    /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x101E, array step: 0x20 */
    };
  } TCD[32];
} DMA_Type;

/** SIM - Register Layout Typedef */
typedef struct {
  __IO uint32_t SOPT1;                             /**< System Options Register 1, offset: 0x0 */
  __IO uint32_t SOPT1CFG;                          /**< SOPT1 Configuration Register, offset: 0x4 */
       uint8_t RESERVED_0[4092];
  __IO uint32_t SOPT2;                             /**< System Options Register 2, offset: 0x1004 */
       uint8_t RESERVED_1[4];
  __IO uint32_t SOPT4;                             /**< System Options Register 4, offset: 0x100C */
  __IO uint32_t SOPT5;                             /**< System Options Register 5, offset: 0x1010 */
  __IO uint32_t SOPT6;                             /**< System Options Register 6, offset: 0x1014 */
  __IO uint32_t SOPT7;                             /**< System Options Register 7, offset: 0x1018 */
       uint8_t RESERVED_2[8];
  __I  uint32_t SDID;                              /**< System Device Identification Register, offset: 0x1024 */
  __IO uint32_t SCGC1;                             /**< System Clock Gating Control Register 1, offset: 0x1028 */
  __IO uint32_t SCGC2;                             /**< System Clock Gating Control Register 2, offset: 0x102C */
  __IO uint32_t SCGC3;                             /**< System Clock Gating Control Register 3, offset: 0x1030 */
  __IO uint32_t SCGC4;                             /**< System Clock Gating Control Register 4, offset: 0x1034 */
  __IO uint32_t SCGC5;                             /**< System Clock Gating Control Register 5, offset: 0x1038 */
  __IO uint32_t SCGC6;                             /**< System Clock Gating Control Register 6, offset: 0x103C */
  __IO uint32_t SCGC7;                             /**< System Clock Gating Control Register 7, offset: 0x1040 */
  __IO uint32_t CLKDIV1;                           /**< System Clock Divider Register 1, offset: 0x1044 */
  __IO uint32_t CLKDIV2;                           /**< System Clock Divider Register 2, offset: 0x1048 */
  __IO uint32_t FCFG1;                             /**< Flash Configuration Register 1, offset: 0x104C */
  __I  uint32_t FCFG2;                             /**< Flash Configuration Register 2, offset: 0x1050 */
  __I  uint32_t UIDH;                              /**< Unique Identification Register High, offset: 0x1054 */
  __I  uint32_t UIDMH;                             /**< Unique Identification Register Mid-High, offset: 0x1058 */
  __I  uint32_t UIDML;                             /**< Unique Identification Register Mid Low, offset: 0x105C */
  __I  uint32_t UIDL;                              /**< Unique Identification Register Low, offset: 0x1060 */
       uint8_t RESERVED_3[4];
  __IO uint32_t CLKDIV4;                           /**< System Clock Divider Register 4, offset: 0x1068 */
  __IO uint32_t MCR;                               /**< Misc Control Register, offset: 0x106C */
} SIM_Type;

/* SCGC6 Bit Fields */
#define SIM_SCGC6_FTF_MASK                       0x1u
#define SIM_SCGC6_FTF_SHIFT                      0
#define SIM_SCGC6_DMAMUX_MASK                    0x2u
#define SIM_SCGC6_DMAMUX_SHIFT                   1
#define SIM_SCGC6_FLEXCAN0_MASK                  0x10u
#define SIM_SCGC6_FLEXCAN0_SHIFT                 4
#define SIM_SCGC6_RNGA_MASK                      0x200u
#define SIM_SCGC6_RNGA_SHIFT                     9
#define SIM_SCGC6_SPI0_MASK                      0x1000u
#define SIM_SCGC6_SPI0_SHIFT                     12
#define SIM_SCGC6_SPI1_MASK                      0x2000u
#define SIM_SCGC6_SPI1_SHIFT                     13
#define SIM_SCGC6_I2S_MASK                       0x8000u
#define SIM_SCGC6_I2S_SHIFT                      15
#define SIM_SCGC6_CRC_MASK                       0x40000u
#define SIM_SCGC6_CRC_SHIFT                      18
#define SIM_SCGC6_USBDCD_MASK                    0x200000u
#define SIM_SCGC6_USBDCD_SHIFT                   21
#define SIM_SCGC6_PDB_MASK                       0x400000u
#define SIM_SCGC6_PDB_SHIFT                      22
#define SIM_SCGC6_PIT_MASK                       0x800000u
#define SIM_SCGC6_PIT_SHIFT                      23
#define SIM_SCGC6_FTM0_MASK                      0x1000000u
#define SIM_SCGC6_FTM0_SHIFT                     24
#define SIM_SCGC6_FTM1_MASK                      0x2000000u
#define SIM_SCGC6_FTM1_SHIFT                     25
#define SIM_SCGC6_FTM2_MASK                      0x4000000u
#define SIM_SCGC6_FTM2_SHIFT                     26
#define SIM_SCGC6_ADC0_MASK                      0x8000000u
#define SIM_SCGC6_ADC0_SHIFT                     27
#define SIM_SCGC6_RTC_MASK                       0x20000000u
#define SIM_SCGC6_RTC_SHIFT                      29
#define SIM_SCGC6_DAC0_MASK                      0x80000000u
#define SIM_SCGC6_DAC0_SHIFT                     31

/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base address */
#define SIM_BASE                                 (0x40047000u)
/** Peripheral SIM base pointer */
#define SIM                                      ((SIM_Type *)SIM_BASE)
/** Array initializer of SIM peripheral base pointers */
#define SIM_BASES                                { SIM }

/* DMAMUX - Peripheral instance base addresses */
/** Peripheral DMAMUX base address */
#define DMAMUX_BASE                              (0x40021000u)
/** Peripheral DMAMUX base pointer */
#define DMAMUX                                   ((DMAMUX_Type *)DMAMUX_BASE)
#define DMAMUX_BASE_PTR                          (DMAMUX)
/** Array initializer of DMAMUX peripheral base pointers */
#define DMAMUX_BASES                             { DMAMUX }

/* DMA - Peripheral instance base addresses */
/** Peripheral DMA base address */
#define DMA_BASE                                 (0x40008000u)
/** Peripheral DMA base pointer */
#define DMA0                                     ((DMA_Type *)DMA_BASE)
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASES                                { DMA0 }

/** DMAMUX - Register Layout Typedef */
typedef struct {
  __IO uint8_t CHCFG[16];                          /**< Channel Configuration Register, array offset: 0x0, array step: 0x1 */
} DMAMUX_Type;

/* DMA 触发源选择 */
#define DISABLE_DMAREQ          0
#define UART0_REV_DMAREQ        2
#define UART0_TRAN_DMAREQ       3
#define UART1_REV_DMAREQ        4
#define UART1_TRAN_DMAREQ       5
#define UART2_REV_DMAREQ        6
#define UART2_TRAN_DMAREQ       7
#define UART3_REV_DMAREQ        8
#define UART3_TRAN_DMAREQ       9
#define UART4_REV_DMAREQ        10
#define UART4_TRAN_DMAREQ       11
#define UART5_REV_DMAREQ        12
#define UART5_TRAN_DMAREQ       13
#define I2S0_REV_DMAREQ         14
#define I2S0_TRAN_DMAREQ        15
#define SPI0_REV_DMAREQ         16
#define SPI0_TRAN_DMAREQ        17
#define SPI1_REV_DMAREQ         18
#define SPI1_TRAN_DMAREQ        19
#define SPI2_REV_DMAREQ         20
#define SPI2_TRAN_DMAREQ        21
#define I2C0_DMAREQ             22
#define I2C1_DMAREQ             23
#define FTM0_CH0_DMAREQ         24
#define FTM0_CH1_DMAREQ         25
#define FTM0_CH2_DMAREQ         26
#define FTM0_CH3_DMAREQ         27
#define FTM0_CH4_DMAREQ         28
#define FTM0_CH5_DMAREQ         29
#define FTM0_CH6_DMAREQ         30
#define FTM0_CH7_DMAREQ         31
#define FTM1_CH0_DMAREQ         32
#define FTM1_CH1_DMAREQ         33
#define FTM2_CH0_DMAREQ         34
#define FTM2_CH1_DMAREQ         35
#define FTM3_CH0_DMAREQ         36
#define FTM3_CH1_DMAREQ         37
#define FTM3_CH2_DMAREQ         38
#define FTM3_CH3_DMAREQ         39  
#define ADC0_DMAREQ             40
#define ADC1_DMAREQ             41
#define CMP0_DMAREQ             42
#define CMP1_DMAREQ             43
#define CMP2_DMAREQ             44
#define DAC0_DMAREQ             45
#define DAC1_DMAREQ             46
#define CMT_DMAREQ              47
#define PDB_DMAREQ              48
#define PORTA_DMAREQ            49
#define PORTB_DMAREQ            50
#define PORTC_DMAREQ            51
#define PORTD_DMAREQ            52
#define PORTE_DMAREQ            53
#define FTM3_CH4_DMAREQ         54
#define FTM3_CH5_DMAREQ         55
#define FTM3_CH6_DMAREQ         56
#define FTM3_CH7_DMAREQ         57
#define MUX0_DMAREQ             58
#define MUX1_DMAREQ             59
#define MUX2_DMAREQ             60
#define MUX3_DMAREQ             61

/* DMA通道 */
#define HW_DMA_CH0    (0x00)  /* DMA0通道，以下一次类推 */
#define HW_DMA_CH1    (0x01)  
#define HW_DMA_CH2    (0x02)  
#define HW_DMA_CH3    (0x03)  

/**
 * \enum DMA_TriggerSource_Type
 * \brief DMA 触发模式选择
 */
typedef enum
{
    kDMA_TriggerSource_Normal,    /**< 正常模式 */
    kDMA_TriggerSource_Periodic,  /**< 周期触发模式 */
}DMA_TriggerSource_Type;

/**
 * \enum DMA_DataWidthBit_Type
 * \brief DMA搬运数据端口位宽设置
 */
typedef enum
{
    kDMA_DataWidthBit_8,   /**< 8 bit data width */
    kDMA_DataWidthBit_16,  /**< 16 bit data width */
    kDMA_DataWidthBit_32,  /**< 32 bit data width */
}DMA_DataWidthBit_Type; 

/**
 * \enum DMA_Modulo_Type
 * \brief DMA Moduluo 设置
 */
typedef enum 
{
    kDMA_ModuloDisable = 0x0U,
    kDMA_Modulo2bytes = 0x1U,
    kDMA_Modulo4bytes = 0x2U,
    kDMA_Modulo8bytes = 0x3U,
    kDMA_Modulo16bytes = 0x4U,
    kDMA_Modulo32bytes = 0x5U,
    kDMA_Modulo64bytes = 0x6U,
    kDMA_Modulo128bytes = 0x7U,
    kDMA_Modulo256bytes = 0x8U,
    kDMA_Modulo512bytes = 0x9U,
    kDMA_Modulo1Kbytes = 0xaU,
    kDMA_Modulo2Kbytes = 0xbU,
    kDMA_Modulo4Kbytes = 0xcU,
    kDMA_Modulo8Kbytes = 0xdU,
    kDMA_Modulo16Kbytes = 0xeU,
    kDMA_Modulo32Kbytes = 0xfU,
    kDMA_Modulo64Kbytes = 0x10U,
    kDMA_Modulo128Kbytes = 0x11U,
    kDMA_Modulo256Kbytes = 0x12U,
    kDMA_Modulo512Kbytes = 0x13U,
    kDMA_Modulo1Mbytes = 0x14U,
    kDMA_Modulo2Mbytes = 0x15U,
    kDMA_Modulo4Mbytes = 0x16U,
    kDMA_Modulo8Mbytes = 0x17U,
    kDMA_Modulo16Mbytes = 0x18U,
    kDMA_Modulo32Mbytes = 0x19U,
    kDMA_Modulo64Mbytes = 0x1aU,
    kDMA_Modulo128Mbytes = 0x1bU,
    kDMA_Modulo256Mbytes = 0x1cU,
    kDMA_Modulo512Mbytes = 0x1dU,
    kDMA_Modulo1Gbytes = 0x1eU,
    kDMA_Modulo2Gbytes = 0x1fU
} DMA_Modulo_Type;

/**
 * \struct DMA_InitTypeDef
 * \brief DMA 初始化结构
 */
typedef struct 
{
    uint8_t                     chl;                                ///< DMA通道号0~15      
    uint8_t                     chlTriggerSource;                   ///< DMA触发源选择 
    uint16_t                    minorLoopByteCnt;                   ///< MINOR LOOP 中一次传输的字节数 
    uint16_t                    majorLoopCnt;                       ///< MAJOR LOOP 循环次数 
    DMA_TriggerSource_Type      triggerSourceMode;                  ///< 触发模式选择 
    /* 源地址配置 */
    int32_t                     sAddrOffset;                ///< DMA每次读取sAddr之后 sAddr的偏移量 可正可负 
    uint32_t                    sAddr;                      ///< 数据源地址 
    DMA_DataWidthBit_Type       sDataWidth;                 ///< 数据源地址数据宽度 8 16 32 
    int32_t                     sLastAddrAdj;               ///< 所有MAJOR LOOP循环完成后 源地址偏移量 
    DMA_Modulo_Type             sMod;                       ///< Modulo 设置 参见 AN2898 
    /* 目标地址属性配置 */
    int32_t                     dAddrOffset;                
    uint32_t                    dAddr;                      
    DMA_DataWidthBit_Type       dDataWidth;                 
    int32_t                     dLastAddrAdj;               
    DMA_Modulo_Type             dMod;                       
}DMA_InitTypeDef;

/**
 * \enum DMA_ITConfig_Type
 * \brief DMA interrupt select
 */
typedef enum
{
    kDMA_IT_Half,               /**< 传输一半中断开启 */
    kDMA_IT_Major,              /**< 传输完成中断开启 */
}DMA_ITConfig_Type;  

/* Callback Type */
typedef void (*DMA_CallBackType)(void);

/* API functions */
uint32_t DMA_ChlAlloc(void);
void DMA_ChlFree(uint32_t chl);
uint32_t DMA_Init(DMA_InitTypeDef *DMA_InitStruct);
/* get vars and status */
uint32_t DMA_GetDestAddress(uint8_t ch);
uint32_t DMA_GetSourceAddress(uint8_t ch);
uint8_t DMA_IsMajorLoopComplete(uint8_t chl);
uint32_t DMA_GetMajorLoopCount(uint8_t chl);
/* control */
void DMA_SetMajorLoopCounter(uint8_t chl, uint32_t val);
void DMA_CancelTransfer(void);
void DMA_SetDestAddress(uint8_t chl, uint32_t address);
void DMA_SetSourceAddress(uint8_t chl, uint32_t address);
void DMA_EnableRequest(uint8_t chl);
void DMA_DisableRequest(uint8_t chl);
void DMA_EnableAutoDisableRequest(uint8_t chl , bool flag);
/* IT funtions */
void DMA_ITConfig(uint8_t chl, DMA_ITConfig_Type config, bool status);
void DMA_CallbackInstall(uint8_t chl, DMA_CallBackType AppCBFun);
/* chl link */
void DMA_EnableMajorLink(uint8_t chl , uint8_t linkChl, bool flag);

void UART_DMASendConfig(UARTn_e uratn, uint8_t dmaChl);

uint32_t UART_SendWithDMA(uint32_t dmaChl, const uint8_t *buf, uint32_t size);

#endif
  
