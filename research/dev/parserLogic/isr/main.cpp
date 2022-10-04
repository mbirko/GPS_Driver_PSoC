#include <iostream>
#include <string>
#include "../../inc/coordinates.hpp"
#include "../../inc/navigation.hpp"
#include "../../inc/parser.hpp"
#include "stdlib.h"

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

#define GPS_ESCAPE_CHAR 'r'

struct NEMA_GNGLL {
    int pos_weights[GPS_MESSAGE_LENGTH];

};
void interrubtRutine()
{

        char recived_uart_char = '\0';
        std::cin >> recived_uart_char;
        if ((header[current_message_pos] == recived_uart_char) || reciving_message)
        {
            
            *(message_buffer_ptr + current_message_pos) = recived_uart_char;
            // std::cout << "\e[0;32m" << recived_uart_char << "\e[0m";
            ++current_message_pos;  
            /* if the intre header is received, accept the rest of message */ 
            if (current_message_pos == 6)
            {
                std::cout << "\e[0;32m header found \e[0m" << std::endl;
                reciving_message = true; 
            }
            /* when sentinal is met, indicate message recived */ 
            if (recived_uart_char == GPS_ESCAPE_CHAR)
            {
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
            // std::cout << recived_uart_char;
        }
}
int main ()
{
    DMS_coordinate dms;
    for(int i = 0; i < 2000; ++i)
    {
        interrubtRutine();
        if (message_received)
        {
            std::cout << "received message" <<   std::endl; 
            std::cout << message_ptr << std::endl;
            
            message_received = false;
        }
    }
    std::cout << std::endl;
    return 0;
}

