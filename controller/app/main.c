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
int dataCnt = 0;
int i;

