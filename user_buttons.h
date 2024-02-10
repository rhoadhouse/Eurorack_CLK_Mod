#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "functions.h"
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


uint8_t get_active_channel_buttons();
uint8_t get_control_buttons_states();
void update_selected_channels(uint8_t param_to_update, uint8_t update_value);
void set_selected_chans(uint8_t chans);