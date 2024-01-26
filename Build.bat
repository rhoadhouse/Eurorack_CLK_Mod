avr-gcc gpio.c -o gpio.o -c -mmcu=atmega328p -DF_CPU=16000000UL -Os
avr-gcc functions.c -o functions.o -c -mmcu=atmega328p -DF_CPU=16000000UL -Os
avr-gcc uart.c -o uart.o -c -mmcu=atmega328p -DF_CPU=16000000UL -Os

avr-gcc main.c -o main.o -c -mmcu=atmega328p -DF_CPU=16000000UL -Os
avr-gcc -o ClkMod.elf main.o gpio.o functions.o uart.o -mmcu=atmega328p -DF_CPU=16000000UL -Os -Wl,-u,vfprintf -lprintf_flt -lm
avr-objcopy ClkMod.elf -O ihex ClkMod.hex