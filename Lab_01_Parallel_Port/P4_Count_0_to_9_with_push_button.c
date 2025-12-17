/*
Auther: Janakantha S.M.B.G. (E/20/157)
Last Modified: 2025-12-17
Title: Count from 0 to 9 on a Seven Segment Display using Parallel Port with and a 74LS47 Decoder
Description: This program counts from 0 to 9 on a seven-segment display connected to a parallel port when a push button is pressed.
Note: Use a common anode seven-segment display.
Port Map:
    Parallel Port -> 74LS47 Decoder
        D0        ->    A0
        D1        ->    A1
        D2        ->    A2
        D3        ->    A3
        D4        ->    VCC
        GND       ->    GND
        S7        ->    VCC
        S6        ->    GND
        S5        ->    GND
        S4        ->    GND
        S3        ->    Push Button Input (Active HIGH)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

// Parallel port base address
#define DATA_PORT 0x378
#define STATUS_PORT (DATA_PORT + 1)

// Note: In default state, status port's last 3 bits are internally HIGH.
// When the button is pressed, it pulls one bit LOW, resulting in 0x07.
// Make sure to check the default state of your status port.
#define BUTTON_PRESSED 0x07

// Binary mapping
unsigned char binaries[] = {
    0x10, // 0001 0000
    0x11, // 0001 0001
    0x12, // 0001 0010
    0x13, // 0001 0011
    0x14, // 0001 0100
    0x15, // 0001 0101
    0x16, // 0001 0110
    0x17, // 0001 0111
    0x18, // 0001 1000
    0x19  // 0001 1001
};

// Variable to store write data
unsigned char data, status;

int main()
{
    // Logging errors
    if (ioperm(DATA_PORT, 1, 1))
    {
        fprintf(stderr, "Access denied to %x\n", DATA_PORT), exit(1);
    }

    if (ioperm(STATUS_PORT, 1, 1))
    {
        fprintf(stderr, "Access denied to %x\n", STATUS_PORT), exit(1);
    }

    // Displaying each character
    int i = 0;
    while (1)
    {
        // Check button press (active LOW)
        status = inb(STATUS_PORT);
        printf("Ready for button press. \t Default STATUS PORT: %02X\n", status);
        if (status == BUTTON_PRESSED)
        {
            usleep(1000); // debounce delay
            if (inb(STATUS_PORT) == BUTTON_PRESSED)
            {
                // Select character
                data = binaries[i];

                // Write to the parallel port
                outb(data, DATA_PORT);

                // Increment the count
                i = (i + 1) % 10;
            }
        }
    }

    return 0;
}
