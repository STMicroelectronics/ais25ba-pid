/**
  ******************************************************************************
  * @file    ais25ba_reg.h
  * @author  Sensors Software Solution Team
  * @brief   This file contains all the functions prototypes for the
  *          ais25ba_reg.c driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef AIS25BA_REGS_H
#define AIS25BA_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <math.h>

/** @addtogroup AIS25BA
  * @{
  *
  */

/** @defgroup  Endianness definitions
  * @{
  *
  */

#ifndef DRV_BYTE_ORDER
#ifndef __BYTE_ORDER__

#define DRV_LITTLE_ENDIAN 1234
#define DRV_BIG_ENDIAN    4321

/** if _BYTE_ORDER is not defined, choose the endianness of your architecture
  * by uncommenting the define which fits your platform endianness
  */
//#define DRV_BYTE_ORDER    DRV_BIG_ENDIAN
#define DRV_BYTE_ORDER    DRV_LITTLE_ENDIAN

#else /* defined __BYTE_ORDER__ */

#define DRV_LITTLE_ENDIAN  __ORDER_LITTLE_ENDIAN__
#define DRV_BIG_ENDIAN     __ORDER_BIG_ENDIAN__
#define DRV_BYTE_ORDER     __BYTE_ORDER__

#endif /* __BYTE_ORDER__*/
#endif /* DRV_BYTE_ORDER */

/**
  * @}
  *
  */

/** @defgroup STMicroelectronics sensors common types
  * @{
  *
  */

#ifndef MEMS_SHARED_TYPES
#define MEMS_SHARED_TYPES

typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t bit0       : 1;
  uint8_t bit1       : 1;
  uint8_t bit2       : 1;
  uint8_t bit3       : 1;
  uint8_t bit4       : 1;
  uint8_t bit5       : 1;
  uint8_t bit6       : 1;
  uint8_t bit7       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t bit7       : 1;
  uint8_t bit6       : 1;
  uint8_t bit5       : 1;
  uint8_t bit4       : 1;
  uint8_t bit3       : 1;
  uint8_t bit2       : 1;
  uint8_t bit1       : 1;
  uint8_t bit0       : 1;
#endif /* DRV_BYTE_ORDER */
} bitwise_t;

#define PROPERTY_DISABLE                (0U)
#define PROPERTY_ENABLE                 (1U)

/** @addtogroup  Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

typedef int32_t (*stmdev_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*stmdev_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef void (*stmdev_mdelay_ptr)(uint32_t millisec);

typedef struct
{
  /** Component mandatory fields **/
  stmdev_write_ptr  write_reg;
  stmdev_read_ptr   read_reg;
  /** Component optional fields **/
  stmdev_mdelay_ptr   mdelay;
  /** Customizable optional pointer **/
  void *handle;

  /** private data **/
  void *priv_data;
} stmdev_ctx_t;

/**
  * @}
  *
  */

#endif /* MEMS_SHARED_TYPES */

#ifndef MEMS_UCF_SHARED_TYPES
#define MEMS_UCF_SHARED_TYPES

/** @defgroup    Generic address-data structure definition
  * @brief       This structure is useful to load a predefined configuration
  *              of a sensor.
  *              You can create a sensor configuration by your own or using
  *              Unico / Unicleo tools available on STMicroelectronics
  *              web site.
  *
  * @{
  *
  */

typedef struct
{
  uint8_t address;
  uint8_t data;
} ucf_line_t;

/**
  * @}
  *
  */

#endif /* MEMS_UCF_SHARED_TYPES */

/**
  * @}
  *
  */

/** @defgroup AIS25BA_Infos
  * @{
  *
  */

/** I2C Device Address 8 bit format. SA0 = not(I2C_A0 pin) **/
#define AIS25BA_I2C_ADD_L                    0x33
#define AIS25BA_I2C_ADD_H                    0x31

/** Device Identification (Who am I) **/
#define AIS25BA_ID                           0x20

/**
  * @}
  *
  */

#define AIS25BA_TEST_REG                   0x0BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01    : 3;
  uint8_t st             : 1;
  uint8_t not_used_02    : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02    : 4;
  uint8_t st             : 1;
  uint8_t not_used_01    : 3;
#endif /* DRV_BYTE_ORDER */
} ais25ba_test_reg_t;

#define AIS25BA_WHO_AM_I                   0x0FU

#define AIS25BA_TDM_CMAX_H                 0x24U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tdm_cmax                      : 4;
  uint8_t not_used_01                   : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01                   : 4;
  uint8_t tdm_cmax                      : 4;
#endif /* DRV_BYTE_ORDER */
} ais25ba_tdm_cmax_h_t;

#define AIS25BA_TDM_CMAX_L                 0x25U
typedef struct
{
  uint8_t tdm_cmax       : 8;
} ais25ba_tdm_cmax_l_t;

#define AIS25BA_CTRL_REG_1                 0x26U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01    : 5;
  uint8_t pd             : 1;
  uint8_t not_used_02    : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02    : 2;
  uint8_t pd             : 1;
  uint8_t not_used_01    : 5;
