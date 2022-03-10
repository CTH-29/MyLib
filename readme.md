# 一些芯片驱动源码

## 前因

在XDU的通院准备电赛时，作为软件组同学，积累了一些芯片驱动，折腾来折腾去感觉还是放在GitHub上好管理一些。

## 版权

我对各种许可了解比较少，本着互联网的开源精神，大家可以自由的使用，保留源文件的Header最好。假设的日后我能在其他项目中看到自己影子，也算是在互联网上留下些足迹了。

## 目录

由于文件的都是以 `.c/.h` 成对出现的，而且也便较多，就统一放在一个文件夹内。

目前已有的芯片如下（按照字母顺序），*表示接口自定义，需要查阅数据手册

### 芯片相关(Lib for IC)

| 芯片     | 文件             | 备注                                               | 接口          |
| :------- | :------------   | :------------------------------------------------- | ------------- |
| ad9834   | \~.c/\~.h       | ADI的DDS芯片，75Mhz                                 | *             |
| ad9910   | \~.c/\~.h       | ADI的DDS芯片，14bit，1GSPS采样率                     | *             |
| ad9959   | \~.c/\~.h       | ADI的DDS芯片，四通道，500MSPS采样率                  | *             |
| adf4351  | \~.c/\~.h       | 锁相环，35 MHz to 4.4 GHz                           | *             |
| aht10    | \~.c/\~.h       | 较高质量的温湿度传感器                               | IIC           |
| as608    | \~.c/\~.h       | 指纹传感器                                          | UART/USB      |
| dht11    | \~.c/\~.h       | 温湿度传感器，单总线                                 | *             |
| ds1302   | \~.c/\~.h       | 实时时钟RTC                                         | 类IIC         |
| ds1307   | \~.c/\~.h       | 实时时钟RTC                                         | IIC           |
| eeprom   | \~.c/\~.h       | 存储芯片（24c02，24c32）                             | IIC           |
| esp8266  | \~.c/\~.h       | WIFI模块，AT指令驱动（物联网的话建议搭配iot库使用）    | UART          |
| gy30     | \~.c/\~.h       | 数字光强传感器，IIC接口                              | IIC           |
| hmc472   | \~.c/\~.h       | 数字步进衰减器，                                     | 并行接口      |
| hmi      | \~.c/\~.h       | HMI串口屏，串口驱动                                  | UART          |
| lcd1602  | \~.c/\~.h       | 经典LCD液晶屏，16列2行，支持8个自定义字符，            | 并行接口／IIC |
| max262   | \~.c/\~.h       | 程控滤波器                                          | *             |
| max30102 | \~.c/\~.h       | 心率血氧传感器                                      | IIC            |
| mlx90614 | \~.c/\~.h       | 高精度温度传感器                                     | IIC           |
| mpu6050  | \~.c/\~.h       | 六轴运动传感器                                      | IIC            |
| nrf24l01 | \~.c/\~.h       | 2.4G无线传输模块                                    | SPI           |
| SSD1306  | \~.c/\~.h       | 经典OLED驱动，建议搭配mygui库使用                    | IIC/SPI       |
| st7735   | \~.c/\~.h       | IPS屏幕驱动                                       |  SPI          |
| mfrc522  | rc522.c/rc522.h | RFID芯片，支持ISO14443A/MIFARE                      | SPI          |
| rda5820  | \~.c/\~.h       | FM收发芯片                                          | IIC           |
| W5500    | \~.c/\~.h       | 以太网芯片                                          | SPI           |
| ws2812b  | \~.c/\~.h       | 彩色LED                                            | *             |
| x9c103   | \~.c/\~.h       | 数字电位器（不推荐）                                 | *             |
| xpt2046  | \~.c/\~.h       | 触摸控制器                                          | SPI           |

### STM32 驱动相关(Lib for STM32)

| 文件              | 备注                            |
| :---------------- | ------------------------------ |
| base.c/base.h     | IO，串口的快速使用               |
| myadc.c/myadc.h   | ADC采样                         |
| mydac.c/mydac.h   | DAC输出波形                     |
| mytask.c/mytask.h | 类Arduino风格，减少对生成代码的修改 |
| mytim.c/mytim.h   | 定时器的重新配置                 |
| myuart.c/myuart.h | 使用DMA和buffer的串口，效率更高   |
| servo.c/servo.h   | 普通舵机驱动                     |
| stepmotor.c/stepmotor.h | 4相8拍步进电机              |

### 其他相关(Lib for Other)

| 文件            | 备注                      |
| --------------- | ------------------------- |
| _template.c/_template.h         | 库模板     |
| fonts.h         | GUI使用的字体              |
| iot.c/iot.h     | 物联网框架                |
| mydsp.c/mydsp.h | 简单的信号处理            |
| mygui.c/mygui.h | 简单的GUI框架             |
| myi2c.c/myi2c.h | 模拟IIC通信               |
| myspi.c/myspi.h | 模拟SPI通信               |

### 未完成的库(Lib Unfinished)

| 文件                 | 备注                       |
| ---------------      | ------------------------- |
| ili9341.c/ili9341.h  | TFT LCD                   |

## 使用

所有的上述使用的工具链为

> STM32CubeMX+MDK

大部分驱动使用时需要提前配置STM32的外设，具体查看相应h文件的TIP部分。

为了方便移植，每个驱动尽可能的把与底层相关的内容抽离出来，进行定义或重写即可。

## 最后

本人并非大佬，代码多多少少有BUG，可以联系我解决，我可能会看。

Enjoy coding!
