#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "functions.h"
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


uint8_t get_channel_buttons_states();
uint8_t get_control_buttons_states();
void update_selected_channels(uint8_t selected_channels);