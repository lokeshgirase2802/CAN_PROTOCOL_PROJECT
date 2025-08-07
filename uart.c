//uart.c
#include <LPC21xx.h>

// UART Initialization
void uart0_init(void) {
    PINSEL0 |= 0x05;     // Enable UART0 (TXD0 = P0.0, RXD0 = P0.1)
    U0LCR = 0x83;        // 8-bit data, 1 stop bit, no parity, enable DLAB
    U0DLM = 0;
    U0DLL = 97;          // Baud rate = 9600 for 15 MHz PCLK
    U0LCR = 0x03;        // Disable DLAB
}

// Send one character over UART
void uart0_tx(char ch) {
    while (!(U0LSR & 0x20));  // Wait until THR is empty
    U0THR = ch;
}

// Send string over UART
void uart0_print(const char *str) {
    while (*str) {
        uart0_tx(*str++);
    }
}

void uart0_print_num(signed char num) {
    char buf[5]; // Enough for "-128" + null terminator
    int i = 0;

    // Handle negative numbers
    if (num < 0) {
        uart0_tx('-');
        num = -num;
    }

    // Convert number to ASCII manually
    if (num == 0) {
        uart0_tx('0');
        return;
    }

    while (num > 0) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Print the digits in reverse
    while (--i >= 0) {
        uart0_tx(buf[i]);
    }
}

