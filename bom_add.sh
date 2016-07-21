#!/bin/sh

# add UTF-8 BOM( bye order mark )
#    for Windows( Visual Studio )

# *.h, *.inc
# *.cxx, *.cpp, *.f90, *.F90

for file in `\find . -name '*.h' -o -name '*.inc' -o -name '*.cxx' -o -name '*.cpp' -o -name '*.f90' `; do
  # echo $file
  # file $file
  nkf --overwrite --oc=UTF-8-BOM $file
done

# check with bom
#  vi -b  file
#
#  header of file without bom
#    /*
#     * Polylib - Polygon Management Library
#
#  header of file with bom
#    <feff>/*
#     * Polylib - Polygon Management Library

