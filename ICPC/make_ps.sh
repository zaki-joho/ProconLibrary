#/#!/bin/bash

# format:
#     cat [path/to/file] >> [folder_name].hpp
# e.g.
#     cat Geometry/geometry.hpp >> Geometry.hpp
cat Geometry/geometry.hpp >> Geometry.hpp
cat Graph/graph.hpp >> Graph.hpp
cat Math/combination.hpp >> Math.hpp
cat Others/zaatsu.hpp >> Others.hpp
cat String/manachar.hpp >> String.hpp
cat Structure/monoid.hpp >> Structure.hpp

OPT="highlight=cpp --color --landscape --columns=2"
# format:
#     enscript $OPT -o [folder_name].ps [folder_name].hpp
# e.g.
#     enscript $OPT -o Geometry.ps Geometry.hpp
enscript $OPT -o Geometry.ps Geometry.hpp
enscript $OPT -o Graph.ps Graph.hpp
enscript $OPT -o Math.ps Math.hpp
enscript $OPT -o Others.ps Others.hpp
enscript $OPT -o String.ps String.hpp
enscript $OPT -o Structure.ps Structure.hpp
enscript $OPT -o template.ps templace.cpp

# format:
#     rm -f [folder_name].hpp
# e.g.
#     rm -f Geometry.hpp
rm -f Geometry.hpp
rm -f Graph.hpp
rm -f Math.hpp
rm -f Others.hpp
rm -f String.hpp
rm -f Structure.hpp
