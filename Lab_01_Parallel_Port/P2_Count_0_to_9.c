/*
Auther: Janakantha S.M.B.G. (E/20/157)
Last Modified: 2025-12-17
Title: Count from 0 to 9 on a Seven Segment Display using Parallel Port
Description: This program counts from 0 to 9 on a seven-segment display connected to a parallel port.
Note: Use a common anode seven-segment display.
Port Map:
    D0 -> a
    D1 -> b
    D2 -> c
    D3 -> d
    D4 -> e
    D5 -> f
    D6 -> g
    D7 -> Common pin (Always HIGH)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

// Parallel port base address
#define DATA_PORT 0x378

// Character mapping
unsigned char characters[] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};
// Reference: https://www.electronicsforu.com/resources/7-segment-display-pinout-understanding

// Variable to store write data
unsigned char data;

void main()
{
    // Logging errors
    if (ioperm(DATA_PORT, 1, 1))
    {
        fprintf(stderr, "Access denied to %x\n", DATA_PORT), exit(1);
    }

    // Displaying each character
    int i = 0;
    while (1)
    {
        // Select character
        data = characters[i];

        // Write to the parallel port
        outb(data, DATA_PORT);
        printf("Displaying: %d -> Hex: %02X\n", i, data);

        // Wait 1 second
        sleep(1);

        // Increment the count
        i = (i + 1) % 10;
    }
}
