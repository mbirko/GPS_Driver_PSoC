
#ifndef COORDINATE_H
#define COORDINATE_H
#include "test_flags.hpp"
// defines allows testing...
#ifdef TESTING
    #ifdef X86 
        #ifdef lang_cpp
            #include <iostream>
        #endif // lang_cpp
        #ifdef lang_c
            #include <stdio.h>
        #endif // lang_c
    #endif // X86
    #ifdef PSOC
        #include <stdio.h> 
    #endif // PSOC 
#endif // TESTING 



struct DD_coordinate
{
    /**
     * @brief defualt Construct a new dd coordinate object, instanciate to 0
     * 
     */
    DD_coordinate() : 
        longitude_(0), 
        latitude_(0) 
    {}
    /**
     * @brief parameticed constructer a new dd coordinate object
     * 
     * @param lon longitude in float
     * @param lat latitude in float
     */
    DD_coordinate(float lat, float lon) :
        longitude_(lon), 
        latitude_(lat) 
    {

    }
    DD_coordinate(double lat, double lon) : 
        longitude_(lon),
        latitude_(lat)
    {

    }
    float longitude_;
    float latitude_;
};

struct DMS_coordinate_part
{
    /**
     * @brief Construct a new dms coordinate part object, instanciate to 0 
     * 
     */
    DMS_coordinate_part() : 
        degree_(0), minut_(0), second_(0) {}
    /**
     * @brief Construct a new dms coordinate part object
     * 
     * @param d degrees of longitude or latitude
     * @param m minutes of longitude or latitude 
     * @param s seconds of longitude or latitude
     */
    DMS_coordinate_part(int d, int m, int s) :
        degree_(d), minut_(m), second_(s) {}  

    int degree_;
    int minut_;
    int second_;
    
};
struct DMS_coordinate
{
    /** 
     * @brief defualt constructor of DMS_coordinate::DMS_coordinate
     * 
    */
    DMS_coordinate() : longitude_(), latitude_() {} 
    /** 
     * @brief parematiced constructor of DMS_coordinate::DMS_coordinate
     *
     * @param longi DMS_coordinate_part longitude
     * @param lat DMS_coordinate_part latitude
    */
    DMS_coordinate(DMS_coordinate_part longi, DMS_coordinate_part lat) : 
        longitude_(longi), latitude_(lat) {}

    /**
     * @brief set latitude of DMS_coordinate 
     * 
     * @param d numger of degrees 
     * @param m number of minutes 
     * @param s number of seconds 
    */
    void setLat(int d, int m, int s)
    {
        latitude_.degree_ = d;
        latitude_.minut_ = m;
        latitude_.second_ = s; 
    }
    /**
     * @brief set longitude of DMS_coordinate 
     * 
     * @param d numger of degrees 
     * @param m number of minutes 
     * @param s number of seconds 
    */
    void setLong(int d, int m, int s)
    {
        longitude_.degree_ = d;
        longitude_.minut_ = m;
        longitude_.second_ = s; 
    }
    struct DMS_coordinate_part longitude_;

    struct DMS_coordinate_part latitude_;
    /**
     * @brief Converts a DMS_coordinate to a DD_coordinate
     * 
     * @return struct DD_coordinate 
     */
    struct DD_coordinate dms_to_dd() 
    {
        struct DD_coordinate temp; 

        temp.longitude_ = dms_to_dd(
                longitude_.degree_,
                longitude_.minut_,
                longitude_.second_ );

        temp.latitude_ = dms_to_dd(
                latitude_.degree_,
                latitude_.minut_,
                latitude_.second_ );
        return temp;
    }
private: 
    /**
     * @brief converts part of DMS coordinates to part of DD_coordinate
     * 
     * @param degree longitude or latitude degress
     * @param minutes longitude or latitude minutes 
     * @param seconds longtitude or latitude seconds
     * @return float 
     */
    float dms_to_dd(int degree, int minutes, int seconds)
    {
        /* 
            second comes in a hole number representing 0.xxxx of a minut.
            convert to seconds by multipling by 60 and deviding by 10^5
        */ 
        return static_cast<float>(degree + minutes / 60.0 + ((seconds*60.0)/100000.0)/3600.0 );

    }
    
};


#ifdef TESTING  
    struct coordinate_printer{
        // if PSOC, paremterices construktor becomes only option
        #ifdef PSOC
            coordinate_printer(void (*uart_print)(const char *))
            {
                // assing debug uart print string pointer.
                this->uart_print = uart_print;
            }
            // member function pointer, used to point to uart used to debug
            void (*uart_print)(const char *);
        #endif
        void print(struct DD_coordinate DD) 
        {
            #ifdef X86
                #ifdef lang_c
                    printf("DD long: %f, lat: %f\n", DD.longitude_, DD.latitude_);
                #endif // lang_c
                #ifdef lang_cpp
                    std::cout   << "DD long: " << DD.longitude_ 
                                << " lat: " << DD.latitude_ << std::endl;
                #endif // lang_cpp
            #endif // X86
            #ifdef PSOC
                char buffer[256] = {0}; 
                snprintf(buffer, 256, "DD long: %f Lat: %f\n", DD.longitude_, DD.latitude_);

                uart_print(buffer);
            #endif
        }
        void print(struct DMS_coordinate DMS)
        {
            #ifdef X86
                #ifdef lang_c
                    printf("DMS long: %d deg %d min %d sec, lat: %d deg %d min %d sec\n", 
                            DMS.longitude_.degree_,
                            DMS.longitude_.minut_,
                            DMS.longitude_.second_,
                            DMS.latitude_.degree_,
                            DMS.latitude_.minut_,
                            DMS.latitude_.second_);
                #endif // lang_c
                #ifdef lang_cpp
                    std::cout   << "DMS long: " 
                                << "deg: " << DMS.longitude_.degree_ 
                                << " min: " << DMS.longitude_.minut_ 
                                << " sec: " << DMS.longitude_.second_
                                << " lat: "
                                << " deg: " << DMS.latitude_.degree_
                                << " min: " << DMS.latitude_.minut_
                                << " sec: " << DMS.latitude_.second_
                                << std::endl;
                #endif // lang_cpp
            #endif // X86
            #ifdef PSOC
                    char buffer[256] = {0};
                    snprintf(buffer, 256, "DMS long: %d deg %d min %d sec, lat: %d deg %d min %d sec\n", 
                            DMS.longitude_.degree_,
                            DMS.longitude_.minut_,
                            DMS.longitude_.second_,
                            DMS.latitude_.degree_,
                            DMS.latitude_.minut_,
                            DMS.latitude_.second_);
                    uart_print(buffer);
                    
            #endif 
        }
    };
    #endif
#endif