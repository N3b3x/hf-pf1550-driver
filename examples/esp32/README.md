# ESP32 PF1550 examples

Build and flash via the shared ESP-IDF project tools submodule:

```bash
git submodule update --init --recursive
./scripts/build_app.sh pf1550_esp32c6_probe Debug
./scripts/flash_app.sh pf1550_esp32c6_probe Debug
```

## Wiring (lab / eval)

| Signal | ESP32-C6 default |
|--------|------------------|
| SDA | GPIO4 |
| SCL | GPIO5 |
| PMIC I2C | 0x08 |

Without a PF1550 on the bus the probe app logs a warning and idles — suitable for CI.

## Apps

| App | Purpose |
|-----|---------|
| `pf1550_esp32c6_probe` | Read DEVICE_ID, optional profile apply |
| `pf1550_esp32c6_register_dump` | Dump regulator / status registers |
