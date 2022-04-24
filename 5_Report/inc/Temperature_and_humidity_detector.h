/**
 * header to enable data flow control over pins
 */
 #include <avr/io.h>
 /**
 * 
 * telling controller crystal frequency attached
 */
#define F_CPU 1000000
/*
*header to enable delay function in program
*/
#include <util/delay.h>
#include <stdlib.h>
/**
 * @brief giving name “enable”  to 5th pin of PORTD, since it Is connected to LCD enable pin
 * 
 */

#define enable            5
/**
 * @brief giving name “registerselection” to 6th pin of PORTD, since is connected to LCD RS pin
 * 
 */
#define registerselection 6

void send_a_command(unsigned char command);
void send_a_character(unsigned char character);
void send_a_string(char *string_of_characters);

int main(void)
{
    /**
     * @brief putting portB and portD as output pins
     * 
     */
    DDRB = 0xFF;
    DDRA = 0;
    DDRD = 0xFF;
    /**
     * @brief giving delay of 50ms
     * 
     */
    _delay_ms(50);
    /**
     * @brief setting the reference of ADC
     * enabling the ADC, setting free running mode, setting prescalar 128
     * 
     */
    
    ADMUX |=(1<<REFS0)|(1<<REFS1);
    ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
    
    int16_t COUNTA = 0;
    char SHOWA [3];
     

    send_a_command(0x01); //Clear Screen 0x01 = 00000001
    _delay_ms(50);
    send_a_command(0x38);
    _delay_ms(50);
    send_a_command(0b00001111);
    _delay_ms(50);
    
    ADCSRA |=(1<<ADSC);
    while(1)
    /**
     * @brief since the resolution (2.56/2^10 = 0.0025) is 2.5mV there 
     * will be an increment of 4 for every 10mV input, that means for every 
     * degree raise there will be increment of 4 in digital value. So to get
     *  the temperature we have to divide ADC output by four.
     * displaying name
     * shifting cursor  to 1st  shell  of second line
     * shifting cursor  to 9st  shell  of second line
     * command for putting variable number in LCD(variable number, in which 
     * character to replace, which base is variable(ten here as we are counting number in base10))
     * telling the display to show character(replaced by variable number) of first person after
     *  positioning the courser on LCD
     */
    {
        COUNTA = ADC/4;
        send_a_string ("CIRCUIT DIGEST");
        send_a_command(0x80 + 0x40 + 0);
        send_a_string ("Temp(C)=");
        send_a_command(0x80 + 0x40 + 8);
        itoa(COUNTA,SHOWA,10);
        send_a_string(SHOWA);
        send_a_string ("      ");
        send_a_command(0x80 + 0);
        
    }    
}

void send_a_command(unsigned char command)
/**
 * @brief putting 0 in RS to tell lcd we are sending command
 * telling lcd to receive command /data at the port
 *telling lcd we completed sending data
 **/
{
    PORTB = command;
    PORTD &= ~ (1<<registerselection);
    PORTD |= 1<<enable;
    _delay_ms(20);
    PORTD &= ~1<<enable;
    PORTB = 0;
}

void send_a_character(unsigned char character)
/**
 * @brief telling lcd we completed sending data/command
 * telling LCD to start receiving command/data
 telling LCD we are sending data not commands
 */
{
    PORTB = character;
    PORTD |= 1<<registerselection;
    PORTD |= 1<<enable;
    _delay_ms(20);
    PORTD &= ~1<<enable;
    PORTB = 0;
}
void send_a_string(char *string_of_characters)
{
    while(*string_of_characters > 0)
    {
        send_a_character(*string_of_characters++);
    }
}
 