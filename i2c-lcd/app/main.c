i#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SLAVE_ADDRESS 0x45

void set_DB0(int);
void set_DB1(int);
void set_DB2(int);
void set_DB3(int);
void set_DB4(int);
void set_DB5(int);
void set_DB6(int);
void set_DB7(int);
void set_all_DB(int, int, int, int, int, int, int, int);

void set_enable(int);
void set_RW(int);
void set_RS(int);
void enable_HTL();
void enable_LTH();
void read_data();
void move_cursor_right(int);
void move_cursor_left(int);
void return_home();
void clear_display();

void display_last_key();
void display_pattern_0();
void display_pattern_1();
void display_pattern_2();
void display_pattern_3();
void display_pattern_4();
void display_pattern_5();
void display_pattern_6();
void display_pattern_6();
void display_pattern_7();

void load_1();
void load_2();
void load_3();
void load_4();
void load_5();
void load_6();
void load_7();
void load_8();
void load_9();
void load_0();
void load_A();
void load_B();
void load_C();
void load_D();
void load_Star();
void load_Pound();

void load_a();
void load_c();
void load_d();
void load_E();
void load_F();
void load_G();
void load_H();
void load_I();
void load_L();
void load_N();
void load_O();
void load_P();
void load_R();
void load_S();
void load_T();
void load_U();
void load_W();
void load_Space();

volatile unsigned char data[2];
int index = 0;
int pattern_num = -1;
int i;

void set_DB0(int bit)
{
    if (bit)
    {
	P4OUT |= BIT5;
    }
    else
    {
	P4OUT &= ~BIT5;
    }
}

void set_DB1(int bit)
{
    if (bit)
    {
	P5OUT |= BIT2;
    }
    else
    {
	P5OUT &= ~BIT2;
    }
}

void set_DB2(int bit)
{
    if (bit)
    {
	P3OUT |= BIT6;
    }
    else
    {
	P3OUT &= ~BIT6;
    }
}

void set_DB3(int bit)
{
    if (bit)
    {
	P1OUT |= BIT7;
    }
    else
    {
	P1OUT &= ~BIT7;
    }
}

void set_DB4(int bit)
{
    if (bit)
    {
	P1OUT |= BIT6;
    }
    else
    {
	P1OUT &= ~BIT6;
    }
}

void set_DB5(int bit)
{
    if (bit)
    {
	P1OUT |= BIT5;
    }
    else
    {
	P1OUT &= ~BIT5;
    }
}

void set_DB6(int bit)
{
    if (bit)
    {
	P1OUT |= BIT1;
    }
    else
    {
	P1OUT &= ~BIT1;
    ]
}

void set_DB7(int bit)
{
    if (bit)
    {
	P5OUT |= BIT4;
    }
    else
    {
	P5OUT &= ~BIT4;
    }
}

void set_all_DB(int bit0, int bit1, int bit2, int bit3, int bit4, int bit5, int bit6, int bit7)
{
    set_DB0(bit0);
    set_DB1(bit1);
    set_DB2(bit2);
    set_DB3(bit3);
    set_DB4(bit4);
    set_DB5(bit5);
    set_DB6(bit6);
    set_DB7(bit7);
}

void set_enable(int bit)
{
    if (bit)
    {
	P3OUT |= BIT4;
    }
    else
    {
	P3OUT &= ~BIT4;
    }
}

void set_RW(int bit)
{
    if (bit)
    {
	P3OUT |= BIT5;
    }
    else
    {
	P3OUT &= ~BIT5;
    }
}

void set_RS(int bit)
{
    if (bit)
    {
	P3OUT |= BIT1;
    }
    else
    {
	P3OUT &= ~BIT1;
    }
}

void enable_HTL()
{
    set_enable(1);
    __delay_cycles(5);
    set_enable(0);
}

void enable_LTH()
{
    set_enable(0);
    __delay_cycles(5);
    set_enable(1);
}

void read_data()
{
    set_RS(1);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 0, 0, 0, 1, 1, 0, 0);
    __delay_cycles(2000);
}

