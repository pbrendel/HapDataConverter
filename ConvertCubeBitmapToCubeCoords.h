/*
 * File:   ConvertCubeBitmapToCubeCoords.h
 * Author: Piotr Brendel
 */

#ifndef CONVERTCUBEBITMAPTOCUBECOORDS_H
#define	CONVERTCUBEBITMAPTOCUBECOORDS_H

#include <map>
#include <vector>

using std::size_t;

// Converts data stored in HAP's cubical complex' 'binaryArray' property
// to the following format:
// cube_0
// cube_1
// ...
// cube_n
// where each cube is a list of its coords separated by spaces

class ConvertCubeBitmapToCubeCoords
{

public:

    bool Convert(const char* filenameIn, const char* filenameOut);

private:

    bool ParseCubeBitmap(const char* filename);
    bool WriteCubeCoords(const char* filename);

    typedef std::vector<size_t> Cube;
    typedef std::vector<Cube>   Cubes;

    Cubes                       _cubes;
};

#endif	/* CONVERTCUBEBITMAPTOCUBECOORDS_H */