#endif /* DRV_BYTE_ORDER */
} ais25ba_ctrl_reg_t;

#define AIS25BA_TDM_CTRL_REG               0x2EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01    : 1;
  uint8_t wclk_fq        : 2;
  uint8_t not_used_02    : 1;
  uint8_t mapping        : 1;
  uint8_t data_valid     : 1;
  uint8_t delayed        : 1;
  uint8_t tdm_pd         : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tdm_pd         : 1;
  uint8_t delayed        : 1;
  uint8_t data_valid     : 1;
  uint8_t mapping        : 1;
  uint8_t not_used_02    : 1;
  uint8_t wclk_fq        : 2;
  uint8_t not_used_01    : 1;
#endif /* DRV_BYTE_ORDER */
} ais25ba_tdm_ctrl_reg_t;

#define AIS25BA_CTRL_REG_2                 0x2FU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t odr_auto_en    : 1;
  uint8_t not_used_01    : 7;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01    : 7;
  uint8_t odr_auto_en    : 1;
#endif /* DRV_BYTE_ORDER */
} ais25ba_axes_ctrl_reg_t;

/**
  * @defgroup AIS25BA_Register_Union
  * @brief    This union group all the registers that has a bitfield
  *           description.
  *           This union is useful but not need by the driver.
  *
  *           REMOVING this union you are compliant with:
  *           MISRA-C 2012 [Rule 19.2] -> " Union are not allowed "
  *
  * @{
  *
  */
typedef union
{
  ais25ba_test_reg_t           test_reg;
  ais25ba_tdm_cmax_h_t         tdm_cmax_h;
  ais25ba_tdm_cmax_l_t         tdm_cmax_l;
  ais25ba_ctrl_reg_t           ctrl_reg;
  ais25ba_tdm_ctrl_reg_t       tdm_ctrl_reg;
  ais25ba_axes_ctrl_reg_t      axes_ctrl_reg;
  bitwise_t                    bitwise;
  uint8_t                      byte;
} ais25ba_reg_t;

/**
  * @}
  *
  */

#ifndef __weak
#define __weak __attribute__((weak))
#endif /* __weak */

/*
 * These are the basic platform dependent I/O routines to read
 * and write device registers connected on a standard bus.
 * The driver keeps offering a default implementation based on function
 * pointers to read/write routines for backward compatibility.
 * The __weak directive allows the final application to overwrite
 * them with a custom implementation.
 */

int32_t ais25ba_read_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                         uint8_t *data,
                         uint16_t len);
int32_t ais25ba_write_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                          uint8_t *data,
                          uint16_t len);

extern float_t ais25ba_from_raw_to_mg(int16_t lsb);

typedef struct
{
  uint8_t id;
} ais25ba_id_t;
int32_t ais25ba_id_get(const stmdev_ctx_t *ctx, ais25ba_id_t *val);

typedef struct
{
  struct
  {
    uint8_t en       : 1; /* TDM interface 1=on / 0=off) */
    uint8_t clk_pol  : 1; /* data valid on 0=rise/1=falling edge of BCLK */
    uint8_t clk_edge : 1; /* data on 0=first / 1=second valid edge of BCLK */
    uint8_t mapping  : 1; /* xl data in 0=slot0-1-2 / 1=slot4-5-6 */
    uint16_t cmax    : 1; /* BCLK in a WCLK (unused if odr=_XL_HW_SEL) */
  } tdm;
} ais25ba_bus_mode_t;
int32_t ais25ba_bus_mode_set(const stmdev_ctx_t *ctx,
                             ais25ba_bus_mode_t *val);
int32_t ais25ba_bus_mode_get(const stmdev_ctx_t *ctx,
                             ais25ba_bus_mode_t *val);

typedef struct
{
  struct
  {
    enum
    {
      AIS25BA_XL_OFF    = 0x01, /* in power down */
      AIS25BA_XL_8kHz   = 0x00, /* sampling rate equal to 8 kHz */
      AIS25BA_XL_16kHz  = 0x02, /* sampling rate equal to 16 kHz */
      AIS25BA_XL_24kHz  = 0x04, /* sampling rate equal to 24 kHz */
      AIS25BA_XL_HW_SEL = 0x10, /* ratio between the MCLK and WCLK */
    } odr;
  } xl;
} ais25ba_md_t;
int32_t ais25ba_mode_set(const stmdev_ctx_t *ctx, ais25ba_md_t *val);
int32_t ais25ba_mode_get(const stmdev_ctx_t *ctx, ais25ba_md_t *val);

typedef struct
{
  struct
  {
    float_t mg[3];
    int16_t raw[3];
  } xl;
} ais25ba_data_t;
int32_t ais25ba_data_get(uint16_t *tdm_stream, ais25ba_bus_mode_t *md,
                         ais25ba_data_t *data);

int32_t ais25ba_self_test_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t ais25ba_self_test_get(const stmdev_ctx_t *ctx, uint8_t *val);

/**
  * @}
  *
  */

#ifdef __cplusplus
}
#endif

#endif /*AIS25BA_DRIVER_H */
