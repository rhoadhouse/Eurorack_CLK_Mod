#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#ifndef GPIO_H
#define GPIO_H

void dio_setup();
void adc_setup();
void interrupt_setup();
void vc_delay(uint16_t time);
void write_port(uint8_t port, uint8_t data);
uint8_t read_port(uint8_t port);
void timer_setup();
uint8_t encoder_trig_func_global(uint8_t action, uint8_t data_to_store);
void write_encoder_trig_func_global(uint8_t data);
uint8_t read_encoder_trig_func_global();
void execute_encoder_functions();

#define ADC_CONVERT_VOLTS(x) (x*(5.0/1024.0))

uint8_t *write_data_ptr;
uint8_t *encoder_ptr;
uint16_t adc_read();




#endif
