#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Function Declarations
void unlock_loop();
void keypad_setup();
void heartbeat_setup();
bool arrays_equal(char[], char[]);
void key_released(volatile unsigned char*, unsigned char);
void RGB_LED_setup();
void red_LED();
void yellow_LED();
void green_LED();
void color_change(int, int, int);
void master_setup(void);
void write_to_slave(unsigned char, volatile unsigned char[]);

unsigned char SLAVE_ADDRESS_1 = 0x45;
unsigned char SLAVE_ADDRESS_2 = 0x46;
volatile unsigned char data[2] = {0, 0};
int BYTES = 2;
int data_cnt = 0;
int i;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    master_setup();
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    UCB0CTLW0 &= ~UCSWRST;                  //Take B0 out of software reset

    __enable_interrupt();

    //Setup all devices
    keypad_setup();
    RGB_LED_setup();
    heartbeat_setup();

    P4DIR |= BIT7;
    P2DIR |= BIT4;
    P2DIR |= BIT5;
    P2DIR |= BIT6;
    P4OUT |= BIT7;
    P2OUT |= BIT4;
    P2OUT |= BIT5;
    P2OUT |= BIT6;


    //Initialize variables (global)
    char input_arr[4] = {'e', 'e', 'e', 'e'};
    char input_arr_pre[4];
    char unlock_code[4] = {'1', '2', '3', '4'};
    bool locked = true;
    unsigned int counter = 0;
    volatile unsigned char base_transition_period = 4;
    int step = 0;
    int j;

    //Poll keypad forever
    while (true)
    {
        //Set LED to red to start
        red_LED();
        while (locked)
        {
            //If a key has been pressed, set LED to yellow
            if(input_arr[0] != 'e')
	    {
		yellow_LED();
            }
            for (i = 0; i < 4; i++)
            {
                input_arr_pre[i] = input_arr[i];
            }
            //poll row 1
            P5OUT &= ~BIT4;
            if ((P3IN & BIT7) == 0)
            {
                input_arr[counter] = '1';
                key_released(&P3IN, BIT7);
            }
            else if ((P1IN & BIT4) == 0)
            {
                input_arr[counter] = '2';
                key_released(&P1IN, BIT4);
            }
            else if ((P1IN & BIT5) == 0)
            {
                input_arr[counter] = '3';
                key_released(&P1IN, BIT5);
            }
            else if ((P1IN & BIT6) == 0)
            {
                input_arr[counter] = 'A';
                key_released(&P1IN, BIT6);
            }
            //poll row 2
            P5OUT |= BIT4;
            P3OUT &= ~BIT4;
            if ((P3IN & BIT7) == 0)
            {
                input_arr[counter] = '4';
                key_released(&P3IN, BIT7);
            }
            else if ((P1IN & BIT4) == 0)
            {
                input_arr[counter] = '5';
                key_released(&P1IN, BIT4);
            }
            else if ((P1IN & BIT5) == 0)
            {
                input_arr[counter] = '6';
                key_released(&P1IN, BIT5);
            }
            else if ((P1IN & BIT6) == 0)
            {
                input_arr[counter] = 'B';
                key_released(&P1IN, BIT6);
            }
            //poll row 3
            P3OUT |= BIT4;
            P3OUT &= ~BIT5;
            if ((P3IN & BIT7) == 0)
            {
                input_arr[counter] = '7';
                key_released(&P3IN, BIT7);
            }
            else if ((P1IN & BIT4) == 0)
            {
                input_arr[counter] = '8';
                key_released(&P1IN, BIT4);
            }
            else if ((P1IN & BIT5) == 0)
            {
                input_arr[counter] = '9';
                key_released(&P1IN, BIT5);
            }
            else if ((P1IN & BIT6) == 0)
            {
                input_arr[counter] = 'C';
                key_released(&P1IN, BIT6);
            }
            //poll row 4
            P3OUT |= BIT5;
            P3OUT &= ~BIT6;
            if ((P3IN & BIT7) == 0)
            {
                input_arr[counter] = '*';
                key_released(&P3IN, BIT7);
            }
            else if ((P1IN & BIT4) == 0)
            {
                input_arr[counter] = '0';
                key_released(&P1IN, BIT4);
            }
            else if ((P1IN & BIT5) == 0)
            {
                input_arr[counter] = '#';
                key_released(&P1IN, BIT5);
            }
            else if ((P1IN & BIT6) == 0)
            {
                input_arr[counter] = 'D';
                key_released(&P1IN, BIT6);
            }
            P3OUT |= BIT6;

            //if 4 keys have been pressed, check if equal to unlock code
            int correct = 0;
            if (counter == 4)
            {
                for (i = 0; i < 4; i++)
                {
                    if (input_arr[i] != unlock_code[i] )
                    {
                        counter = 0;
                        for (j = 0; j < 4; j++)
                        {
                            input_arr[j] = 'e';
                        }
                        red_LED();
                        break;
                    }
                    correct++;
                }
                if (correct == 4)
		{
			locked = false;
		}
            }
            else if (!arraysEqual(input_arr, input_arr_pre))
	    {
		counter++;
	    }
        }

        //If unlock code was entered, set LED to green
        green_LED();

        //Loop checking for pattern code
        while (true)
        {
            //Poll row 1
            P5OUT &= ~BIT4;
            if ((P3IN & BIT7) == 0)
            {
                data[0] = 1;
                data[1] = base_transition_period;
                key_released(&P3IN, BIT7);
                write_to_slave(SLAVE_ADDRESS_2, data);
		write_to_slave(SLAVE_ADDRESS_1, data);
                P4OUT |= BIT7;
                P2OUT &= ~BIT4;
                P2OUT &= ~BIT5;
                P2OUT &= ~BIT6;
            }
            else if ((P1IN & BIT4) == 0)
            {
                data[0] = 2;
                data[1] = base_transition_period;
                key_released(&P1IN, BIT4);
                write_to_slave(SLAVE_ADDRESS_2, data);
		write_to_slave(SLAVE_ADDRESS_1, data);
                P4OUT &= ~BIT7;
                P2OUT |= BIT4;
                P2OUT &= ~BIT5;
                P2OUT &= ~BIT6;
            }
            else if ((P1IN & BIT5) == 0)
            {
                data[0] = 3;
                data[1] = base_transition_period;
                key_released(&P1IN, BIT5);
                write_to_slave(SLAVE_ADDRESS_2, data);
		write_to_slave(SLAVE_ADDRESS_1, data);
                P4OUT |= BIT7;
                P2OUT |= BIT4;
                P2OUT &= ~BIT5;
                P2OUT &= ~BIT6;
            }
            else if ((P1IN & BIT6) == 0)
            {
                key_released(&P1IN, BIT6);
                if (base_transition_period > 1)
                {
                    base_transition_period -= 1;
                    data[1] = base_transition_period;
                    data[0] = 8;
                    write_to_slave(SLAVE_ADDRESS_2, data);
		    write_to_slave(SLAVE_ADDRESS_1, data);
                }
            }
            P5OUT |= BIT4;
            //Poll row 2
            P3OUT &= ~BIT4;
            if ((P1IN & BIT6) == 0)
            {
                key_released(&P1IN, BIT6);
                if (base_transition_period < 8)
                {
                    base_transition_period += 1;
                    data[1] = base_transition_period;
                    data[0] = 8;
                    write_to_slave(SLAVE_ADDRESS_2, data);
		    write_to_slave(SLAVE_ADDRESS_1, data);
                }
            }
            P3OUT |= BIT4;
            //Poll row 4
            P3OUT &= ~BIT6;
            if ((P1IN & BIT4) == 0)
            {
                data[0] = 0;
                data[1] = base_transition_period;
                key_released(&P1IN, BIT4);
                write_to_slave(SLAVE_ADDRESS_2, data);
                write_to_slave(SLAVE_ADDRESS_1, data);
                P4OUT &= ~BIT7;
                P2OUT |= BIT4;
                P2OUT |= BIT5;
                P2OUT |= BIT6;
            }
            P3OUT |= BIT6;
        }
    }
    return 0;
}

