---
layout: default
title: "🔗 Platform integration"
nav_order: 7
parent: "📚 Documentation"
permalink: /docs/platform_integration/
---

# Platform integration — hf-core Pf1550Handler

The handler bridges **HardFOC `BaseI2c`** and optional **`BaseGpio`** strap pins to `pf1550::PF1550<HalPf1550Comm>`.

## Location

```
hf-core/handlers/pf1550/
  Pf1550Handler.h
  Pf1550Handler.cpp
```

Enable with `-DHF_CORE_ENABLE_PF1550=ON`.

## Construction

```cpp
#include "Pf1550Handler.h"

Pf1550Handler pmic(
    pmic_i2c,           // BaseI2c @ 0x08
    &standby_gpio,      // PJ0 — optional
    &usb_vbus_en_gpio,  // PJ4
    &usb_otg_en_gpio    // PJ6
);

pmic.SetPowerMode(pf1550::PowerMode::Run);
pmic.SetUsbRails(true, true);
pmic.ApplyPortentaH7Profile();
```

## Thread safety

All public methods use `RtosMutex`. I2C transactions are additionally serialized in `HalPf1550Comm`.

## Advanced access

```cpp
if (auto* drv = pmic.GetDriver()) {
  drv->ReadOtpByte(0x1C, value);
}
```

See hf-core `docs/handlers/pf1550_handler.md` when integrated in the monorepo.
