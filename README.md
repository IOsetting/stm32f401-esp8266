# stm32f401-esp8266
A working demo of ESP8266 ESP-01S UART WiFi module running on STM32F401CCU6

# Components Required

* STM32F401CCU6 board
* ESP-01S: ESP8266 Wi-Fi module
* UHF RFID module (optional)
* USB2TTL: PL2303 or CH340 or FT232 or CP2102
* ST-Link or J-LInk
* Laptop & Wi-Fi hotspot

# Circuit Diagram and connections

Refer below table to connect ESP-01S pins with STM32 pins:

| ESP-01S   | STM32    | USB2TTL      | RFID  |
| --------- | -------- | ------------ | ----  |
| GND       | GND      | GND          | GND   |
| TX(GPIO1) | PA3      |              |       |
| RX(GPIO3) | PA2      |              |       |
| 3.3V      | 3.3V     |              | 3.3V  |
|           | PA10     | TX           |       |
|           | PA9      | RX           |       |
|           | PA11     |              | RX    |
|           | PA12     |              | TX    |

# Working & Code Explanation

Use ST-Link to upload the code to STM32.  

Connect ST-Link with STM32 Development Board
```
G   -- GND
CLK -- SWCLK
IO  -- SWDIO
V3  -- 3.3V
```

## Create `config.h`

Add `config.h` under User folder, change the configurations accordingly.
```c
#ifndef _CONFIG_H
#define _CONFIG_H

const char WIFI_SSID[]  = "SSID";
const char WIFI_PASSWORD[] = "password";

const char SERVER_IP[] = "192.168.1.2";
const char SERVER_PORT[] = "5555";

#endif
```

## Compile 

Define
```
USE_STDPERIPH_DRIVER,STM32F401xx,PRINT_TO_UART
```

Include Paths
```
..\libraries\CMSIS\Include;..\libraries\CMSIS\Device\ST\STM32F4xx\Include;..\libraries\STM32F4xx_StdPeriph_Driver\inc;..\hardware;..\user
```

Compile Control String
```bash
--c99 --gnu -c --cpu Cortex-M4.fp -g -O0 --apcs=interwork --split_sections -I ../libraries/CMSIS/Include -I ../libraries/CMSIS/Device/ST/STM32F4xx/Include -I ../libraries/STM32F4xx_StdPeriph_Driver/inc -I ../hardware -I ../user
-I./RTE/_stm32f401esp8366
-IC:/Keil_v5/ARM/PACK/Keil/STM32F4xx_DFP/2.15.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include
-IC:/Keil_v5/ARM/CMSIS/Include
-D__UVISION_VERSION="525" -DSTM32F401xC -DUSE_STDPERIPH_DRIVER -DSTM32F401xx -DPRINT_TO_UART
-o .\Objects\*.o --omf_browse .\Objects\*.crf --depend .\Objects\*.d
```