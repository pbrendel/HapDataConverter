/*
 * File:   main.cpp
 * Author: Piotr Brendel
 */

#include <ctime>
#include <iostream>
#include <string>

#include "ConvertCubeBitmapToCubeCoords.h"
#include "ConvertCWComplexBoundaryToKappaMap.h"

enum ConversionType
{
    CT_Unknown,
    CT_Cubes,
    CT_Kappa,
};

ConversionType GetConversionType(const char *cmd)
{
    if (std::string(cmd) == std::string("cubes"))
    {
        return CT_Cubes;
    }
    if (std::string(cmd) == std::string("kappa"))
    {
        return CT_Kappa;
    }
    return CT_Unknown;
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cout<<"Usage program_name [cubes|kappa] input output"<<std::endl;
        return 1;
    }
    std::cout<<"Converting..."<<std::endl;
    bool res = false;
    time_t now = time(0);
    switch (GetConversionType(argv[1]))
    {
        case CT_Cubes:
            {
                ConvertCubeBitmapToCubeCoords converter;
                res = converter.Convert(argv[2], argv[3]);
            }
            break;
        case CT_Kappa:
            {
                ConvertCWComplexBoundaryToKappaMap converter;
                res = converter.Convert(argv[2], argv[3]);
            }
            break;
        default:
            std::cout<<"Error: unknown conversion type specified: "<<argv[1]<<std::endl;
            break;
    }
    if (!res)
    {
        std::cout<<"Failed"<<std::endl;
        return 1;
    }
    std::cout<<"Finished OK in "<<(time(0) - now)<<" seconds"<<std::endl;
    return 0;
}

