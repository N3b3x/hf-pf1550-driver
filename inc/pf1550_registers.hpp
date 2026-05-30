/**
 * @file pf1550_registers.hpp
 * @brief NXP PF1550 family I2C register map and constants
 *
 * Covers MC34PF1550*, MC32PF1550*, and related OTP variants (e.g. MC34PF1550A0EP).
 * Register addresses follow NXP PF1550 datasheet (PF1550.pdf).
 *
 * @copyright Copyright (c) 2024-2026 HardFOC. All rights reserved.
 */
#pragma once

#include <cstdint>

namespace pf1550 {

/** @brief Default 7-bit I2C address (PMIC_I2C on Portenta H7). */
inline constexpr uint8_t kDefaultI2cAddress = 0x08;

/** @brief Expected DEVICE_ID register value (family identifier). */
inline constexpr uint8_t kExpectedDeviceId = 0x7C;

/**
 * @enum Register
 * @brief PF1550 I2C register addresses used by this driver.
 */
enum class Register : uint8_t {
  DeviceId = 0x00,

  Sw1Volt = 0x32,
  Sw1VoltDvs = 0x33,
  Sw1Volt2 = 0x34,
  Sw1Ctrl = 0x35,

  Sw2Volt = 0x38,
  Sw2VoltDvs = 0x39,
  Sw2Volt2 = 0x3A,
  Sw2Ctrl = 0x3B,

  Sw3Volt = 0x3E,
  Sw3VoltDvs = 0x3F,
  Sw3Volt2 = 0x40,
  Sw3Ctrl = 0x41,
  Sw3Ctrl1 = 0x42,

  Ldo1Volt = 0x4C,
  Ldo1Ctrl = 0x4D,
  Ldo2Volt = 0x4F,
  Ldo2Ctrl = 0x50,
  Ldo3Volt = 0x52,
  Ldo3Ctrl = 0x53,
  LdoMisc = 0x58,

  PmicStatus = 0x67,

  OtpKey1 = 0x6F,
  OtpRcReq = 0x6B,
  FmrAddr = 0xC4,
  FmrData = 0xC5,

  ChargerLedDuty = 0x9C,
  ChargerLedCtrl = 0x9E,
  OtpKey2 = 0x9F,
  TestRegKey3 = 0xDF,

  VbusInCurrentLimit = 0x94,
};

/**
 * @enum SwVoltageCode
 * @brief Common SW buck output voltage codes (RUN mode).
 *
 * Full table is in the PF1550 datasheet; these are the values used on Portenta H7.
 */
enum class SwVoltageCode : uint8_t {
  V2_5 = 0x05,
  V3_0 = 0x06,
  V3_1 = 0x0D,
  V3_3 = 0x07,
};

/**
 * @enum LdoVoltageCode
 * @brief Common LDO output voltage codes used on Portenta H7.
 */
enum class LdoVoltageCode : uint8_t {
  V1_0 = 0x05,
  V1_2 = 0x09,
  V1_8 = 0x00,
};

/** @brief OTP indirect read unlock sequence keys. */
struct OtpUnlockKeys {
  static constexpr uint8_t kKey1Reg = static_cast<uint8_t>(Register::OtpKey1);
  static constexpr uint8_t kKey1Val = 0x15;
  static constexpr uint8_t kKey2Reg = static_cast<uint8_t>(Register::OtpKey2);
  static constexpr uint8_t kKey2Val = 0x50;
  static constexpr uint8_t kKey3Reg = static_cast<uint8_t>(Register::TestRegKey3);
  static constexpr uint8_t kKey3Val = 0xAB;
};

/** @brief OTP memory indirect address range (via FMRADDR/FMRDATA). */
struct OtpRegion {
  static constexpr uint8_t kStart = 0x1C;
  static constexpr uint8_t kEndExclusive = 0x37;
};

} // namespace pf1550
