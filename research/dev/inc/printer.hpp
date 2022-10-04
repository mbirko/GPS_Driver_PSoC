

#ifndef PRINTER_H
#define PRINTER_H


#include "../inc/test_flags.hpp"
#ifdef TESTING
    #ifdef X86 
        #ifdef lang_cpp
            #include <iostream>
            template <typename T>
            void print_number(const char * msg, T number, bool newline = false)
            {
                std::cout << msg << ": " << number << " ";
                if (newline) std::cout << std::endl;
            }
        #endif // lang_cpp
        #ifdef lang_c
            #include <stdio.h>
            print_number(const char * msg, int number);
            {
                printf("%s: %d",msg, number);
                return;
            }
            
        #endif // lang_c
    #endif // X86
    #ifdef PSOC
        #include <stdio.h> 
        void print_number(const char * msg, int number);
        {
            char buffer[256] = {0};
            snprintf(buffer, 256, "%s: %d\n", 
                        msg, number);
            uart_print(buffer);
        }
    #endif // PSOC 
#endif // TESTING 

#endif // PRINTER_H