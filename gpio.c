#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include "gpio.h"
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

#ifndef stuff
#define stuff



//this is needed to set the function that the interrupt calls.
/**************
 * 
 * 
 * Interrupts
 * 
 *  
 * 
****************/ 




// This sets the subroutine that will run when the Timer overflow is set
uint16_t timer_interrupt_counter = 0;
uint16_t clk_tempo_counter = 0;
uint16_t clk_tempo = 1000;


ISR(TIMER0_COMPA_vect){
    timer_interrupt_counter ++;  //this should count the number of ms based on the division of clk in the timer setup
    clk_tempo_counter ++; //this counter is used for determining the nnumber of ms that 
    
    if(clk_tempo_counter >= clk_tempo){
        // write_port(0, *write_data_ptr);
        write_port(0, clk_engine());
        clk_tempo_counter = 0;
    }
    
}

uint8_t interrupt_entry_num = 0; //used to store how many times the interrupt has been triggered.  for tempos we need two clk pulses to derive the time between them
uint16_t clk_period = 0;  //value to store the time between clk pulses
ISR(INT0_vect){
    //this interrupt is used to set the tempo of the clk modifier.
    //It uses the ms value incremented from the timer interrupt to measure the time between pulses and set the tempo of the clk modifier
    
    //we need to add a way to debounce the trigger signal for this interrupt without adding a delay.
    //A simple delay used to debounce will cause our clk signal to drift since we need about 20ms of delay.
    
    if(interrupt_entry_num == 0){
        interrupt_entry_num ++;
        clk_period = timer_interrupt_counter;
    }

    else{
        interrupt_entry_num = 0;
        clk_tempo = abs(timer_interrupt_counter - clk_period);
    }

}

ISR(PCINT2_vect){
//     current_state = read_port(3)&0b11000000;
//     if(current_state == 0 && previous_state == 0b01000000){
//         _delay_ms(5);  
//         encoder_counter++;        
//         write_func_global(encoder_counter);
//     }
    
//     else if (current_state == 0 && previous_state == 0b10000000)
//     {
//         _delay_ms(5);   
//         encoder_counter--;        
//         write_func_global(encoder_counter);
//     }
//     // write_func_global(encoder_counter);
    
//     PCIFR |= 0b00000100;
//     previous_state = read_port(3)&0b11000000;

write_encoder_trig_func_global(1);  //when the interrupt is triggered we write a 1 to this function to indicate that the encoder has been triggered.
//the main function checks the value of this function and will then execute the encoder funciton to increment or decrement

}

/***********************
 * Encoder funcitons
 * 
 * 
 * 
 * ********************/

//this function is used to store when the encoder interrupt has been triggered
uint8_t encoder_stored_trig = 0;
uint8_t encoder_trig_func_global(uint8_t action, uint8_t data_to_store){
    
    switch (action)
    {
    case 0 :
        encoder_stored_trig = data_to_store;
        return encoder_stored_trig;
    
    case 1:
    return encoder_stored_trig;

    default:
        return 0;
    }
}

//we use this function to write the data to the encoder triggered function
void write_encoder_trig_func_global(uint8_t data){
    encoder_trig_func_global(0, data);
}

//we use this funciton to read the value of the encoder triggered function
uint8_t read_encoder_trig_func_global(){
    return encoder_trig_func_global(1, 0);
}

void write_encoder_data_func_global(uint8_t data){
    encoder_trig_func_global(0, data);
}

//we use this funciton to read the value of the encoder triggered function
uint8_t read_encoder_data_func_global(){
    return encoder_trig_func_global(1, 0);
}


//This is where we handle the functions for executing the encoder increment and decrement funcitons
uint8_t encoder_counter = 0;
uint8_t previous_state = 0;
uint8_t current_state = 0;
void execute_encoder_functions(){
    if(read_encoder_trig_func_global() == 1){
            current_state = read_port(3)&0b11000000;
            write_port(1, 0b00001111);
        if(current_state == 0 && previous_state == 0b01000000){
            _delay_ms(1);  
            encoder_counter++;        
            write_encoder_data_func_global(encoder_counter);
        }
        
        else if (current_state == 0 && previous_state == 0b10000000)
        {
            _delay_ms(5);   
            encoder_counter--;        
            write_encoder_data_func_global(encoder_counter);
        }
        
    
        PCIFR |= 0b00000100;
        previous_state = read_port(3)&0b11000000;
        write_encoder_trig_func_global(0);  //write a zero to the encoder triggered storing function to indicate that we have finished with the encoder duties
    }
}

