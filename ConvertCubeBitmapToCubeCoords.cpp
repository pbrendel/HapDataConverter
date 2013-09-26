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


    while (!file.eof())
    {
        int c = file.get();
//        if (c == '[')
//        {
//            currentLevel++;
//        }
//        else if (c == ']')
//        {
//            if (currentLevel == LT_Cell)
//            {
//                currentCell.push_back(currentValue);
//                _cells.push_back(currentCell);
//                currentValue = 0;
//                currentCell.clear();
//                cellsCountInCurrentDim++;
//            }
//            else if (currentLevel == LT_Dim)
//            {
//                _cellsCountByDim[currentDim] = cellsCountInCurrentDim;
//                cellsCountInCurrentDim = 0;
//                currentDim++;
//            }
//            currentLevel--;
//        }
//        else if (c == ',')
//        {
//            if (currentLevel == LT_Cell)
//            {
//                currentCell.push_back(currentValue);
//                currentValue = 0;
//            }
//        }
//        else if (c >= '0' && c <= '9')
//        {
//            currentValue = currentValue * 10 + (c - '0');
//        }
//        else
//        {
//            continue;
//        }
    }
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


    file.close();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
// eof
