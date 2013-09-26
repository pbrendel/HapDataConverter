/*
 * File:   ConvertCWComplexBoundaryToKappaMap.cpp
 * Author: Piotr Brendel
 */

#include "ConvertCWComplexBoundaryToKappaMap.h"

#include <fstream>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

bool ConvertCWComplexBoundaryToKappaMap::Convert(const char* filenameIn,
                                                 const char* filenameOut)
{
    if (!ParseCWComplexBoundary(filenameIn))
    {
        std::cout<<"Error opening file: "<<filenameIn<<std::endl;
        return false;
    }
    std::cout<<filenameIn<<" - CW Complex boundary parsed"<<std::endl;
    if (!WriteKappaMap(filenameOut))
    {
        std::cout<<"Error opening file: "<<filenameIn<<std::endl;
        return false;
    }
    std::cout<<filenameOut<<" - Kappa map written"<<std::endl;
    return true;
}

bool ConvertCWComplexBoundaryToKappaMap::ParseCWComplexBoundary(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    enum LevelType
    {
        LT_Init = 0,
        LT_Global = 1,
        LT_Dim = 2,
        LT_Cell = 3,
    };

    size_t currentLevel = LT_Init;
    Cell currentCell;
    size_t currentDim = 0;
    size_t currentValue = 0;
    size_t cellsCountInCurrentDim = 0;

    while (!file.eof())
    {
        int c = file.get();
        if (c == '[')
        {
            currentLevel++;
        }
        else if (c == ']')
        {
            if (currentLevel == LT_Cell)
            {
                currentCell.push_back(currentValue);
                _cells.push_back(currentCell);
                currentValue = 0;
                currentCell.clear();
                cellsCountInCurrentDim++;
            }
            else if (currentLevel == LT_Dim)
            {
                _cellsCountByDim[currentDim] = cellsCountInCurrentDim;
                cellsCountInCurrentDim = 0;
                currentDim++;
            }
            currentLevel--;
        }
        else if (c == ',')
        {
            if (currentLevel == LT_Cell)
            {
                currentCell.push_back(currentValue);
                currentValue = 0;
            }
        }
        else if (c >= '0' && c <= '9')
        {
            currentValue = currentValue * 10 + (c - '0');
        }
    }
    file.close();
    return true;
}

bool ConvertCWComplexBoundaryToKappaMap::WriteKappaMap(const char* filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    std::map<size_t, size_t> cellsIndicesOffsets;
    size_t topDimension = _cellsCountByDim.size() - 1;

    file<<topDimension<<std::endl;
    for (int i = 0; i <= topDimension; i++)
    {
        file<<_cellsCountByDim[i]<<std::endl;
        cellsIndicesOffsets[i] = (i == 0) ? 0 : (cellsIndicesOffsets[i - 1] + _cellsCountByDim[i - 1]);
        std::cout<<"cells offset in dim "<<i<<" = "<<cellsIndicesOffsets[i]<<std::endl;
    }

    // Each cell is a sequence of numbers:
    // - first value is a length of boundary (n)
    // - next n values is a collection of indices to boundary cells
    // Cells are indexed from 1, so we need to shift index by 1.
    // Dimension of cell is equal to (number_of_values - 1) / 2
    // (we assume that source CW complex was made from cubical complex,
    // so there are 2 cells in boundary in each dimension).
    for (size_t index = _cellsCountByDim[0]; index < _cells.size(); index++)
    {
        Cell c = _cells[index];
        // writing only cells of dimension 1 and more
        if (c.size() < 3)
        {
            continue;
        }
        int dim = (c.size() - 1) / 2;
        int cellsOffset = cellsIndicesOffsets[dim - 1];
        Cell::iterator it = c.begin();
        // skipping first value (dimension)
        it++;
        for (int i = 0; i < dim; i++)
        {
            file<<index<<" "<<(*it - 1 + cellsOffset)<<" 1"<<std::endl;
            it++;
        }
        for (int i = 0; i < dim; i++)
        {
            file<<index<<" "<<(*it - 1 + cellsOffset)<<" -1"<<std::endl;
            it++;
        }
    }

    file.close();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
// eof
