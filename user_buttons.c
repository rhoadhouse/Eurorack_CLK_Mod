#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "functions.h"
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


bool selected_chans_array[8];

void set_selected_chans(uint8_t chans){
    for(uint8_t i = 0; i < 8; i++){
        uint8_t val = (1<<i);
        val = val & chans;
        selected_chans_array[i] = val>>i;
    }
}


uint8_t get_active_channel_buttons(){
    uint8_t chan_button_states = read_port(3);
    chan_button_states &= 0b00110011;
    return ~chan_button_states;
    //return the NOT of the channel buttons that are currently pressed.
    //We use the Not because buttons that are active will appear as low signals due to the active pullups being pulled low
}

uint8_t get_control_buttons_states(){
    uint8_t control_states = read_port(3);
        return control_states;

}


void update_selected_channels(uint8_t param_to_update, uint8_t update_value){
    // the param to update gets passed into the case structure then each active channel gets their param updated
    switch(param_to_update){

    case 0:
    set_selected_chans(get_active_channel_buttons());
    for(uint8_t i; i<8; i++){
            set_chan_divisions((i+1), update_value);
        
    }
    
    case 1:
    set_selected_chans(get_active_channel_buttons());
    for(uint8_t i; i<8; i++){
        if(selected_chans_array[i] == 1) {
            ((i+1),update_value);
        }
    }

    case 2:
    set_selected_chans(get_active_channel_buttons());
    for(uint8_t i; i<8; i++){
        if(selected_chans_array[i] == 1) {
            set_chan_pw((i+1),update_value);
        }
    }

    }
    
}

void update_para_per_selected_chan(uint8_t selected_channels, uint8_t param_to_update){

}