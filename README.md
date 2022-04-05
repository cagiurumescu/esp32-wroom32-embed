## Getting started

Install the Expressif tools following their online documentation [here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html).

It works OK to git clone in /opt using sudo then run the `install.sh` script as normal user.

PMOD-ESP32 has a 4MB flash and the clock to flash is 40 MHz. To save the firmware that Digilent put in the flash perform the following:

* connect the UART (RX/TX/GND) on header J2 to the programming PC/SBC.
* connecting IO0 (BOOT) is not necessary as we'll use the switch SW1.2.
* power on the PMOD.
* slide switch SW1.2 to ON (BOOT).
* press BTN1 to reset.
* connect the UART at BAUD 115200, it should show something like:
```
   ets Jun  8 2016 00:22:57
   rst:0x1 (POWERON_RESET),boot:0x2 (DOWNLOAD_BOOT(UART0/UART1/SDIO_REI_FEO_V2))
   waiting for download
```
* close the UART and open a terminal and source the IDF's `export.sh`
* run:
```
   esptool.py --port /dev/ttyUSB0 --baud 115200 read_flash 0 0x400000 digilent.bin
``` 
* reading multiple times shows tiny differences in the file. These seem inconsequential as erasing the flash then re-writing any of the binaries restores the Digilent functionality.
* to erase the flash use:
```
   esptool.py --port /dev/ttyUSB0 --baud 115200 erase_flash
``` 
* following erase the chip will boot with the message:
```
   ets Jun  8 2016 00:22:57
   rst:0x10 (RTCWDT_RTC_RESET),boot:0x12 (SPI_FAST_FLASH_BOOT)
   flash read err, 1000
   ets_main.c 371
```
* to restore the original Digilent image run:
```
   esptool.py --port /dev/ttyUSB0 --baud 115200 write_flash --flash_mode dio --flash_freq 40m --flash_size 4MB 0x0 digilent.bin
```
* the Digilent WiFi has AP on IP 192.168.4.1 which can be pinged once connected. 

* could not get AT interface to work with Putty/Minicom (likely a CR/LF issue). Trying Python (make sure serial and pyserial packages are installed) and it seems to work. See [this](./esp32_at_test.py) code.


