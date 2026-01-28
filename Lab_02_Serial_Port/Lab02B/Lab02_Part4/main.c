#include "mcc_generated_files/mcc.h"

char data;

/* Function to send a string over EUSART */
void send_string(const char *x)
{
    while (*x)
    {
        EUSART_Write(*x++);
    }
}

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    int delay = 500;

    // Startup messages
    send_string("Welcome to CO326 Lab3\r\n");
    __delay_ms(delay);
    send_string("Press 1 for Red, 2 for Yellow, 3 for Green...\r\n");

    while (1)
    {
        /* Check if data is available before reading */
        if (EUSART_DataReady)
        {
            data = EUSART_Read();

            /* Turn OFF all LEDs first */
            RED_SetLow();
            YELLOW_SetLow();
            GREEN_SetLow();

            /* Control LEDs based on received data */
            switch (data)
            {
                case '1':
                    RED_SetHigh();
                    break;

                case '2':
                    YELLOW_SetHigh();
                    break;

                case '3':
                    GREEN_SetHigh();
                    break;

                default:
                    break;
            }
        }
    }
}
