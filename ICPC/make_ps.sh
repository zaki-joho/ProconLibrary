#/#!/bin/bash

# format:
#     cat [path/to/file] >> [folder_name].hpp
# e.g.
#     cat Geometry/geometry.hpp >> Geometry.hpp

OPT="highlight=cpp --color --landscape --columns=2"
# format:
#     enscript $OPT -o [folder_name].ps [folder_name].hpp
# e.g.
#     enscript $OPT -o Geometry.ps Geometry.hpp
enscript $POST -o template.ps templace.cpp

# format:
#     rm -f [folder_name].hpp
# e.g.
#     rm -f Geometry.hpp
