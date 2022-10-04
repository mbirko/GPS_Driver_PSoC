#include "../inc/coordinates.hpp"
#include "../inc/parser.hpp"
#include "../inc/navigation.hpp"
#include "../inc/test_flags.hpp"




int main(int argc, char ** argv)
{
    print_number("Test application started", 1, true);

    int direction = 450;
    Navigation nav;

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
    for (int i = 0; i < sizeof(targets) / sizeof(targets[0]); i++)
    {
        nav.set_target(targets[i]);
        nav.cal_errors();
        print_number<int>("tgt", i+1);
        nav.print();
    }
    print_number("boat dir", direction/10);

    return 0;
}