


#include <iostream>
#include <fstream>


int main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./main filename" << std::endl;
        return 0;
    }
    std::ifstream input_stream(argv[1]);
    std::cout << std::endl;
    if (input_stream)
    {
        input_stream.seekg(0, input_stream.end);
        int len = input_stream.tellg();
        input_stream.seekg(0, input_stream.beg);
        for (int i = 0; i < len; i++)
        {
            char buffer[2] = { 0 };
            input_stream.read(buffer,1); 
            std::cout << buffer;
        }

        input_stream.close();
    }
    return 0;
}