void move_cursor_right(int num_times)
{
    for(i = 0; i < num_times; i++)
    {
        set_RS(0);
        set_RW(0);
        enable_HTL();
        set_all_DB(0, 0, 1, 0, 1, 0, 0, 0);
        __delay_cycles(2000);
    }
}

void move_cursor_left(int num_times)
{
    for(i = 0; i < num_times; i++)
    {
        set_RS(0);
        set_RW(0);
        enable_HTL();
        set_all_DB(0, 0, 0, 0, 1, 0, 0, 0);
        __delay_cycles(2000);
    }
}

void return_home()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 1, 0, 0, 0, 0, 0, 0);
    __delay_cycles(2000);
}

void clear_display()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 0, 0, 0, 0, 0, 0, 0);
    __delay_cycles(2000);
}

void display_last_key()
{
    move_cursor_right(55);
    load_A();
    read_data();
}

void display_pattern_0()
{
    return_home();
    clear_display();
    load_S();
    read_data();
    load_T();
    read_data();
    load_a();
    read_data();
    load_T();
    read_data();
    load_I();
    read_data();
    load_c();
    read_data();
}

void display_pattern_1()
{
    return_home();
    clear_display();
    load_T();
    read_data();
    load_O();
    read_data();
    load_G();
    read_data();
    load_G();
    read_data();
    load_L();
    read_data();
    load_E();
    read_data();
}

void display_pattern_2()
{
    return_home();
    clear_display();
    load_U();
    read_data();
    load_P();
    read_data();
    load_Space();
    read_data();
    load_c();
    read_data();
    load_O();
    read_data();
    load_U();
    read_data();
    load_N();
    read_data();
    load_T();
    read_data();
    load_E();
    read_data();
    load_R();
    read_data();
}

void display_pattern_3()
{
    return_home();
    clear_display();
    load_I();
    read_data();
    load_N();
    read_data();
    load_Space();
    read_data();
    load_a();
    read_data();
    load_N();
    read_data();
    load_d();
    read_data();
    load_Space();
    read_data();
    load_O();
    read_data();
    load_U();
    read_data();
    load_T();
    read_data();
}

void display_pattern_4()
{
    return_home();
    clear_display();
    load_d();
    read_data();
    load_O();
    read_data();
    load_W();
    read_data();
    load_N();
    read_data();
    load_Space();
    read_data();
    load_c();
    read_data();
    load_O();
    read_data();
    load_U();
    read_data();
    load_N();
    read_data();
    load_T();
    read_data();
    load_E();
    read_data();
    load_R();
    read_data();
}

void display_pattern_5()
{
    return_home();
    clear_display();
    load_R();
    read_data();
    load_O();
    read_data();
    load_T();
    read_data();
    load_a();
    read_data();
    load_T();
    read_data();
    load_E();
    read_data();
    load_Space();
    read_data();
    load_1();
    read_data();
    load_Space();
    read_data();
    load_L();
    read_data();
    load_E();
    read_data();
    load_F();
    read_data();
    load_T();
    read_data();
}

void display_pattern_6()
{
    return_home();
    clear_display();
    load_R();
    read_data();
    load_O();
    read_data();
    load_T();
    read_data();
    load_a();
    read_data();
    load_T();
    read_data();
    load_E();
    read_data();
    load_Space();
    read_data();
    load_7();
    read_data();
    load_Space();
    read_data();
    load_R();
    read_data();
    load_I();
    read_data();
    load_G();
    read_data();
    load_H();
    read_data();
    load_T();
    read_data();
}

void display_pattern_7()
{
    return_home();
    clear_display();
    load_F();
    read_data();
    load_I();
    read_data();
    load_L();
    read_data();
    load_L();
    read_data();
    load_Space();
    read_data();
    load_L();
    read_data();
    load_E();
    read_data();
    load_F();
    read_data();
    load_T();
    read_data();
}

//////////////////////////////////////////////////////////////////

void load_1()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 0, 0, 0, 1, 1, 0, 0);
    __delay_cycles(2000);
}

