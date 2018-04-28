# Overview

Use the SPI peripheral on an STM8 chip to drive an ILI9341 screen.

I want to figure out the STM32 SPI peripheral, but it's more complex. So, I figure I'll get this TFT display working on the simple STM8 to make sure that I don't have the initialization sequence or communications wrong.

This project uses the STM8S103F3 chip. They are ridiculously cheap; a minimal dev board shouldn't cost more than $0.75.

Thanks to 'lujji' for a great overview of bare-metal programming for these chips and an overview of some registers/peripherals/etc:

https://lujji.github.io/blog/bare-metal-programming-stm8/

TODO: Use the hardware SPI peripheral.

# Running it

Build with SDCC:

sdcc -lstm8 -mstm8 --out-fmt-ihx --std-sdcc11 main.c

Flash with the 'stm8flash' project and a generic STLink/v2 module:

stm8flash -c stlinkv2 -p stm8s103f3 -w main.ihx

If the chip is write-protected and the flash operation times out, try resetting it:

echo "00 00 ff 00 ff 00 ff 00 ff 00 ff" | xxd -r -p > defaults.bin

stm8flash -c stlinkv2 -p stm8s103f3 -s opt -w defaults.bin

From: https://github.com/vdudouyt/stm8flash/issues/38

I haven't figured out on-chip debugging with OpenOCD yet.
