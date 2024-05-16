#ifndef UTILS_H
#define UTILS_H

#include "font.h"  

// Declare the function prototypes
void drawChar(unsigned char ch, int x, int y, unsigned int attr, int zoom);
void drawString(int x, int y, const char *str, unsigned int attr, int zoom);
unsigned int uart_isReadByteReady(void);
unsigned char getUart(void);
void wait_msec(unsigned int msVal);
void set_wait_timer(int set, unsigned int msVal);

#endif // UTILS_H