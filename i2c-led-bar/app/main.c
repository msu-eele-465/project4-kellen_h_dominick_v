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
