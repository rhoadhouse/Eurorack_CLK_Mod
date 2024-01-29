#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#ifndef FUNCTIONS_H
#define FUNCTIONS_H


typedef struct chan_mods{
    uint8_t chan1_mod;
    uint8_t chan2_mod;
    uint8_t chan3_mod;
    uint8_t chan4_mod;
    uint8_t chan5_mod;
    uint8_t chan6_mod;
    uint8_t chan7_mod;
    uint8_t chan8_mod;
}chan_mods;

chan_mods *get_chan_structure();
void print_all_channels();

void vc_delay(uint16_t time);
uint8_t modifiy_port_data(uint8_t data, uint8_t chan, uint8_t mod, uint8_t count);
uint8_t clk_engine();
char *num_to_binary_string(uint8_t num);


/*

Need to think of a way that we can store the desired clk mod with each channel
- we could use an array that has 8, 9, 10, etc values in it that refer to the division amount
    - to add a channel to the divisor add the corresponding number for that channel to the number in the array
    - to remove a channel from the divisor subtract the corresponding nubmer for that channel from teh number in the array
    - in our divider function we can then do our XNOR bit shifting but instead of with a fixed value, instead use the corresponding value from the array to affect each desired channel

- learn how to use a hash table

*/




void set_chan_divisions(int chan, int mod);


uint8_t read_func_global();
void write_func_global(uint8_t data);


#endif