
#include "Coordinates.hpp"
#include <math.h>
#include <cmath>
#include <stdint.h>
#include "test_flags.hpp"

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
const static float LON_UNIT =  62392.61751; // 1.112185;
const static float LAT_UNIT = 111341.98121; // 1.771704;
const static float PI = 3.141592653589793;

class Navigation
{
private:
    DD_coordinate target_;
    struct boat_position : public DD_coordinate {
        boat_position() : DD_coordinate() 
        {

        } 
        int direction_;
    };
    boat_position postion_;
    float distance_to_target;
    float angle_to_target;
    int16_t trig_degree;
    float delta_lat_; 
    float delta_lon_;

    void distance_error()
    {
        float delta_lat_m = delta_lat_ * LAT_UNIT;
        float delta_lon_m = delta_lon_ * LON_UNIT;

        distance_to_target = sqrt((delta_lat_m * delta_lat_m) + (delta_lon_m * delta_lon_m));  
    }
    void angle_error() 
    {
        trig_degree = static_cast<int16_t>((atan2f(delta_lon_, delta_lat_) * 57.29578)*10);        

        uint16_t gps_degree = 3600-((trig_degree-900)%3600);
        int16_t raw_angle_to_target = postion_.direction_ - gps_degree;
        if (raw_angle_to_target > 1800)
        {
            angle_to_target = raw_angle_to_target - 3600;
        }
        else if (raw_angle_to_target < -180)
        {
            angle_to_target = raw_angle_to_target + 3600;
        }
        else 
        {
            angle_to_target = raw_angle_to_target;
        }

    }
public: 
    Navigation() : target_(), postion_()
    {
        distance_to_target = 0;
        angle_to_target = 0;
        delta_lat_ = 0;
        delta_lon_ = 0;
        #ifdef TESTING
            #ifdef PSOC
                this->uart_print = nullptr;
            #endif //PSOC
        #endif // testing 
    }
    #ifdef TESTING
        #ifdef PSOC
            Navigation(void (*uart_print)(const char*)) : target_(), postion_()
            {
                distance_to_target = 0;
                angle_to_target = 0;
                delta_lat_ = 0;
                delta_lon_ = 0;
                this->uart_print = uart_print;
            }
            void (*uart_print)(const char*);
            #endif //PSOC
        #endif // testing 
    
    void set_target(const DD_coordinate target)
    {
        target_ = target;
    }
    void set_postion(const DD_coordinate postion, int direction)
    {
        postion_.latitude_ = postion.latitude_;
        postion_.longitude_ = postion.longitude_;        
        postion_.direction_ = direction;

    }
    void cal_errors()
    {

        delta_lat_ = (target_.latitude_ - postion_.latitude_);
        delta_lon_ = (target_.longitude_ - postion_.longitude_);
        distance_error();
        angle_error();

        return;
    }
    // utillity methoeds 
    #ifdef TESTING
    #ifdef X86 
        #ifdef lang_cpp
            void print()
            {
                std::cout << "distance: " << distance_to_target << " tri ang: " << trig_degree/10 << " ang from dir: " << angle_to_target/10 << std::endl;
            }
        #endif // lang_cpp
        #ifdef lang_c
            #include <stdio.h>
        #endif // lang_c
    #endif // X86
    #ifdef PSOC
        void print()
        {
            char buffer[256] = {0}; 
            snprintf(buffer, 256, "Distance: %.2f tri ang: %d ang from dir: %.2f \n",
                distance_to_target,
                trig_degree/10, 
                angle_to_target/10);
            uart_print(buffer);
        }
        #include <stdio.h> 
    #endif // PSOC 
#endif // TESTING 
     
};