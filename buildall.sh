#!/bin/sh
set -e
mkdir -p build32reference
cd build32reference
../configure reference
make -j4 all test BLIS_ENABLE_DYNAMIC_BUILD=yes CC=i686-w64-mingw32-gcc CPICFLAGS=""
for i in reference dunnington sandybridge haswell piledriver carrizo bulldozer; do
  mkdir -p ../build64$i
  cd ../build64$i
  ../configure $i
  make -j4 all test BLIS_ENABLE_DYNAMIC_BUILD=yes CC=x86_64-w64-mingw32-gcc CPICFLAGS=""
done
