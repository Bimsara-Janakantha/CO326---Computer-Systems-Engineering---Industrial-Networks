#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

// Parallel port base address
#define DATA_PORT 0x378

// Port mapping
unsigned char segments[] = {
    0x01, // a
    0x02, // b
    0x04, // c
    0x08, // d
    0x10, // e
    0x20, // f
    0x40  // g
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
