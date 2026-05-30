---
layout: default
title: "📖 API reference"
nav_order: 8
parent: "📚 Documentation"
permalink: /docs/api_reference/
---

# API reference

## Namespace

All symbols are in namespace `pf1550`.

## Class `PF1550<BusType>`

Header: `inc/pf1550.hpp` · Implementation: `src/pf1550.ipp`

### Construction

```cpp
PF1550(BusType* bus, uint8_t address = kDefaultI2cAddress);
```

### Lifecycle

| Method | Returns | Description |
|--------|---------|-------------|
| `EnsureInitialized()` | `bool` | Probe DEVICE_ID (0x7C) |
| `IsInitialized()` | `bool` | Cached init state |
| `GetI2cAddress()` | `uint8_t` | 7-bit address |

### Identification

| Method | Description |
|--------|-------------|
| `ReadDeviceId(uint8_t& id)` | Read reg 0x00 |
| `VerifyDevice()` | Check id == 0x7C |

### Registers

| Method | Description |
|--------|-------------|
| `ReadRegister(Register reg, uint8_t& value)` | Single-byte read |
| `WriteRegister(Register reg, uint8_t value)` | Single-byte write |

### Profiles

| Method | Description |
|--------|-------------|
| `ApplyProfile(span<RegisterWrite>)` | Generic init table |
| `ApplyPortentaH7DefaultProfile()` | `profiles::kPortentaH7Default` |

### Power / USB

| Method | Description |
|--------|-------------|
| `SetPowerMode(PowerMode)` | STANDBY strap via `GpioSet` |
| `SetUsbRails(vbus_en, otg_en)` | USB_VBUS_EN / USB_OTG_EN |

### Diagnostics

| Method | Description |
|--------|-------------|
| `ReadPmicStatus(uint8_t&)` | Reg 0x67 |
| `ReadOtpByte(addr, value)` | Indirect OTP read |
| `ReadOtpRegion(buf, len, start)` | Bulk OTP read |
| `SetSwVoltage(index, code)` | SW1–3 RUN voltage |
| `SetLdoVoltage(index, code)` | LDO1–3 voltage |
| `SetVbusCurrentLimitMa(mA)` | Reg 0x94 encoding |

### Errors

Bitmask enum `PF1550::Error`. Use `GetErrorFlags()` / `ClearErrorFlags()`.

## Constants

| Name | Value |
|------|-------|
| `kDefaultI2cAddress` | 0x08 |
| `kExpectedDeviceId` | 0x7C |

## Version

`PF1550<BusType>::GetDriverVersion()` → CMake-generated string.
