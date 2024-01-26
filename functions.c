
#include "functions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



uint8_t current_port_data = 0;
uint8_t counter = 0;
uint8_t *cpd_ptr = &current_port_data; //cpd_ptr stands for Current Port Data Pointer
bool divider_clk = 0;

uint8_t modifiy_port_data(uint8_t data, uint8_t chan, uint8_t mod, uint8_t count){
    //divides the counter by the specified divisor and if the remainder is zero then applies an exclusive OR mask to flp the bit.
    //returns the byte after applying the appropriate masks
        if (count%mod == 0){
        data ^= (1 << (chan-1));
    }
    return data;
}







//setting up a structure in order to store the different mod settings for each channel
chan_mods channels = {1,2,3,4,5,6,7,8}; //initialize the struct for channels

//function for changing the modifier value for a channel
void set_chan_divisions(int chan, int mod, chan_mods *channels){
    if(chan <=8){
        switch(chan){
            case 1:
                channels -> chan1_mod = mod;
                break;
            case 2:
                channels -> chan2_mod = mod;
                break;
            case 3:
                channels -> chan3_mod = mod;
                break;
            case 4:
                channels -> chan4_mod = mod;
                break;
            case 5:
                channels -> chan5_mod = mod;
                break;
            case 6:
                channels -> chan6_mod = mod;
                break;
            case 7:
                channels -> chan7_mod = mod;
                break;
            case 8:
                channels -> chan8_mod = mod;
                break;
        }
   }
}


// void init_channel_mods(chan_mods* channels){
// channels -> chan1_mod = 1;
// channels -> chan2_mod = 2;
// channels -> chan3_mod = 3;
// channels -> chan4_mod = 4;
// channels -> chan3_mod = 3;
// channels -> chan5_mod = 5;
// channels -> chan6_mod = 7;
// channels -> chan8_mod = 8;

// }


uint8_t clk_engine(chan_mods *channels){
    //this function is supposed to emulate a clk divider and muiltiplier
    
    //this is the "main clk" of the clk mod function.
    //we want to increment the counter each time the clk goes from 0 to 1 
    divider_clk ^= 1;
    if (divider_clk == 1){
         counter ++;
    }

    //Here is where we apply the mod to each channel
    current_port_data = modifiy_port_data(current_port_data, 1, (channels -> chan1_mod), counter);
    current_port_data = modifiy_port_data(current_port_data, 2, (channels -> chan2_mod), counter);
    current_port_data = modifiy_port_data(current_port_data, 3, (channels -> chan3_mod), counter);
    current_port_data = modifiy_port_data(current_port_data, 4, (channels -> chan4_mod), counter);
    current_port_data = modifiy_port_data(current_port_data, 5, (channels -> chan5_mod), counter);
    current_port_data = modifiy_port_data(current_port_data, 6, (channels -> chan6_mod), counter);
    current_port_data = modifiy_port_data(current_port_data, 7, (channels -> chan7_mod), counter);
    current_port_data = modifiy_port_data(current_port_data, 8, (channels -> chan8_mod), counter);

    

    return current_port_data; //use the bitwise not to invert the bits since we start with all ones.  Clk dividers start with channels in the low state
} 





//HAVE TO DECLARE THE POINTER TO THIS ARRAY IN ORDER FOR THE BELOW FUNCTION TO WORK 
char *binary_string[8] = {};
//I use this function to convert a number to a binary string for debug purposes when I need to see the individual bits
char *num_to_binary_string(uint8_t num){
    //this function is used for turning a number into a binary string to output over UART for debugging
    // char *binary_string[8] = {};
    sprintf((char*)binary_string, "%d%d%d%d%d%d%d%d\n", (num & 128) >> 7, (num & 64) >> 6, (num & 32) >> 5, (num & 16) >> 4, (num & 8) >> 3, (num & 4) >> 2, (num & 2) >> 1, num & 1);
    return binary_string;
    
}



/****************
 * This is a function that is used to store the data that we need to trasnport between the gpio.c file and the main funciton
 * 
 * 
 * 
 * 
 * *****************/
uint8_t stored_data = 0;
uint8_t func_global(uint8_t action, uint8_t data_to_store){
    switch (action)
    {
    case 0 :
        stored_data = data_to_store;
        return stored_data;
    
    case 1:
    return stored_data;

    default:
        return 0;
    }
}

void write_func_global(uint8_t data){
    func_global(0, data);
}

uint8_t read_func_global(){
    return func_global(1, 0);
}