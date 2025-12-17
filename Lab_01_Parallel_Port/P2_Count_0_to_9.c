#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

// Parallel port base address
#define DATA_PORT 0x378

// Character mapping
unsigned char[] characters = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x67  // 9
};
// Reference: https://hosteng.com/dmdhelp/content/instruction_set/SEG_Hex_BCD_to_7_Segment_Display.htm

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

        // Wait 1 second
        sleep(1);

        // Increment the count
        i = (i > 8) ? 0 : i + 1;
    }
}
