#include "intrinsics.h"
#include "msp430fr2310.h"
#include <msp430.h>

#define SLAVE_ADDRESS 0x46
volatile unsigned char data[3] = {10,4,10};
int index = 0;
int pattern_num = -1;
int base_transition_period = 8;
int button_pressed = 0;
int button_pressed_prev = -1;
int step = 0;
int i = 0;
int pattern[8] = {0,0,0,0,0,0,0,0};
int pattern_zero_arr[8] = {1, 0, 1, 0, 1, 0, 1, 0};
int pattern_one_arr[8];
int pattern_two_arr[8];
int pattern_three_arr[8];
int prev_patterns[3] = {0, 0, 0};

void LED_bar_setup(void);
void set_pattern(int[]);
void pattern_zero(int[]);
void pattern_one(int, int[]);
void pattern_two(int, int[]);
void pattern_three(int, int[]);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

    UCB0CTLW0 |= UCSWRST;

    P1SEL1 &= ~BIT3;
    P1SEL0 |= BIT3;

    P1SEL1 &= ~BIT2;
    P1SEL0 |= BIT2;

    UCB0CTLW0 &= ~UCTR;
    UCB0CTLW0 &= ~UCMST;
    UCB0CTLW0 |= UCMODE_3 | UCSYNC;

    UCB0I2COA0 = SLAVE_ADDRESS | UCOAEN;
    UCB0I2COA0 |= UCGCEN;

    UCB0CTLW0 &= ~UCSWRST;

    PM5CTL0 &= ~LOCKLPM5;

    UCB0IE |= UCRXIE0;
    __enable_interrupt();  // Enable global interrupts

    P1DIR |= BIT1;
    P1OUT &= ~BIT1;

    LED_bar_setup();
    set_pattern(pattern);
}

void LED_bar_setup()
{
    P1DIR |= BIT4;              //LED1
    P1DIR |= BIT5;              //LED2
    P1DIR |= BIT6;              //LED3
    P1DIR |= BIT7;              //LED4
    P2DIR |= BIT0;              //LED5
    P2DIR |= BIT6;              //LED6
    P2DIR |= BIT7;              //LED7
    P1DIR |= BIT0;              //LED8
}

void pattern_zero(int pattern_zero_arr[])
{
    set_pattern(pattern_zero_arr);
}

void pattern_one(int step, int pattern_one_arr[])
{
    if (step == 0)
    {
        pattern_one_arr[0] = 1;
        pattern_one_arr[1] = 0;
        pattern_one_arr[2] = 1;
        pattern_one_arr[3] = 0;
        pattern_one_arr[4] = 1;
        pattern_one_arr[5] = 0;
        pattern_one_arr[6] = 1;
        pattern_one_arr[7] = 0;
        set_pattern(pattern_one_arr);
    }
    else
    {
        pattern_one_arr[0] = 0;
        pattern_one_arr[1] = 1;
        pattern_one_arr[2] = 0;
        pattern_one_arr[3] = 1;
        pattern_one_arr[4] = 0;
        pattern_one_arr[5] = 1;
        pattern_one_arr[6] = 0;
        pattern_one_arr[7] = 1;
        set_pattern(pattern_one_arr);
    }
}

void pattern_two(int step, int pattern_two_arr[])
{
    int num = step;
    unsigned int mask = 1 << 7;
    int k;
    for (k = 0; k < 8; k++)
    {
        if (num & mask)
        {
            pattern_two_arr[k] = 1;
        }
        else {
            pattern_two_arr[k] = 0;
        }
        num <<= 1;
    }

    set_pattern(pattern_two_arr);
}