void master_setup()
{
    UCB0CTLW0 |= UCSWRST;               //Software Reset

    UCB0CTLW0 |= UCSSEL__SMCLK;         //SMCLK
    UCB0BRW = 10;                       //Set prescalar to 10

    UCB0CTLW0 |= UCMODE_3;              //Put into i2c mode
    UCB0CTLW0 |= UCMST;                 //Set MSP430FR2355 as master

    UCB0CTLW1 |= UCASTP_2;
    UCB0TBCNT = 0x01;

    P1SEL1 &= ~BIT3;                    //SCL setup
    P1SEL0 |= BIT3;

    P1SEL1 &= ~BIT2;                    //SDA setup
    P1SEL0 |= BIT2;
}

void write_to_slave(unsigned char slave_address, volatile unsigned char data[])
{
    UCB0I2CSA = slave_address;
    UCB0CTLW0 |= UCTR;
    UCB0TBCNT = BYTES;
    UCB0IE |= UCTXIE0;
    UCB0CTLW0 |= UCTXSTT;
    for (i = 0; i < 200; i++)
    {

    }
    UCB0IE &= ~UCTXIE0;
    UCB0CTLW0 &= ~UCTR;
}

//Setup function for keypad
void keypad_setup()
{

    P1DIR &= ~BIT6;         // all columns set as inputs
    P1DIR &= ~BIT5;
    P1DIR &= ~BIT4;
    P3DIR &= ~BIT7;

    P1REN |= BIT6;          // enable resistors for columns
    P1REN |= BIT5;
    P1REN |= BIT4;
    P3REN |= BIT7;
    P1OUT |= BIT6;          // set column resistors as pull-ups
    P1OUT |= BIT5;
    P1OUT |= BIT4;
    P3OUT |= BIT7;

    P3DIR |= BIT6;          // all rows set as outputs
    P3DIR |= BIT5;
    P3DIR |= BIT4;
    P5DIR |= BIT4;

    P3OUT |= BIT6;          // initialize row outputs HI
    P3OUT |= BIT5;
    P3OUT |= BIT4;
    P5OUT |= BIT4;
}

