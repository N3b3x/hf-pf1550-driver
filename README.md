---
layout: default
title: "HardFOC PF1550 Driver"
description: "Header-only NXP PF1550 PMIC driver with ESP32-C6 examples and Portenta H7 profile"
nav_order: 1
permalink: /
---

# HF-PF1550 Driver

**NXP [PF1550](https://www.nxp.com/products/power-management/pmics/power-management-ics-pmic-for-high-performance-applications:PF1550) PMIC family — I2C power management for application processors**

[![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![License](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![CI](https://github.com/N3b3x/hf-pf1550-driver/actions/workflows/esp32-examples-build-ci.yml/badge.svg?branch=main)](https://github.com/N3b3x/hf-pf1550-driver/actions/workflows/esp32-examples-build-ci.yml)
[![Docs](https://img.shields.io/badge/docs-GitHub%20Pages-blue)](https://n3b3x.github.io/hf-pf1550-driver/)

## 📚 Table of Contents

1. [Overview](#-overview)
2. [Features](#-features)
3. [Quick Start](#-quick-start)
4. [Installation](#-installation)
5. [API Reference](#-api-reference)
6. [Examples](#-examples)
7. [Documentation](#-documentation)
8. [References](#-references)
9. [Contributing](#-contributing)
10. [License](#-license)

## 📦 Overview

> **📖 [Live documentation](https://n3b3x.github.io/hf-pf1550-driver/)** — guides, register extracts, Portenta profile, ESP32-C6 examples.

The **PF1550** is a multi-rail PMIC (3 bucks, 3 LDOs, charger, OTP) used on **Arduino Portenta H7** (`MC34PF1550A0EP`) and **Synapse** MCU domains. Bare CubeMX firmware does **not** configure it — this driver provides portable I2C control, board profiles, and hf-core HAL integration.

You implement a small **CRTP bus adapter** (`pf1550::BusInterface<YourBus>`) for I2C and optional strap GPIOs.

### 🔀 Chip compatibility

| Part | I2C | DEVICE_ID | OTP |
|------|-----|-----------|-----|
| MC34PF1550A0EP | 0x08 | 0x7C | Unprogrammed — full profile writes |
| MC34PF1550* | 0x08 | 0x7C | Factory OTP — some rails locked |
| MC32PF1550* | 0x08 | 0x7C | Same register map |

## ✨ Features

- ✅ **Header-only C++20** — `pf1550::PF1550<BusType>` with `.ipp` implementation
- ✅ **CRTP bus interface** — zero virtual overhead on I2C path
- ✅ **Portenta H7 profile** — `portenta_h7_default` from VFR / Synapse heritage
- ✅ **Register map** — curated headers + auto-generated datasheet Section 12 extract
- ✅ **OTP read helpers** — indirect FMRADDR/FMRDATA access
- ✅ **Strap pin hooks** — STANDBY, USB_VBUS_EN, USB_OTG_EN
- ✅ **CMake package** — `hf::pf1550`, ESP-IDF component wrapper
- ✅ **hf-core handler** — `Pf1550Handler` via `HF_CORE_ENABLE_PF1550`
- ✅ **ESP32-C6 examples** — CI-safe I2C probe without hardware
- ✅ **CI** — ESP32 matrix build, C++ lint, docs link check, YAML lint

## 🚀 Quick Start

```cpp
#include "pf1550.hpp"

struct MyBus : pf1550::BusInterface<MyBus> {
  bool EnsureInitialized() noexcept { /* init I2C */ return true; }
  bool Write(uint8_t a, uint8_t r, const uint8_t* d, size_t n) noexcept { /* ... */ }
  bool Read(uint8_t a, uint8_t r, uint8_t* d, size_t n) noexcept { /* ... */ }
};

MyBus bus;
pf1550::PF1550<MyBus> pmic(&bus);

if (pmic.EnsureInitialized()) {
  pmic.SetPowerMode(pf1550::PowerMode::Run);
  pmic.ApplyPortentaH7DefaultProfile();
}
```

See [Quick Start Guide](docs/quickstart.md) and [Portenta profile](docs/portenta-profile.md).

## 🔧 Installation

1. Clone with submodules (for ESP32 examples):
   ```bash
   git clone --recursive https://github.com/N3b3x/hf-pf1550-driver.git
   ```
2. CMake:
   ```cmake
   add_subdirectory(hf-pf1550-driver)
   target_link_libraries(my_app PRIVATE hf::pf1550)
   ```
3. Datasheet (local, gitignored PDF):
   ```bash
   ./scripts/fetch_datasheet.sh
   ./scripts/extract_register_reference.sh
   ```

Details: [docs/installation.md](docs/installation.md)

## 📖 API Reference

| Method | Description |
|--------|-------------|
| `EnsureInitialized()` | I2C + DEVICE_ID check (0x7C) |
| `ApplyPortentaH7DefaultProfile()` | Board init sequence |
| `ApplyProfile(span<RegisterWrite>)` | Custom register table |
| `SetPowerMode(Run \| Standby)` | STANDBY strap |
| `SetUsbRails(vbus, otg)` | USB enable straps |
| `ReadPmicStatus()` | Status reg 0x67 |
| `ReadOtpRegion()` | OTP indirect read |

Full API: [docs/api_reference.md](docs/api_reference.md)

## 📊 Examples

| Example | Target | Description |
|---------|--------|-------------|
| `pf1550_esp32c6_probe` | ESP32-C6 | DEVICE_ID + status |
| `pf1550_esp32c6_register_dump` | ESP32-C6 | Regulator register dump |

```bash
cd examples/esp32
./scripts/build_app.sh pf1550_esp32c6_probe Debug
```

## 📚 Documentation

| Guide | Description |
|-------|-------------|
| [Documentation home](docs/index.md) | Full TOC |
| [Installation](docs/installation.md) | CMake, ESP-IDF, hf-core |
| [Quick start](docs/quickstart.md) | Bus adapter + probe |
| [Chip reference](docs/chip-reference.md) | Parts and IDs |
| [Portenta profile](docs/portenta-profile.md) | Rails, straps, init table |
| [Hardware setup](docs/hardware_setup.md) | ESP32-C6 wiring |
| [Platform integration](docs/platform_integration.md) | Pf1550Handler |
| [Datasheet](docs/datasheet/README.md) | PDF fetch + readable extracts |
| [Troubleshooting](docs/troubleshooting.md) | OTP, power-cycle, USB |

## 🔗 References

| Resource | Link |
|----------|------|
| NXP PF1550 datasheet | [PF1550.pdf](https://www.nxp.com/docs/en/data-sheet/PF1550.pdf) |
| Portenta VFR reference | `I2C_PMIC.c` in pw-design reference tree |
| ESP-IDF I2C master | [ESP32-C6 I2C docs](https://docs.espressif.com/projects/esp-idf/en/stable/esp32c6/api-reference/peripherals/i2c.html) |

## 🤝 Contributing

Run `./scripts/verify_driver_scaffold.sh` before opening a PR. Hardware validation remains manual.

## 📄 License

**GPL-3.0** — see [LICENSE](LICENSE).
