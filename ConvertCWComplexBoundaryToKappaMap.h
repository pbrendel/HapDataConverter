/*
 * File:   ConvertCWComplexBoundaryToKappaMap.h
 * Author: Piotr Brendel
 */

#ifndef CONVERTCWCOMPLEXBOUNDARYTOKAPPAMAP_H
#define	CONVERTCWCOMPLEXBOUNDARYTOKAPPAMAP_H

#include <map>
#include <vector>

using std::size_t;

// Converts data stored in HAP's CW complex' 'boundaries' property
// to the following format:
// top_dimension
// number_of_cells_for_dim_0
// number_of_cells_for_dim_1
// ...
// number_of_cells_for_dim_n
// kappa_map_entry_0
// kappa_map_entry_1
// ...
// kappa_map_entry_n

class ConvertCWComplexBoundaryToKappaMap
{

public:

    bool Convert(const char* filenameIn, const char* filenameOut);

private:

    bool ParseCWComplexBoundary(const char* filename);
    bool WriteKappaMap(const char* filename);

    typedef std::vector<size_t>  Cell;
    typedef std::vector<Cell>   Cells;

    Cells                       _cells;
    std::map<size_t, size_t>    _cellsCountByDim;
};

#endif	/* CONVERTCWCOMPLEXBOUNDARYTOKAPPAMAP_H */

