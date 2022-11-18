# CY8CPROTO-064B0S1-BLE BSP

## Overview

The PSoC™ 64 Secure Boot BLE Prototyping Kit (CY8CPROTO-064B0S1-BLE) is a low-cost hardware platform that enables design and debug of PSoC™ 64 MCUs. This kit is designed with a snap-away form-factor, allowing users to separate the KitProg (on-board programmer and debugger) from the target board and use independently.

![](docs/html/board.png)

To use code from the BSP, simply include a reference to `cybsp.h`.

## Features

### Kit Features:

* BLE 5.0 certified CYBLE-4xxxx-xx EZ-BLE module with onboard crystal oscillators, trace antenna, passive components and PSoC™ 64 MCU
* Up to 36 GPIOs in a 14x18.5x2 mm package
* Supports digital programmable logic, capacitive-sensing with CAPSENSE, a PDM-PCM digital microphone interface, a Quad-SPI interface, high-performance analog-to-digital converter (ADC), low-power comparators, and standard communication and timing peripherals.

### Kit Contents:

* 2x PSoC™ 64 BLE Prototyping Board
* USB Type-A to Micro-B cable
* Quick Start Guide

## BSP Configuration

The BSP has a few hooks that allow its behavior to be configured. Some of these items are enabled by default while others must be explicitly enabled. Items enabled by default are specified in the CY8CPROTO-064B0S1-BLE.mk file. The items that are enabled can be changed by creating a custom BSP or by editing the application makefile.

Components:
* Device specific category reference (e.g.: CAT1) - This component, enabled by default, pulls in any device specific code for this board.
* BSP_DESIGN_MODUS - This component, enabled by default, causes the Configurator generated code for this specific BSP to be included. This should not be used at the same time as the CUSTOM_DESIGN_MODUS component.
* CUSTOM_DESIGN_MODUS - This component, disabled by default, causes the Configurator generated code from the application to be included. This assumes that the application provides configurator generated code. This should not be used at the same time as the BSP_DESIGN_MODUS component.

Defines:
* CYBSP_WIFI_CAPABLE - This define, disabled by default, causes the BSP to initialize the interface to an onboard wireless chip if it has one.
* CY_USING_HAL - This define, enabled by default, specifies that the HAL is intended to be used by the application. This will cause the BSP to include the applicable header file and to initialize the system level drivers.
* CYBSP_CUSTOM_SYSCLK_PM_CALLBACK - This define, disabled by default, causes the BSP to skip registering its default SysClk Power Management callback, if any, and instead to invoke the application-defined function `cybsp_register_custom_sysclk_pm_callback` to register an application-specific callback.

### Clock Configuration

| Clock    | Source    | Output Frequency |
|----------|-----------|------------------|
| FLL      | IMO       | 100.0 MHz        |
| PLL      | IMO       | 48.0 MHz         |
| CLK_HF0  | CLK_PATH0 | 100 MHz          |

### Power Configuration

* System Active Power Mode: LP
* System Idle Power Mode: Deep Sleep
* VDDA Voltage: 3300 mV
* VDDD Voltage: 3300 mV

See the [BSP Setttings][settings] for additional board specific configuration settings.

## API Reference Manual

The CY8CPROTO-064B0S1-BLE Board Support Package provides a set of APIs to configure, initialize and use the board resources.

See the [BSP API Reference Manual][api] for the complete list of the provided interfaces.

## More information
* [CY8CPROTO-064B0S1-BLE BSP API Reference Manual][api]
* [CY8CPROTO-064B0S1-BLE Documentation](https://www.cypress.com/documentation/development-kitsboards/psoc-64-ble-prototyping-kit-cy8cproto-064b0s1-ble)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Infineon GitHub](https://github.com/infineon)
* [ModusToolbox™](https://www.cypress.com/products/modustoolbox-software-environment)

[api]: https://infineon.github.io/TARGET_CY8CPROTO-064B0S1-BLE/html/modules.html
[settings]: https://infineon.github.io/TARGET_CY8CPROTO-064B0S1-BLE/html/md_bsp_settings.html

---
© Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation, 2019-2021.