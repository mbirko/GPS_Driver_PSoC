
#ifndef COORDINATE_H
#define COORDINATE_H

// defines allows testing...
#define X86
#define TESTING
#define lang_cpp

#ifdef lang_cpp
    #include <iostream>
#endif // lang_cpp
#ifdef lang_c
    #include <stdio.h>
#endif // lang_c



#include "coordinates.hpp"
    struct DMS_coordinate_part
    {
        // defualt constructor 
        DMS_coordinate_part() : 
            degree_(0), minut_(0), second_(0) {}
        // param constructor 
        DMS_coordinate_part(int d, int m, int s) :
            degree_(d), minut_(m), second_(s) {}  

        int degree_;
        int minut_;
        int second_;
    };
    struct DMS_coordinate
    {
        DMS_coordinate() : longitude_(), latitude_() {} 
        DMS_coordinate(DMS_coordinate_part longi, DMS_coordinate_part lat) : 
            longitude_(longi), latitude_(lat) {}
        void setLat(int d, int m, int s)
        {
            latitude_.degree_ = d;
            latitude_.minut_ = m;
            latitude_.second_ = s; 
        }
        void setLong(int d, int m, int s)
        {
            longitude_.degree_ = d;
            longitude_.minut_ = m;
            longitude_.second_ = s; 
        }
        struct DMS_coordinate_part longitude_;

        struct DMS_coordinate_part latitude_;
    };

    struct DD_coordinate
    {
        float longitude_;
        float latitude_;
    };

    #ifdef TESTING
     
    struct coordinate_printer{
        void print(struct DD_coordinate DD) 
        {
            #ifdef X86
                #ifdef lang_c
                    printf("DD long: %f, lat: %f\n", DD.longitude_, DD.latitude_);
                #endif // lang_c
                #ifdef lang_cpp
                    std::cout   << "DD long: " << DD.longitude_ 
                                << "DD lat: " << DD.latitude_ << std::endl;
                #endif // lang_cpp
            #endif // X86
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
        }
    };
    #endif
#endif