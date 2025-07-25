/**
  ******************************************************************************
  * @file    ais25ba_reg.c
  * @author  Sensors Software Solution Team
  * @brief   AIS25BA driver file
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

#include "ais25ba_reg.h"

/**
  * @defgroup  AIS25BA
  * @brief     This file provides a set of functions needed to drive the
  *            ais25ba enhanced inertial module.
  * @{
  *
  */

/**
  * @defgroup  AIS25BA_Interfaces_Functions
  * @brief     This section provide a set of functions used to read and
  *            write a generic register of the device.
  *            MANDATORY: return 0 -> no Error.
  * @{
  *
  */

/**
  * @brief  Read generic device register
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  reg   first register address to read.
  * @param  data  buffer for data read.(ptr)
  * @param  len   number of consecutive register to read.
  * @retval       interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t __weak ais25ba_read_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                                uint8_t *data,
                                uint16_t len)
{
  int32_t ret;

  if (ctx == NULL) return -1;

  ret = ctx->read_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  reg   first register address to write.
  * @param  data  the buffer contains data to be written.(ptr)
  * @param  len   number of consecutive register to write.
  * @retval       interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t __weak ais25ba_write_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                                 uint8_t *data,
                                 uint16_t len)
{
  int32_t ret;

  if (ctx == NULL) return -1;

  ret = ctx->write_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  AIS25BA_Private_functions
  * @brief     Section collect all the utility functions needed by APIs.
  * @{
  *
  */

static void bytecpy(uint8_t *target, uint8_t *source)
{
  if ((target != NULL) && (source != NULL))
  {
    *target = *source;
  }
}

/**
  * @}
  *
  */

/**
  * @defgroup  AIS25BA_Sensitivity
  * @brief     These functions convert raw-data into engineering units.
  * @{
  *
  */
