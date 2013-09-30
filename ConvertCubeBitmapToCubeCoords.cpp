/*
 * File:   ConvertCubeBitmapToCubeCoords.cpp
 * Author: Piotr Brendel
 */

#include "ConvertCubeBitmapToCubeCoords.h"

#include <fstream>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

bool ConvertCubeBitmapToCubeCoords::Convert(const char* filenameIn,
                                            const char* filenameOut)
{
    if (!ParseCubeBitmap(filenameIn))
    {
        std::cout<<"Error opening file: "<<filenameIn<<std::endl;
        return false;
    }
    std::cout<<filenameIn<<" - cube bitmap parsed"<<std::endl;
    if (!WriteCubeCoords(filenameOut))
    {
        std::cout<<"Error opening file: "<<filenameIn<<std::endl;
        return false;
    }
    std::cout<<filenameOut<<" - cube coords written"<<std::endl;
    return true;
}

bool ConvertCubeBitmapToCubeCoords::ParseCubeBitmap(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    int currentDim = -1;
    Cube currentCube;

    while (!file.eof())
    {
        int c = file.get();
        if (c == '[')
        {
            currentDim++;
            while (currentDim > static_cast<int>(currentCube.size()) - 1)
            {
                currentCube.push_back(0);
            }
            currentCube[currentDim] = 0;
        }
        else if (c == ']')
        {
            currentDim--;
        }
        else if (c == ',')
        {
            currentCube[currentDim]++;
        }
        else if (c == '1')
        {
            _cubes.push_back(currentCube);
        }
        else
        {
            continue;
        }
    }

    std::cout<<"parsed "<<_cubes.size()<<" cubes"<<std::endl;

    file.close();
    return true;
}

bool ConvertCubeBitmapToCubeCoords::WriteCubeCoords(const char* filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    for (Cubes::iterator it = _cubes.begin(); it != _cubes.end(); ++it)
    {
        for (Cube::iterator jt = it->begin(); jt != it->end(); jt++)
        {
            file<<*jt<<" ";
        }
        file<<std::endl;
    }

    file.close();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
// eof
