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