//Setup function for hearbeat LED
void heartbeat_setup()
{
    P6DIR |= BIT6;
    P6OUT &= ~BIT6;

    TB3CTL = TBSSEL__ACLK | MC__UP | TBCLR;

    TB3CCR0 = 16384;
    TB3CCTL0 |= CCIE;
    TB3CCTL0 &= ~CCIFG;
}

//ISR for toggling LED2 for heartbeat LED
#pragma vector = TIMER3_B0_VECTOR
__interrupt void ISR_TB3_CCR0(void)
{
    P6OUT ^= BIT6;
    TB3CCTL0 &= ~CCIFG;
}

//Setup function for RGB LED
void RGB_LED_Setup()
{
    P5DIR |= BIT3 | BIT1 | BIT0;   // Set red, green, and blue pins to outputs

    TB0CTL = TBSSEL__ACLK | MC__UP | TBCLR;
    TB1CTL = TBSSEL__ACLK | MC__UP | TBCLR;
    TB2CTL = TBSSEL__ACLK | MC__UP | TBCLR;
    TB0CCR0 = 255;
    TB1CCR0 = 255;
    TB2CCR0 = 255;

    TB0CCR1 = 254;                  // RED
    TB1CCR1 = 254;                  // GREEN
    TB2CCR1 = 254;                  // BLUE

    TB0CCTL0 |= CCIE;
    TB0CCTL1 |= CCIE;
    TB1CCTL0 |= CCIE;
    TB1CCTL1 |= CCIE;
    TB2CCTL0 |= CCIE;
    TB2CCTL1 |= CCIE;
    __enable_interrupt();
    TB0CCTL0 &= ~CCIFG;
    TB0CCTL1 &= ~CCIFG;
    TB1CCTL0 &= ~CCIFG;
    TB1CCTL1 &= ~CCIFG;
    TB2CCTL0 &= ~CCIFG;
    TB2CCTL1 &= ~CCIFG;
}

//ISR for red period
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P5OUT &= ~BIT3;
    TB0CCTL0 &= ~CCIFG;
}

//ISR for red pulse width
#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_CCR1(void)
{
    P5OUT |= BIT3;
    TB0CCTL1 &= ~CCIFG;
}

//ISR for green period
#pragma vector = TIMER1_B0_VECTOR
__interrupt void ISR_TB1_CCR0(void)
{
    P5OUT &= ~BIT1;
    TB1CCTL0 &= ~CCIFG;
}

//ISR for green pulse width
#pragma vector = TIMER1_B1_VECTOR
__interrupt void ISR_TB1_CCR1(void)
{
    P5OUT |= BIT1;
    TB1CCTL1 &= ~CCIFG;
}

//ISR for blue period
#pragma vector = TIMER2_B0_VECTOR
__interrupt void ISR_TB2_CCR0(void)
{
    P5OUT &= ~BIT0;
    TB2CCTL0 &= ~CCIFG;
}

//ISR for blue pulse width
#pragma vector = TIMER2_B1_VECTOR
__interrupt void ISR_TB2_CCR1(void)
{
    P5OUT |= BIT0;
    TB2CCTL1 &= ~CCIFG;
}

//Checks if two char arrays are equal
bool arrays_equal(char arr1[], char arr2[])
{
    int i;
    for (i = 0; i < 4; i++) {
        if (arr1[i] != arr2[i])
        {
            return false;
        }
    }
    return true;
}

//Check if key has been unpressed
void key_released(volatile unsigned char* pin, unsigned char bit)
{
    while ((*pin & bit) == 0) {}
    return;
}

//Sets red
void red_LED()
{
    color_change(0, 254, 254);
}

//Sets yellow
void yellow_LED()
{
    color_change(0, 0, 254);
}

//Sets blue
void green_LED()
{
    color_change(254, 0, 254);
}

//Sets CCR1 for timers B0,1,2 to reflect correct color
void color_change(int red, int green, int blue)
{
    TB0CCR1 = 254 - red;
    TB1CCR1 = 254 - green;
    TB2CCR1 = 254 - blue;
}


#pragma vector=EUSCI_B0_VECTOR
__interrupt void EUSCI_B0_I2C_ISR(void)
{
    if (data_cnt == BYTES - 1)
    {
        UCB0TXBUF = data[data_cnt];
        data_cnt = 0;
    }
    else
    {
        UCB0TXBUF = data[data_cnt];
        data_cnt++;
    }
}