void pattern_three(int step, int pattern_three_arr[])
{
    if (step == 0)
    {
        pattern_three_arr[0] = 0;
        pattern_three_arr[1] = 0;
        pattern_three_arr[2] = 0;
        pattern_three_arr[3] = 1;
        pattern_three_arr[4] = 1;
        pattern_three_arr[5] = 0;
        pattern_three_arr[6] = 0;
        pattern_three_arr[7] = 0;
        set_pattern(pattern_three_arr);
    }
    else if (step == 1)
    {
        pattern_three_arr[0] = 0;
        pattern_three_arr[1] = 0;
        pattern_three_arr[2] = 1;
        pattern_three_arr[3] = 0;
        pattern_three_arr[4] = 0;
        pattern_three_arr[5] = 1;
        pattern_three_arr[6] = 0;
        pattern_three_arr[7] = 0;
        set_pattern(pattern_three_arr);
    }
    else if (step == 2)
    {
        pattern_three_arr[0] = 0;
        pattern_three_arr[1] = 1;
        pattern_three_arr[2] = 0;
        pattern_three_arr[3] = 0;
        pattern_three_arr[4] = 0;
        pattern_three_arr[5] = 0;
        pattern_three_arr[6] = 1;
        pattern_three_arr[7] = 0;
        set_pattern(pattern_three_arr);
    }
    else if (step == 3)
    {
        pattern_three_arr[0] = 1;
        pattern_three_arr[1] = 0;
        pattern_three_arr[2] = 0;
        pattern_three_arr[3] = 0;
        pattern_three_arr[4] = 0;
        pattern_three_arr[5] = 0;
        pattern_three_arr[6] = 0;
        pattern_three_arr[7] = 1;
        set_pattern(pattern_three_arr);
    }
    else if (step == 4)
    {
        pattern_three_arr[0] = 0;
        pattern_three_arr[1] = 1;
        pattern_three_arr[2] = 0;
        pattern_three_arr[3] = 0;
        pattern_three_arr[4] = 0;
        pattern_three_arr[5] = 0;
        pattern_three_arr[6] = 1;
        pattern_three_arr[7] = 0;
        set_pattern(pattern_three_arr);
    }
    else if (step == 5)
    {
        pattern_three_arr[0] = 0;
        pattern_three_arr[1] = 0;
        pattern_three_arr[2] = 1;
        pattern_three_arr[3] = 0;
        pattern_three_arr[4] = 0;
        pattern_three_arr[5] = 1;
        pattern_three_arr[6] = 0;
        pattern_three_arr[7] = 0;
        set_pattern(pattern_three_arr);
    }
}

void set_pattern(int pattern[]) {
    if (pattern[0] == 1)
    {
        P1OUT |= BIT4;
    }
    else
    {
        P1OUT &= ~BIT4;
    }
    if (pattern[1] == 1)
    {
        P1OUT |= BIT5;
    }
    else
    {
        P1OUT &= ~BIT5;
    }
    if (pattern[2] == 1)
    {
        P1OUT |= BIT6;
    }
    else
    {
        P1OUT &= ~BIT6;
    }
    if (pattern[3] == 1)
    {
        P1OUT |= BIT7;
    }
    else
    {
        P1OUT &= ~BIT7;
    }
    if (pattern[4] == 1)
    {
        P2OUT |= BIT0;
    }
    else
    {
        P2OUT &= ~BIT0;
    }
    if (pattern[5] == 1)
    {
        P2OUT |= BIT6;
    }
    else
    {
        P2OUT &= ~BIT6;
    }
    if (pattern[6] == 1)
    {
        P2OUT |= BIT7;
    }
    else
    {
        P2OUT &= ~BIT7;
    }
    if (pattern[7] == 1)
    {
        P1OUT |= BIT0;
    }
    else
    {
        P1OUT &= ~BIT0;
    }
}

#pragma vector=EUSCI_B0_VECTOR
__interrupt void EUSCI_B0_ISR(void)
{
    P1OUT |= BIT1;
    if (index == 2)
    {
        index = 0;
        data[0] = 0;
        data[1] = 0;
    }
    else if (index == 1)
    {
        if (button_pressed == 0)
        {
            button_pressed_prev = 0;
            button_pressed = 1;
        }
        else
        {
            button_pressed_prev = 1;
            button_pressed = 0;
        }
    }
    data[index] = UCB0RXBUF;
    index++;
    P1OUT &= ~BIT1;
    UCB0IFG &= ~UCRXIFG;
}
