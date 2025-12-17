/*
Auther: Janakantha S.M.B.G. (E/20/157)
Last Modified: 2025-12-17
Title: Count from 0 to 9 on a Seven Segment Display using Parallel Port with and a 74LS47 Decoder
Description: This program counts from 0 to 9 on a seven-segment display connected to a parallel port.
Note: Use a common anode seven-segment display.
Port Map:
    Parallel Port -> 74LS47 Decoder
        D0        ->    A0
        D1        ->    A1
        D2        ->    A2
        D3        ->    A3
        D4        ->    VCC
        GND       ->    GND
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

// Parallel port base address
#define DATA_PORT 0x378

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
        data = binaries[i];

        // Write to the parallel port
        outb(data, DATA_PORT);
        printf("Displaying: %d -> Input: %02X\n", i, data);

        // Wait 1 second
        sleep(1);

        // Increment the count
        i = (i + 1) % 10;
    }
}