float_t ais25ba_from_raw_to_mg(int16_t lsb)
{
  return ((float_t)lsb) * 0.122f;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Basic configuration
  * @brief     This section groups all the functions concerning
  *            device basic configuration.
  * @{
  *
  */

/**
  * @brief  Device "Who am I".[get]
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  val   ID values read from the I2C interface.
  *
  * @retval       interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t ais25ba_id_get(const stmdev_ctx_t *ctx, ais25ba_id_t *val)
{
  int32_t ret = 0;

  if (ctx != NULL)
  {
    ret = ais25ba_read_reg(ctx, AIS25BA_WHO_AM_I, (uint8_t *) & (val->id), 1);
  }

  return ret;
}

/**
  * @brief  Configures the bus operating mode.[set]
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  val   configures the TDM bus operating mode.(ptr)
  *
  * @retval       interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t ais25ba_bus_mode_set(const stmdev_ctx_t *ctx,
                             ais25ba_bus_mode_t *val)
{
  ais25ba_tdm_ctrl_reg_t tdm_ctrl_reg;
  ais25ba_tdm_cmax_h_t tdm_cmax_h;
  ais25ba_tdm_cmax_l_t tdm_cmax_l;
  uint8_t reg[2];
  int32_t ret;

  ret = ais25ba_read_reg(ctx, AIS25BA_TDM_CTRL_REG,
                         (uint8_t *)&tdm_ctrl_reg, 1);

  if (ret == 0)
  {
    ret = ais25ba_read_reg(ctx, AIS25BA_TDM_CMAX_H, reg, 2);
    bytecpy((uint8_t *)&tdm_cmax_h, &reg[0]);
    bytecpy((uint8_t *)&tdm_cmax_l, &reg[1]);
    tdm_ctrl_reg.tdm_pd = ~val->tdm.en;
    tdm_ctrl_reg.data_valid = val->tdm.clk_pol;
    tdm_ctrl_reg.delayed = val->tdm.clk_edge;
    tdm_ctrl_reg.wclk_fq = val->tdm.mapping;
    tdm_cmax_h.tdm_cmax = (uint8_t)(val->tdm.cmax / 256U);
    tdm_cmax_l.tdm_cmax = (uint8_t)(val->tdm.cmax - tdm_cmax_h.tdm_cmax);
  }

  if (ret == 0)
  {
    ret = ais25ba_write_reg(ctx, AIS25BA_TDM_CTRL_REG,
                            (uint8_t *)&tdm_ctrl_reg, 1);
  }

  if (ret == 0)
  {
    bytecpy(&reg[0], (uint8_t *)&tdm_cmax_h);
    bytecpy(&reg[1], (uint8_t *)&tdm_cmax_l);
    ret = ais25ba_write_reg(ctx, AIS25BA_TDM_CMAX_H, reg, 2);
  }

  return ret;
}

/**
  * @brief  Get the bus operating mode.[get]
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  val   configures the TDM bus operating mode.(ptr)
  *
  * @retval       interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t ais25ba_bus_mode_get(const stmdev_ctx_t *ctx,
                             ais25ba_bus_mode_t *val)
{
  ais25ba_tdm_ctrl_reg_t tdm_ctrl_reg;
  ais25ba_tdm_cmax_h_t tdm_cmax_h;
  ais25ba_tdm_cmax_l_t tdm_cmax_l;
  uint8_t reg[2];
  int32_t ret;

  ret = ais25ba_read_reg(ctx, AIS25BA_TDM_CTRL_REG,
                         (uint8_t *)&tdm_ctrl_reg, 1);

  if (ret == 0)
  {
    ret = ais25ba_read_reg(ctx, AIS25BA_TDM_CMAX_H, reg, 2);
    bytecpy((uint8_t *)&tdm_cmax_h, &reg[0]);
    bytecpy((uint8_t *)&tdm_cmax_l, &reg[1]);
  }

  val->tdm.en = ~tdm_ctrl_reg.tdm_pd;
  val->tdm.clk_pol = tdm_ctrl_reg.data_valid;
  val->tdm.clk_edge = tdm_ctrl_reg.delayed;
  val->tdm.mapping = tdm_ctrl_reg.wclk_fq;
  val->tdm.cmax = tdm_cmax_h.tdm_cmax * 256U;
  val->tdm.cmax += tdm_cmax_l.tdm_cmax;

  return ret;
}

/**
  * @brief  Sensor conversion parameters selection.[set]
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  val   set the sensor conversion parameters by checking
  *               the constraints of the device.(ptr)
  *
  * @retval       interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t ais25ba_mode_set(const stmdev_ctx_t *ctx, ais25ba_md_t *val)
{
  ais25ba_axes_ctrl_reg_t axes_ctrl_reg;
  ais25ba_tdm_ctrl_reg_t tdm_ctrl_reg;
  ais25ba_ctrl_reg_t ctrl_reg;
  uint8_t reg[2];
  int32_t ret;

  ret = ais25ba_read_reg(ctx, AIS25BA_CTRL_REG_1, (uint8_t *)&ctrl_reg, 1);

  if (ret == 0)
  {
    ret = ais25ba_read_reg(ctx, AIS25BA_TDM_CTRL_REG, reg, 2);
    bytecpy((uint8_t *)&tdm_ctrl_reg, &reg[0]);
    bytecpy((uint8_t *)&axes_ctrl_reg,  &reg[1]);
  }

  ctrl_reg.pd = (uint8_t)val->xl.odr & 0x01U;
  tdm_ctrl_reg.wclk_fq = ((uint8_t)val->xl.odr & 0x06U) >> 1;
  axes_ctrl_reg.odr_auto_en = ((uint8_t)val->xl.odr & 0x10U) >> 4;

  if (ret == 0)
  {
    ret = ais25ba_write_reg(ctx, AIS25BA_CTRL_REG_1, (uint8_t *)&ctrl_reg, 1);
  }

  /* writing checked configuration */
  bytecpy(&reg[0], (uint8_t *)&tdm_ctrl_reg);
  bytecpy(&reg[1], (uint8_t *)&axes_ctrl_reg);

  if (ret == 0)
  {
    ret = ais25ba_write_reg(ctx, AIS25BA_TDM_CTRL_REG, (uint8_t *)&reg,
                            2);
  }

  return ret;
}

/**
  * @brief  Sensor conversion parameters selection.[get]
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  val   get the sensor conversion parameters.(ptr)
  *
  * @retval       interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t ais25ba_mode_get(const stmdev_ctx_t *ctx, ais25ba_md_t *val)
{
  ais25ba_axes_ctrl_reg_t axes_ctrl_reg;
  ais25ba_tdm_ctrl_reg_t tdm_ctrl_reg;
  ais25ba_ctrl_reg_t ctrl_reg;
  uint8_t reg[2];
  int32_t ret;

  ret = ais25ba_read_reg(ctx, AIS25BA_CTRL_REG_1, (uint8_t *)&ctrl_reg, 1);

  if (ret == 0)
  {
    ret = ais25ba_read_reg(ctx, AIS25BA_TDM_CTRL_REG, reg, 2);
    bytecpy((uint8_t *)&tdm_ctrl_reg, &reg[0]);
    bytecpy((uint8_t *)&axes_ctrl_reg,  &reg[1]);
  }

  switch ((axes_ctrl_reg.odr_auto_en << 4) | (tdm_ctrl_reg.wclk_fq <<
                                              1) |
          ctrl_reg.pd)
  {
    case AIS25BA_XL_OFF:
      val->xl.odr = AIS25BA_XL_OFF;
      break;

    case AIS25BA_XL_8kHz:
      val->xl.odr = AIS25BA_XL_8kHz;
      break;

    case AIS25BA_XL_16kHz:
      val->xl.odr = AIS25BA_XL_16kHz;
      break;

    case AIS25BA_XL_24kHz:
      val->xl.odr = AIS25BA_XL_24kHz;
      break;

    case AIS25BA_XL_HW_SEL:
      val->xl.odr = AIS25BA_XL_HW_SEL;
      break;

    default:
      val->xl.odr = AIS25BA_XL_OFF;
      break;
  }

  return ret;
}

/**
  * @brief  Read data in engineering unit.[get]
  *
  * @param  tdm_stream  data stream from TDM interface.(ptr)
  * @param  md          the TDM interface configuration.(ptr)
  * @param  data        data read by the sensor.(ptr)
  *
  * @retval             interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t ais25ba_data_get(uint16_t *tdm_stream, ais25ba_bus_mode_t *md,
                         ais25ba_data_t *data)
{
  uint8_t offset;
  uint8_t i;

  if (md->tdm.mapping == PROPERTY_DISABLE)
  {
    offset = 0; /* slot0-1-2 */
  }

  else
  {
    offset = 4; /* slot4-5-6 */
  }

  for (i = 0U; i < 3U; i++)
  {
    data->xl.raw[i] = (int16_t) tdm_stream[i + offset];
    data->xl.mg[i] = ais25ba_from_raw_to_mg(data->xl.raw[i]);
  }

  return 0;
}

/**
  * @brief  Linear acceleration sensor self-test enable.[set]
  *
  * @param  ctx      read / write interface definitions.(ptr)
  * @param  val      enable/ disable selftest
  *
  * @retval          interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t ais25ba_self_test_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  ais25ba_test_reg_t test_reg;
  int32_t ret;

  ret = ais25ba_read_reg(ctx, AIS25BA_TEST_REG, (uint8_t *)&test_reg, 1);

  if (ret == 0)
  {
    test_reg.st = val;
    ret = ais25ba_write_reg(ctx, AIS25BA_TEST_REG, (uint8_t *)&test_reg, 1);
  }

  return ret;
}

/**
  * @brief  Linear acceleration sensor self-test enable.[get]
  *
  * @param  ctx      read / write interface definitions.(ptr)
  * @param  val      enable/ disable selftest.(ptr)
  *
  * @retval          interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t ais25ba_self_test_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  ais25ba_test_reg_t test_reg;
  int32_t ret;

  ret = ais25ba_read_reg(ctx, AIS25BA_TEST_REG, (uint8_t *)&test_reg, 1);
  *val = test_reg.st;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @}
  *
  */
