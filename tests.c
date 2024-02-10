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


typedef struct my_struct{
    int num;
    int num2;
}test_struct;

test_struct return_struct();
test_struct test_data = {1,2};

test_struct return_struct(){
    test_data.num = 5;
}


bool selected_chans_array[8];

void set_selected_chans(uint8_t chans);
void set_selected_chans(uint8_t chans){
    printf("assigning selected chann\n");
    for(uint8_t i = 0; i < 8; i++){
        uint8_t val = (1<<i);
        val = (val & chans);
        selected_chans_array[i] = val>>i;
        printf("%d, %d\n", selected_chans_array[i],i);
    }
}

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


printf("Stuff");

// print_all_channels();
// printf("setting chan divisions...\n");
// set_chan_divisions(1, 8);
// set_chan_divisions(2, 7);
// set_chan_divisions(3, 6);
// set_chan_divisions(4, 5);
// set_chan_divisions(5, 4);
// set_chan_divisions(6, 3);
// set_chan_divisions(7, 2);
// set_chan_divisions(8, 1);

print_all_channels();

for(uint16_t i; i<700; i++){
    printf(num_to_binary_string(clk_engine()));
    
}



// printf("chan 1 %d, chan 2 %d, chan 3 %d, chan 4 %d, chan 5 %d, chan 6 %d \n", channels.chan1_mod, channels.chan2_mod, channels.chan3_mod, channels.chan4_mod, channels.chan5_mod, channels.chan6_mod);


uint8_t some_value = 56;



set_selected_chans(some_value);


int myvar = 1;

test_struct t1 = {3, 5};
printf("num1 is %d\n", test_data.num);
printf("num2 is %d\n", test_data.num2);
return_struct();
printf("num1 is %d\n", test_data.num);
printf("num2 is %d\n", test_data.num2);


uint8_t yarp = 1;

printf("%d\n", yarp);
yarp = yarp << 0;
printf("%d\n", yarp);



}

