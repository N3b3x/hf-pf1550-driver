/**
 * @file pf1550.ipp
 * @brief PF1550 driver template implementation
 * @copyright Copyright (c) 2024-2026 HardFOC. All rights reserved.
 */
#pragma once

namespace pf1550 {

template <typename BusType>
PF1550<BusType>::PF1550(BusType* bus, uint8_t address) noexcept
    : bus_(bus), address_(address), initialized_(false), error_flags_(0) {}

template <typename BusType>
bool PF1550<BusType>::writeReg8(uint8_t reg, uint8_t value) noexcept {
  if (bus_ == nullptr) {
    setError(Error::InvalidParam);
    return false;
  }
  const uint8_t data = value;
  if (!bus_->Write(address_, reg, &data, 1)) {
    setError(Error::I2cWrite);
    return false;
  }
  return true;
}

template <typename BusType>
bool PF1550<BusType>::readReg8(uint8_t reg, uint8_t& value) noexcept {
  if (bus_ == nullptr) {
    setError(Error::InvalidParam);
    return false;
  }
  if (!bus_->Read(address_, reg, &value, 1)) {
    setError(Error::I2cRead);
    return false;
  }
  return true;
}

template <typename BusType>
bool PF1550<BusType>::EnsureInitialized() noexcept {
  if (initialized_) {
    return true;
  }
  if (bus_ == nullptr || !bus_->EnsureInitialized()) {
    setError(Error::NotInitialized);
    return false;
  }
  if (!VerifyDevice()) {
    return false;
  }
  initialized_ = true;
  ClearErrorFlags(static_cast<uint16_t>(Error::NotInitialized));
  return true;
}

template <typename BusType>
bool PF1550<BusType>::ReadDeviceId(uint8_t& id) noexcept {
  if (!readReg8(static_cast<uint8_t>(Register::DeviceId), id)) {
    return false;
  }
  return true;
}

template <typename BusType>
bool PF1550<BusType>::VerifyDevice() noexcept {
  uint8_t id = 0;
  if (!ReadDeviceId(id)) {
    setError(Error::DeviceNotFound);
    return false;
  }
  if (id != kExpectedDeviceId) {
    setError(Error::WrongDeviceId);
    return false;
  }
  return true;
}

template <typename BusType>
bool PF1550<BusType>::ReadRegister(Register reg, uint8_t& value) noexcept {
  return readReg8(static_cast<uint8_t>(reg), value);
}

template <typename BusType>
bool PF1550<BusType>::WriteRegister(Register reg, uint8_t value) noexcept {
  return writeReg8(static_cast<uint8_t>(reg), value);
}

template <typename BusType>
bool PF1550<BusType>::ApplyProfile(std::span<const profiles::RegisterWrite> profile) noexcept {
  if (bus_ == nullptr || !bus_->EnsureInitialized()) {
    setError(Error::NotInitialized);
    return false;
  }

  for (const auto& entry : profile) {
    if (!writeReg8(entry.reg, entry.value)) {
      setError(Error::ProfileApply);
      return false;
    }
    if (entry.delay_us > 0) {
      bus_->DelayUs(entry.delay_us);
    }
  }
  return true;
}

template <typename BusType>
bool PF1550<BusType>::ApplyPortentaH7DefaultProfile() noexcept {
  return ApplyProfile(profiles::kPortentaH7Default);
}

template <typename BusType>
bool PF1550<BusType>::SetPowerMode(PowerMode mode) noexcept {
  if (bus_ == nullptr) {
    setError(Error::InvalidParam);
    return false;
  }
  switch (mode) {
  case PowerMode::Run:
    bus_->GpioSetInactive(CtrlPin::Standby);
    break;
  case PowerMode::Standby:
    bus_->GpioSetActive(CtrlPin::Standby);
    break;
  default:
    setError(Error::InvalidParam);
    return false;
  }
  return true;
}

template <typename BusType>
bool PF1550<BusType>::SetUsbRails(bool vbus_en, bool otg_en) noexcept {
  if (bus_ == nullptr) {
    setError(Error::InvalidParam);
    return false;
  }
  bus_->GpioSet(CtrlPin::UsbVbusEn, vbus_en ? GpioSignal::Active : GpioSignal::Inactive);
  bus_->GpioSet(CtrlPin::UsbOtgEn, otg_en ? GpioSignal::Active : GpioSignal::Inactive);
  return true;
}

template <typename BusType>
bool PF1550<BusType>::ReadPmicStatus(uint8_t& status) noexcept {
  return readReg8(static_cast<uint8_t>(Register::PmicStatus), status);
}

template <typename BusType>
bool PF1550<BusType>::ReadOtpByte(uint8_t otp_addr, uint8_t& value) noexcept {
  if (!writeReg8(OtpUnlockKeys::kKey1Reg, OtpUnlockKeys::kKey1Val) ||
      !writeReg8(OtpUnlockKeys::kKey2Reg, OtpUnlockKeys::kKey2Val) ||
      !writeReg8(OtpUnlockKeys::kKey3Reg, OtpUnlockKeys::kKey3Val)) {
    return false;
  }

  if (!writeReg8(static_cast<uint8_t>(Register::FmrAddr), otp_addr)) {
    return false;
  }
  bus_->DelayUs(2000);
  return readReg8(static_cast<uint8_t>(Register::FmrData), value);
}

template <typename BusType>
bool PF1550<BusType>::ReadOtpRegion(uint8_t* buffer, size_t len, uint8_t start) noexcept {
  if (buffer == nullptr || len == 0) {
    setError(Error::InvalidParam);
    return false;
  }
  for (size_t i = 0; i < len; ++i) {
    const uint8_t addr = static_cast<uint8_t>(start + i);
    if (addr >= OtpRegion::kEndExclusive) {
      setError(Error::InvalidParam);
      return false;
    }
    if (!ReadOtpByte(addr, buffer[i])) {
      return false;
    }
  }
  return true;
}

template <typename BusType>
bool PF1550<BusType>::SetSwVoltage(uint8_t sw_index, SwVoltageCode run_code) noexcept {
  Register volt_reg = Register::Sw1Volt;
  switch (sw_index) {
  case 1:
    volt_reg = Register::Sw1Volt;
    break;
  case 2:
    volt_reg = Register::Sw2Volt;
    break;
  case 3:
    volt_reg = Register::Sw3Volt;
    break;
  default:
    setError(Error::InvalidParam);
    return false;
  }
  return writeReg8(static_cast<uint8_t>(volt_reg), static_cast<uint8_t>(run_code));
}

template <typename BusType>
bool PF1550<BusType>::SetLdoVoltage(uint8_t ldo_index, LdoVoltageCode code) noexcept {
  Register volt_reg = Register::Ldo1Volt;
  switch (ldo_index) {
  case 1:
    volt_reg = Register::Ldo1Volt;
    break;
  case 2:
    volt_reg = Register::Ldo2Volt;
    break;
  case 3:
    volt_reg = Register::Ldo3Volt;
    break;
  default:
    setError(Error::InvalidParam);
    return false;
  }
  return writeReg8(static_cast<uint8_t>(volt_reg), static_cast<uint8_t>(code));
}

template <typename BusType>
bool PF1550<BusType>::SetVbusCurrentLimitMa(uint16_t limit_ma) noexcept {
  // PF1550 VBUS limit: value = (limit_ma / 50) << 3 per Portenta bootloader (1500 mA -> 0xA0)
  if (limit_ma == 0 || (limit_ma % 50) != 0) {
    setError(Error::InvalidParam);
    return false;
  }
  const uint8_t steps = static_cast<uint8_t>(limit_ma / 50U);
  const uint8_t value = static_cast<uint8_t>(steps << 3);
  return writeReg8(static_cast<uint8_t>(Register::VbusInCurrentLimit), value);
}

} // namespace pf1550
