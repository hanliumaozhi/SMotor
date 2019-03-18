#ifndef __DRV8301_H
#define __DRV8301_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "spi.h"

// SPI registers
#define DRV_SPI_READ            0x8000
#define DRV_SPI_WRITE           0x0000

#define DRV_SPI_ADR(x)          ((x<<11)&0x7800)
#define DRV_SPI_SR1             DRV_SPI_ADR(0)
#define DRV_SPI_SR2             DRV_SPI_ADR(1)
#define DRV_SPI_CTRL1           DRV_SPI_ADR(2)
#define DRV_SPI_CTRL2           DRV_SPI_ADR(3)

// SR1 bits
#define SR1_FAULT           0x0400
#define SR1_GVDD_UV         0x0200
#define SR1_PVDD_UV         0x0100
#define SR1_OTSD            0x0080
#define SR1_OTW             0x0040
#define SR1_FETHA_OC        0x0020
#define SR1_FETLA_OC        0x0010
#define SR1_FETHB_OC        0x0008
#define SR1_FETLB_OC        0x0004
#define SR1_FETHC_OC        0x0002
#define SR1_FETLC_OC        0x0001

// SR2 bits
#define SR2_GVDD_OV         0x0080
#define SR2_DEVICE_ID       0x000f

// CTRL1 bits
#define CTRL1_GATE_CURRENT_1_7_A      0x0000
#define CTRL1_GATE_CURRENT_0_7_A      0x0001
#define CTRL1_GATE_CURRENT_0_25_A     0x0002
#define CTRL1_GATE_RESET_NORMAL       0x0000
#define CTRL1_GATE_RESET_LATCHED      0x0004
#define CTRL1_PWM_MODE_6_INPUT        0x0000
#define CTRL1_PWM_MODE_3_INPUT        0x0008
#define CTRL1_OCP_MODE_CURRENT_LIMIT  0x0000
#define CTRL1_OCP_MODE_LATCH_SHUTDOWN 0x0010
#define CTRL1_OCP_MODE_REPORT_ONLY    0x0020
#define CTRL1_OCP_MODE_DISABLED       0x0030
#define CTRL1_OC_ADJ_SET(x)           ((x<<6) & 0x07C0)

// CTRL2 bits
#define CTRL2_OCTW_MODE_BOTH          0x0000
#define CTRL2_OCTW_MODE_OT_ONLY       0x0001
#define CTRL2_OCTW_MODE_OC_ONLY       0x0002
#define CTRL2_GAIN_10                 0x0000
#define CTRL2_GAIN_20                 0x0004
#define CTRL2_GAIN_40                 0x0008
#define CTRL2_GAIN_80                 0x000C
#define CTRL2_DC_CAL_CH1_NORMAL       0x0000
#define CTRL2_DC_CAL_CH1_SHORT        0x0010
#define CTRL2_DC_CAL_CH2_NORMAL       0x0000
#define CTRL2_DC_CAL_CH2_SHORT        0x0020
#define CTRL2_OC_TOFF_CYCLE           0x0000
#define CTRL2_OC_TOFF_TIME            0x0040

void drv8301_setup(SPI_HandleTypeDef* spiHandle, GPIO_TypeDef* drv8301_port, uint16_t drv8301_pin);
void drv8301_init(void);



#ifdef __cplusplus
}
#endif
#endif