void load_2()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 1, 0, 0, 1, 1, 0, 0);
    __delay_cycles(2000);
}

void load_3()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 1, 0, 0, 1, 1, 0, 0);
    __delay_cycles(2000);
}

void load_4()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 0, 1, 0, 1, 1, 0, 0);
    __delay_cycles(2000);
}

void load_5()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 0, 1, 0, 1, 1, 0, 0);
    __delay_cycles(2000);
}

void load_6()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 1, 1, 0, 1, 1, 0, 0);
    __delay_cycles(2000);
}

void load_7()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 1, 1, 0, 1, 1, 0, 0);
    __delay_cycles(2000);
}

void load_8()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 0, 0, 1, 1, 1, 0, 0);
    __delay_cycles(2000);
}

void load_9()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 0, 0, 1, 1, 1, 0, 0);
    __delay_cycles(2000);
}

void load_0()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 0, 0, 0, 1, 1, 0, 0);
    __delay_cycles(2000);
}

void load_A()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 0, 0, 0, 0, 0, 1, 0);
    __delay_cycles(2000);
}

void load_B()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 1, 0, 0, 0, 0, 1, 0);
    __delay_cycles(2000);
}

void load_C()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 1, 0, 0, 0, 0, 1, 0);
    __delay_cycles(2000);
}

void load_D()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 0, 1, 0, 0, 0, 1, 0);
    __delay_cycles(2000);
}

void load_Star()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 1, 0, 1, 0, 1, 0, 0);
    __delay_cycles(2000);
}

void load_Pound()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 1, 0, 0, 0, 1, 0, 0);
    __delay_cycles(2000);
}

////////////////////////////////////////////////////////////

void load_a()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 0, 0, 0, 0, 1, 1, 0);
    __delay_cycles(2000);
}

void load_c()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 1, 0, 0, 0, 1, 1, 0);
    __delay_cycles(2000);
}

void load_d()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 0, 1, 0, 0, 1, 1, 0);
    __delay_cycles(2000);
}

void load_E()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 0, 1, 0, 0, 1, 1, 0);
    __delay_cycles(2000);
}

void load_F()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 1, 1, 0, 0, 1, 1, 0);
    __delay_cycles(2000);
}

void load_G()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 1, 1, 0, 0, 1, 1, 0);
    __delay_cycles(2000);
}

void load_H()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 0, 0, 1, 0, 1, 1, 0);
    __delay_cycles(2000);
}

void load_I()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 0, 0, 1, 0, 1, 1, 0);
    __delay_cycles(2000);
}

void load_L()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 0, 1, 1, 0, 1, 1, 0);
    __delay_cycles(2000);
}

void load_N()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 1, 1, 1, 0, 1, 1, 0);
    __delay_cycles(2000);
}

void load_O()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 1, 1, 1, 0, 1, 1, 0);
    __delay_cycles(2000);
}

void load_P()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 0, 0, 0, 1, 1, 1, 0);
    __delay_cycles(2000);
}

void load_R()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 1, 0, 0, 1, 1, 1, 0);
    __delay_cycles(2000);
}

void load_S()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 1, 0, 0, 1, 1, 1, 0);
    __delay_cycles(2000);
}

void load_T()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 0, 1, 0, 1, 1, 1, 0);
    __delay_cycles(2000);
}

void load_U()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 0, 1, 0, 1, 1, 1, 0);
    __delay_cycles(2000);
}

void load_W()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(1, 1, 1, 0, 1, 1, 1, 0);
    __delay_cycles(2000);
}

void load_Space()
{
    set_RS(0);
    set_RW(0);
    enable_HTL();
    set_all_DB(0, 0, 0, 0, 0, 1, 0, 0);
    __delay_cycles(2000);
}

#pragma vector=EUSCI_B0_VECTOR
__interrupt void EUSCI_B0_ISR()
{
    if(index == 2)
    {
        index = 0;
    }
    data[index] = UCB0RXBUF;
    pattern_num = data[0];
    index++;
    UCB0IFG &= ~UCRXIFG;
}
