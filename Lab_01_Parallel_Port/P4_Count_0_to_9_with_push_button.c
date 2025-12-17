#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

// Parallel port base address
#define DATA_PORT 0x378
#define STATUS_PORT (DATA_PORT + 1)

// Binary mapping
unsigned char binaries[] = {
    0x00, // 0000
    0x01, // 0001
    0x02, // 0010
    0x03, // 0011
    0x04, // 0100
    0x05, // 0101
    0x06, // 0110
    0x07, // 0111
    0x08, // 1000
    0x09  // 1001
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
        if (inb(STATUS_PORT) == 0x00)
        {
            usleep(1000); // debounce delay
            if (inb(STATUS_PORT) == 0x00)
            {
                // Select character
                data = binaries[i];

                // Write to the parallel port
                outb(data, DATA_PORT);

                // Increment the count
                i = (i > 8) ? 0 : i + 1;
            }
        }
    }

    return 0;
}
