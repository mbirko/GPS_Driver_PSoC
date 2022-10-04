
#include "coordinates.hpp"

class Navigation
{
private:
    

public: 

    // utillity methoeds 
    struct DD_coordinate DMStoDD(struct DMS_coordinate DMS) 
    {
        struct DD_coordinate temp; 

        temp.longitude_ = DMStoDD(
                DMS.longitude_.degree_,
                DMS.longitude_.minut_,
                DMS.longitude_.second_ );

        temp.latitude_ = DMStoDD(
                DMS.latitude_.degree_,
                DMS.latitude_.minut_,
                DMS.latitude_.second_ );
        return temp;
    }
    float DMStoDD(int degree, int minutes, int seconds)
    {
        /* 
            second comes in a hole number representing 0.xxxx of a minut.
            convert to seconds by multipling by 60 and deviding by 10^5
        */ 
        return static_cast<float>(degree + minutes / 60.0 + ((seconds*60.0)/100000.0)/3600.0 );

    }

     
};