/**************
 This is where we setup the subroutine that will run when the interupt for when the ADC conversion complete is triggered
****************/ 
volatile static uint8_t adc_convert_done = 1;
ISR(ADC_vect){
    adc_convert_done = 1;
}
void timer_setup(){
    TCCR0A |= (0b10 << WGM00);
    TCCR0B |= 0b11; //set prescale to divide by 64.  Dividing the 16MHz CLk by 64 then by 250 (the value for 0CR0A) will give us 1ms increments
    OCR0A = 249;  // this will then further divide our interrupt into 1ms divisions
    TIMSK0 |= (0b011 << CS00);
    
}

void dio_setup(){
    
    //this sets up the outputs and inputs for PORTB
    DDRB = 15;  //00001111 sets pin PB3, PB2, PB1, and PB0 as outputs and all other pins to inputs
    DDRD = 0; //00000000 sets all portD pins as inputs
    PORTD = 0b11111111; //enables portD pull ups    
}

void interrupt_setup(){
    //This sets up the interrupts.  INT0 is used for the TEmpo input

    EICRA = 2; //External Interrupt Control Register A.  This is used to set the how the external interrupt (INT0 and INT1) is triggered (falling edge, rising edge, or low level)
               //setting to 2 configures INT0 to be triggered on a falling edge
    EIMSK = 1; //External Interrupt Mask Register.  Used to enable the external interput pin.
    PCICR |= 0b100;
    PCMSK2 |= 0b11000000;

    sei(); //global interrupt enable
   
    }



/*******************************************
 * 
 * DIO
 * 
 * 
 * *****************************************/

void write_port(uint8_t port, uint8_t data){
    /*
    PortA = 0
    PortB = 1
    PortC = 2
    PortD = 3
    */
   if(port == 0){
    PORTB = (data & 15); //taking the bitwise AND so that we only write to the first 4 IO
   }

}

uint8_t read_port(uint8_t port){
     /*
    PortA = 0 * Note: there is no PORTA on teh Atmega328P this case will always return a zero
    PortB = 1
    PortC = 2
    PortD = 3  *when reading PORTD bits 0 and 1 will be high because they are the UART transmission and receive lines
    */
   switch (port){
    case 0:
        return 0; //there is no PORTA on the Atmega328p
    case 1:
        return PINB;
    case 2:
        return PINC;
    case 3:
        return PIND;
    }
   }



/*********************************************
 * 
 * ADC
 * 
 * 
 * 
 * 
 * *******************************************/




void adc_setup(){
    ADMUX = (1 << REFS0) | (1 << MUX2) | (1 << MUX0); //sets Vref to Vcc, left aligned, and connects ADC5 to the MUX
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADIE) | (1 << ADPS2); //enables ADC, starts ADC conversion,enables interrupt flag, sets adc clk division to 1/16 from system clk
    }


uint16_t adc_read(){
    
    adc_convert_done = 0;
    uint8_t adcl = 0;
    uint8_t adch = 0;

    ADCSRA |= 1 << ADSC; //enable conversion to start the measurement

    while(adc_convert_done == 0);
    
    //in order to correctly read from the registers you need to convert them to an integer first
    
    adcl = ADCL;
    adch = ADCH;

    return adch << 8 | adcl;
}



/*****************
 * Miscellaneous Funcitons
 * 
 * 
 * 
 * ******************/

//the _delay_ms built in function will not allow us to pass a variable into it.
//using a for loop with a 1ms time delay will instead have to do
void vc_delay(uint16_t time){
    for(uint16_t i = 0; i <= time; i++){
        _delay_ms(1);
    }
}



#endif
