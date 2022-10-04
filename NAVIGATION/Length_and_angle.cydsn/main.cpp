/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "test_flags.hpp"

extern "C" { 
    #include "project.h"   
}
/* includes */ 
#include "coordinates.hpp"
#include "navigation.hpp"
#include "parser.hpp"
#include <stdint.h>
#include <stdio.h>

// define length of arrays to be allocated
#define GPS_MESSAGE_MAX_LENGTH 255
// define actual length of full message +1 
#define GPS_MESSAGE_LENGTH 56

// global variables
bool message_received;
char message_buffer[GPS_MESSAGE_MAX_LENGTH] = {0};
char message[GPS_MESSAGE_MAX_LENGTH] = {0};
char *message_buffer_ptr = message_buffer; 
char *message_ptr = message;
uint8_t current_message_pos = 0;
static const char * header = {"$GNGLL"};
static bool reciving_message = false;

#define GPS_ESCAPE_CHAR 'E'

CY_ISR_PROTO (GPS_rx_handler);
CY_ISR (GPS_rx_handler)
{
    uint8_t numberOfBytes = UART_GPS_GetRxBufferSize();
    for (uint8_t i = 0; i < numberOfBytes; ++i)
    {
        char recived_uart_char = UART_GPS_GetChar();

        if ((header[current_message_pos] == recived_uart_char) || reciving_message)
        {
            
            *(message_buffer_ptr + current_message_pos) = recived_uart_char;
            #ifdef TESTING
                #ifdef X86
                    // std::cout << "\e[0;32m" << recived_uart_char << "\e[0m";
                #endif
            #endif
            ++current_message_pos;  
            /* if the intre header is received, accept the rest of message */ 
            if (current_message_pos == 6)
            {
                #ifdef TESTING
                    #ifdef X86 
                        std::cout << "\e[0;32m header found \e[0m" << std::endl;
                    #endif
                    #ifdef PSOC
                        UART_PC_PutString("header found\r\n");
                    #endif
                #endif
                reciving_message = true; 
            }
            /* when sentinal is met, indicate message recived */ 
            if (recived_uart_char == GPS_ESCAPE_CHAR)
            {
                 
                #ifdef TESTING
                    #ifdef X86 
                        std::cout << "esc found" << std::endl;
                    #endif
                    #ifdef PSOC
                        UART_PC_PutString("escpae found\n");
                    #endif
                #endif
                /* 
                    instead of copying loop with a itrating loop, 
                    the two pointers are simply interchaned.
                    THis allows for one message to be passed one, 
                    while accepting the next one write away.
                */
                char *temp = message_ptr;
                message_ptr = message_buffer;
                message_buffer_ptr = temp;

                /* stop recieving the message */
                reciving_message = false;
                /* indicate that message is recived */ 
                message_received = true;
                /* reset message postion for next message */ 
                current_message_pos = 0;
            }
            /* if nosentinal is met, reset */
            if (current_message_pos == GPS_MESSAGE_LENGTH)
            {
                reciving_message = false;
                current_message_pos = 0;
            }

        }
        else
        {
            /* when a char that differ from header is met, reset */ 
            current_message_pos = 0;
            #ifdef TESTING
                #ifdef X86
                    // std::cout << recived_uart_char;
                #endif
            #endif
        }
    }
}
void test_length_n_angle()
{
    
    int direction = 450;
    Navigation nav(&UART_PC_PutString);

    DD_coordinate positon(56.144105, 10.125220);
    nav.set_postion(positon, direction);

    DD_coordinate targets[8] = {
               DD_coordinate(56.145462, 10.125252),
               DD_coordinate(56.145026, 10.126647),
               DD_coordinate(56.144392, 10.126958),
               DD_coordinate(56.143525, 10.126121),
               DD_coordinate(56.143136, 10.124308),
               DD_coordinate(56.143566, 10.122709),
               DD_coordinate(56.144708, 10.122130),
               DD_coordinate(56.145306, 10.122860)};
    for (uint8_t i = 0; i < sizeof(targets) / sizeof(targets[0]); i++)
    {
        nav.set_target(targets[i]);
        nav.cal_errors();
        char buffer[10] = {0};
        snprintf(buffer, 10, "tgt: %d", i);
        UART_PC_PutString(buffer);
        nav.print();
    }
}

void PC_char_recived_handeler (char msg)
{
    switch (msg)
    {
    /* Toggle reciving GPS signal */ 
    case 'q':
        /* code */
        break;
    /* test the calculation of angles and  distantes */ 
    case 'w':
        test_length_n_angle();
        break;
    default:
        UART_PC_PutChar(msg);
        break;
    }
}
CY_ISR_PROTO (PC_rx_handler);
CY_ISR (PC_rx_handler)
{ 
    uint8_t numberOfBytes = UART_PC_GetRxBufferSize();
    for (uint8_t i = 0; i < numberOfBytes; ++i)
    {
        PC_char_recived_handeler(UART_PC_GetChar());
    } 
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    // enable debug uart 
    isr_PC_StartEx(PC_rx_handler);
    // enable GPS uart
   // isr_GPS_StartEx(GPS_rx_handler);
    // start uarts 
    UART_PC_Start();
    // UART_GPS_Start();
    UART_PC_PutString("\r\napp started\r\n");


    DMS_coordinate dms;
    DD_coordinate dd; 
    parser p;
    coordinate_printer printer(&UART_PC_PutString);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        if (message_received)
        {
            #ifdef TESTING
                #ifdef X86
                    std::cout << "received message" <<   std::endl; 
                    std::cout << message_ptr << std::endl;
                #endif
                #ifdef PSOC
                    UART_PC_PutString("received message\r\n");
                #endif
            #endif

            dms = p.parse_to_DMS(message_ptr);
            printer.print(dms); 
            dd = dms.dms_to_dd();
            printer.print(dd);
            message_received = false;
        }
    }
}

/* [] END OF FILE */
