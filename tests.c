#include "functions.h"
#include <string.h>
#include <stdio.h>
//setup for USART
// #define FOSC 1843200 //clock speed
// #define BAUD 9600
// #define MYUBRR FOSC/16/BAUD-1
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


void main(){

uint8_t print_buffer[64] = {0};
memset(print_buffer, 0, sizeof(print_buffer));
sprintf((char*)print_buffer, "data");
printf(print_buffer);



uint8_t num_array[]= {0, 255, 127, 63, 31, 15, 7, 3, 1, 0};

for(uint16_t i; i<sizeof(num_array); i++){
    printf(num_to_binary_string(num_array[i])); 
    
}
printf("This is the tests for the divider function\n\n");

// for(uint16_t i; i<10; i++){
//     printf("%d\n",divider(1));
// }


extern struct chan_mods channels;
// channels.chan1_mod = 1;
// channels.chan2_mod = 2;
// channels.chan3_mod = 3;
// channels.chan4_mod = 4;
// channels.chan5_mod = 5;
// channels.chan6_mod = 6;
// channels.chan7_mod = 7;
// channels.chan8_mod = 8;
// init_channel_mods(channels);

printf("chan 1 is %d\n", channels.chan1_mod);
set_chan_divisions(1, 1, &channels);
printf("chan 1 is %d\n", channels.chan1_mod);


for(uint16_t i; i<20; i++){
    printf(num_to_binary_string(clk_engine(&channels)));
    
}



// printf("chan 1 %d, chan 2 %d, chan 3 %d, chan 4 %d, chan 5 %d, chan 6 %d \n", channels.chan1_mod, channels.chan2_mod, channels.chan3_mod, channels.chan4_mod, channels.chan5_mod, channels.chan6_mod);



int myvar = 1;





}

