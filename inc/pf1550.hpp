/**
 * @file pf1550.hpp
 * @brief Hardware-agnostic driver for NXP PF1550 PMIC family
 *
 * Supports MC34PF1550*, MC32PF1550*, including unprogrammed OTP variant
 * MC34PF1550A0EP used on Arduino Portenta H7 and Synapse MCU domain.
 *
 * @copyright Copyright (c) 2024-2026 HardFOC. All rights reserved.
 */
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>

#include "pf1550_i2c_interface.hpp"
#include "pf1550_profiles.hpp"
#include "pf1550_registers.hpp"
#include "pf1550_version.h"

namespace pf1550 {

/**
 * @class PF1550
 * @brief CRTP-based PF1550 PMIC driver.
 * @tparam BusType Platform bus type inheriting pf1550::BusInterface<BusType>.
 */
template <typename BusType>
class PF1550 {
public:
  enum class Error : uint16_t {
    None = 0,
    I2cWrite = 1 << 0,
    I2cRead = 1 << 1,
    InvalidParam = 1 << 2,
    DeviceNotFound = 1 << 3,
    NotInitialized = 1 << 4,
    WrongDeviceId = 1 << 5,
    ProfileApply = 1 << 6,
  };

  PF1550(BusType* bus, uint8_t address = kDefaultI2cAddress) noexcept;

  bool EnsureInitialized() noexcept;
  bool IsInitialized() const noexcept { return initialized_; }

  uint8_t GetI2cAddress() const noexcept { return address_; }

  bool ReadDeviceId(uint8_t& id) noexcept;
  bool VerifyDevice() noexcept;

  bool ReadRegister(Register reg, uint8_t& value) noexcept;
  bool WriteRegister(Register reg, uint8_t value) noexcept;

  bool ApplyProfile(std::span<const profiles::RegisterWrite> profile) noexcept;
  bool ApplyPortentaH7DefaultProfile() noexcept;

  bool SetPowerMode(PowerMode mode) noexcept;
  bool SetUsbRails(bool vbus_en, bool otg_en) noexcept;

  bool ReadPmicStatus(uint8_t& status) noexcept;
  bool ReadOtpByte(uint8_t otp_addr, uint8_t& value) noexcept;
  bool ReadOtpRegion(uint8_t* buffer, size_t len, uint8_t start = OtpRegion::kStart) noexcept;

  bool SetSwVoltage(uint8_t sw_index, SwVoltageCode run_code) noexcept;
  bool SetLdoVoltage(uint8_t ldo_index, LdoVoltageCode code) noexcept;
  bool SetVbusCurrentLimitMa(uint16_t limit_ma) noexcept;

  uint16_t GetErrorFlags() const noexcept { return error_flags_; }
  void ClearErrorFlags(uint16_t mask = 0xFFFF) noexcept { error_flags_ &= static_cast<uint16_t>(~mask); }

  static constexpr const char* GetDriverVersion() noexcept { return HF_PF1550_VERSION; }

private:
  bool writeReg8(uint8_t reg, uint8_t value) noexcept;
  bool readReg8(uint8_t reg, uint8_t& value) noexcept;
  void setError(Error e) noexcept { error_flags_ |= static_cast<uint16_t>(e); }

  BusType* bus_;
  uint8_t address_;
  bool initialized_;
  uint16_t error_flags_;
};

} // namespace pf1550

#include "../src/pf1550.ipp"
