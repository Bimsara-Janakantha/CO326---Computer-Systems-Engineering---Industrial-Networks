/*
Auther: Janakantha S.M.B.G. (E/20/157)
Last Modified: 2025-12-17
Title: Lighting up individual segments in a seven-segment display
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

// Port mapping
unsigned char segments[] = {
    0xFE, // a
    0xFD, // b
    0xFB, // c
    0xF7, // d
    0xEF, // e
    0xDF, // f
    0xBF  // g
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

    // Lighting each segment individually
    for (int i = 0; i < 7; i++)
    {
        // Select segment
        data = segments[i];

        // Write to the parallel port
        outb(data, DATA_PORT);

        // Wait 1 second
        sleep(1);
    }

    // Turn OFF all segments
    data = 0x00;
    outb(data, DATA_PORT);

    return 0;
}
