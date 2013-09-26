/*
 * File:   main.cpp
 * Author: Piotr Brendel
 */

#include <iostream>

#include "ConvertCubeBitmapToCubeCoords.h"
#include "ConvertCWComplexBoundaryToKappaMap.h"

int main(int argc, char** argv)
{
    std::cout<<"Converting..."<<std::endl;
    //ConvertCWComplexBoundaryToKappaMap converter;
    //bool res = converter.Convert("boundaries.txt", "kappa_1.txt");
    ConvertCubeBitmapToCubeCoords converter;
    bool res = converter.Convert("bitmap.txt", "cubes.txt");
    if (res)
    {
        std::cout<<"Finished OK"<<std::endl;
    }
    else
    {
        std::cout<<"Failed"<<std::endl;
    }
    return 0;
}

