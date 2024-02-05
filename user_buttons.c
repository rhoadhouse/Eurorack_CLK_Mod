#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "functions.h"
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>



uint8_t get_channel_buttons_states(){
    uint8_t chan_button_states = read_port(3);
    return chan_button_states &= 0b00110011;  //return the channel buttons that are currently pressed
}

uint8_t get_control_buttons_states(){
    uint8_t control_states = read_port(3);
        return control_states;

}


void update_selected_channels(uint8_t selected_channels, uint8_t param_to_update){
    // the channels gets passed in, then we need to take the value of each channel and apply 
    switch(param_to_update){

    case 0:
    ;

    }
    
}

void update_para_per_selected_chan(uint8_t selected_channels, uint8_t param_to_update){

}