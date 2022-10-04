
#ifndef PARSER_H
#define PARSER_H

#include <iostream>

#include "coordinates.hpp"
// define length of arrays to be allocated
#define GPS_MESSAGE_MAX_LENGTH 255
// define actual length of full message +1 
#define GPS_MESSAGE_LENGTH 56



class parser {
    public:
        enum  coord_pos { 
            longi_degree_10     = 7,
            longi_degree_1      = 8,
            longi_min_10        = 9,
            longi_min_1         = 10,
            longi_sec_10000     = 12,
            longi_sec_1000      = 13,
            longi_sec_100       = 14,
            longi_sec_10        = 15,
            longi_sec_1         = 16,
            lat_degree_100      = 20,
            lat_degree_10       = 21,
            lat_degree_1        = 22,
            lat_min_10          = 23,
            lat_min_1           = 24,
            lat_sec_10000       = 26,
            lat_sec_1000        = 27 ,
            lat_sec_100         = 28,
            lat_sec_10          = 29,
            lat_sec_1           = 30,
        } ;
        /* int array holding the pos of the coordinates */ 
        int cord_pos_indexed[19] = {
            longi_degree_10,
            longi_degree_1,
            longi_min_10,
            longi_min_1,
            longi_sec_10000,
            longi_sec_1000,
            longi_sec_100,
            longi_sec_10,
            longi_sec_1,
            lat_degree_100,
            lat_degree_10,
            lat_degree_1,
            lat_min_10,
            lat_min_1,
            lat_sec_10000,
            lat_sec_1000,
            lat_sec_100,
            lat_sec_10,
            lat_sec_1
        };
        struct DMS_coordinate parse_to_DMS(const char * msg)
        {
            /* ints for creating the DMS coordinate */ 

            int longi_degree,   longi_min,  longi_sec;
            int lat_degree,     lat_min,    lat_sec;
                longi_degree =  longi_min = longi_sec = 0;
                lat_degree   =  lat_min   = lat_sec = 0;

            // quicly grab the relevant chars from message
            char buffer[19];
            for (int i = 0; i < 19; ++i) 
            {
                buffer[i] = *(msg + cord_pos_indexed[i]);

            }
            /* convert the long and latitude based on buffer */ 
            longi_degree += char_to_digit(buffer[0], 10);
            longi_degree += char_to_digit(buffer[1], 1);
            longi_min +=    char_to_digit(buffer[2], 10);
            longi_min +=    char_to_digit(buffer[3], 1);
            longi_sec +=    char_to_digit(buffer[4], 10000);
            longi_sec +=    char_to_digit(buffer[5],1000);
            longi_sec +=    char_to_digit(buffer[6], 100);
            longi_sec +=    char_to_digit(buffer[7],10);
            longi_sec +=    char_to_digit(buffer[8], 1);
            /* the lat is alittle more detalied, with an extra degree */ 
            lat_degree +=   char_to_digit(buffer[9],100);
            lat_degree +=   char_to_digit(buffer[10],10);
            lat_degree +=   char_to_digit(buffer[11], 1);
            lat_min +=      char_to_digit(buffer[12],10);
            lat_min +=      char_to_digit(buffer[13], 1);
            lat_sec +=      char_to_digit(buffer[14],10000);
            lat_sec +=      char_to_digit(buffer[15],1000);
            lat_sec +=      char_to_digit(buffer[16],100);
            lat_sec +=      char_to_digit(buffer[17],10);
            lat_sec +=      char_to_digit(buffer[18], 1);
            /* return the created DMS */
            return DMS_coordinate( 
                        DMS_coordinate_part(
                            longi_degree, 
                            longi_min,
                            longi_sec),
                        DMS_coordinate_part(
                            lat_degree, 
                            lat_min, 
                            lat_sec));
        }
    private:

    int char_to_digit(char num, int place)
    {
        switch (num)
        {
            case ('0') : 
                return 0*place;
            break;
            case ('1') : 
                return 1*place;
            break;
            case ('2') : 
                return 2*place;
            break;
            case ('3') : 
                return 3*place ;
            break;
            case ('4') : 
                return 4*place;
            break;
            case ('5') : 
                return 5*place;
            break;
            case ('6') : 
                return 6*place;
            break;
            case ('7') : 
                return 7*place;
            break;
            case ('8') : 
                return 8*place;
            break;
            case ('9') : 
                return 9*place;
            break;
            default: 
                return 0;
            break;
        }
    }
};

#endif // PARSER_H