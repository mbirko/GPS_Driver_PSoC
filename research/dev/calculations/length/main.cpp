#include "../../inc/coordinates.hpp"
#include "../../inc/navigation.hpp"
#include "../../inc/parser.hpp"

#include <iostream>

int main (int argc, char** argv)
{


    DD_coordinate postion, target;
    target.latitude_ = 2.0;
    target.longitude_ = 2.0;

    coordinate_printer printer; 
    printer.print(postion);
    printer.print(target);

    
    return 0;


}