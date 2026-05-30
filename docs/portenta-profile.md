---
layout: default
title: "Portenta H7 profile"
nav_order: 5
parent: "📚 Documentation"
permalink: /docs/portenta-profile/
---

# Portenta H7 / Synapse `portenta_h7_default` profile

## Rail assignment (MCU domain)

| Rail | Voltage | Role |
|------|---------|------|
| LDO1 | 1.0 V | MCU core / analog |
| LDO2 | 1.8 V | I/O / peripherals |
| LDO3 | 1.2 V | DDR / memory I/O |
| SW1 | 3.3 V | MCU VCAP / digital |
| SW2 | 3.3 V | Board 3.3 V |
| SW3 | 3.1 V (OTP on programmed parts) | WiFi / high-current 3.3 V domain |

## GPIO straps (STM32H7 CM7)

| Signal | Pin | Boot value |
|--------|-----|------------|
| PMIC_STANDBY | PJ0 | LOW = RUN |
| USB_VBUS_EN | PJ4 | HIGH for USB-C VBUS |
| USB_OTG_EN | PJ6 | HIGH for OTG HS |
| PMIC_INT | PK0 | Input (optional) |

## I2C

- **Bus:** I2C1, PB6/PB7
- **Address:** 0x08
- **Speed:** up to 1 MHz (Fast Mode Plus) on Portenta

## Init sequence

Use `pf1550::profiles::kPortentaH7Default` or `PF1550::ApplyPortentaH7DefaultProfile()`.

Register `0x50` (LDO2_CTRL commit) is written **last**. Some SW3 voltage registers may be OTP-locked on factory-programmed parts.

## Important behavior

1. **PMIC state survives MCU reset** — only full power cycle resets PF1550.
2. **First init after power-up matters** — voltage changes may not take effect on subsequent soft resets.
3. **CubeMX does not configure the PMIC** — bare-metal firmware must call profile init explicitly.

## VBUS / charger extras in profile

- VBUS input limit: 1500 mA (reg 0x94 = 0xA0)
- SW3 current limit: 2 A (reg 0x42 = 0x02)
- Charger LED disabled (0x9C, 0x9E)
