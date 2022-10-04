#include <iostream>
#include "navigation.hpp"
#include "coordinates.hpp"
// define length of arrays to be allocated
#define GPS_MESSAGE_MAX_LENGTH 255
// define actual length of full message +1 
#define GPS_MESSAGE_LENGTH 56



class parser {
    public:
        enum  coord_pos { 
            longi_degree_10 = 7,
            longi_degree_1 = 8,
            longi_min_10 = 9,
            longi_min_1 = 10,
            longi_sec_10000 = 12,
            longi_sec_1000 = 13,
            longi_sec_100 = 14,
            longi_sec_10 = 15,
            longi_sec_1 = 16,
            lat_degree_100 = 20,
            lat_degree_10 = 21,
            lat_degree_1 = 22,
            lat_min_10 = 23,
            lat_min_1 = 24,
            lat_sec_10000 = 26,
            lat_sec_1000 = 27 ,
            lat_sec_100 = 28,
            lat_sec_10 = 29,
            lat_sec_1 = 30,
        } ;
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

            int longi_degree, longi_min, longi_sec;
            int lat_degree, lat_min, lat_sec;
            longi_degree = longi_min = longi_sec = 0;
            lat_degree = lat_min = lat_sec = 0;

            longi_degree += char_to_digit(msg[coord_pos::longi_degree_10], 10);
            longi_degree += char_to_digit(msg[coord_pos::longi_degree_1], 1);
            longi_min += char_to_digit(msg[coord_pos::longi_min_10], 10);
            longi_min += char_to_digit(msg[coord_pos::longi_min_1], 1);
            longi_sec += char_to_digit(msg[coord_pos::longi_sec_10000], 10000);
            longi_sec += char_to_digit(msg[coord_pos::longi_sec_1000],1000);
            longi_sec += char_to_digit(msg[coord_pos::longi_sec_100], 100);
            longi_sec += char_to_digit(msg[coord_pos::longi_sec_10],10);
            longi_sec += char_to_digit(msg[coord_pos::longi_sec_1], 1);
            
            lat_degree += char_to_digit(msg[coord_pos::lat_degree_10],10);
            lat_degree += char_to_digit(msg[coord_pos::lat_degree_1], 1);
            lat_min += char_to_digit(msg[coord_pos::lat_min_10],10);
            lat_min += char_to_digit(msg[coord_pos::lat_min_1], 1);
            lat_sec += char_to_digit(msg[coord_pos::lat_sec_10000],10000);
            lat_sec += char_to_digit(msg[coord_pos::lat_sec_1000],1000);
            lat_sec += char_to_digit(msg[coord_pos::lat_sec_100],100);
            lat_sec += char_to_digit(msg[coord_pos::lat_sec_10],10);
            lat_sec += char_to_digit(msg[coord_pos::lat_sec_1], 1);

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
                throw "invalid char";
            break;
        }
    }
};


int main ()
{
    char buffer[GPS_MESSAGE_LENGTH] = "$GNGLL,5610.36931,N,01011.45411,E,091804.00,A,A*7B\r";
    char * msg = buffer;
    parser p;
    coordinate_printer printer;
    DMS_coordinate DMS = p.parse_to_DMS(msg);
    printer.print(DMS);
    return 0;
}