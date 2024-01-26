#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "functions.h"
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
//setup for USART
// #define FOSC 1843200 //clock speed
// #define BAUD 9600
// #define MYUBRR FOSC/16/BAUD-1
#include "uart.h"
#include <stdint.h>


int main()
{
    // Initialize ports, ADC, UART, interrupts, etc
    uint8_t start[] = "Program Start\n\r";
    uint8_t print_buffer[64] = {0}; //establish the buffer that will hold our data to print
    dio_setup();
    adc_setup();
    interrupt_setup();
    timer_setup();
    
    //setup Uart
    uart_init(9600, 0);

    uart_send_string(start);
    uint8_t data = 'A';
    uint8_t value = 'B';
    // uint8_t * port_data_write;
    uint8_t data_to_write = 0;
    uint8_t * write_data_ptr;
    float volts = 0.0;

    uint8_t * encoder_interrupt_triggered_ptr;
    uint16_t loop_counter = 0;

    while (1) {
        //if(uart_read_count() > 0){

            data = uart_read(); //obtains the data that is within the read buffer
            
            volts = ADC_CONVERT_VOLTS(adc_read());
            // data_to_write = divider(0);
            // write_data_ptr = &data_to_write;

            data_to_write = read_func_global();
            write_data_ptr = &data_to_write;
            memset(print_buffer, 0, sizeof(print_buffer));
            
            if(loop_counter == 1000){

            sprintf((char*)print_buffer, "ADC read is: %0.2f volts, Counter is: %s\r", volts, num_to_binary_string(*write_data_ptr));
            // sprintf((char*)print_buffer, "%d\n\r", read_port);
            
            uart_send_string(print_buffer);
            loop_counter =0;
            }

            if(read_encoder_trig_func_global() == 1){
                execute_encoder_functions();
            }
            
            // vc_delay(1000/((volts*100)+1));        
            loop_counter++;
        }
    return 0;
    
}