#!/bin/sh
set -e
mkdir -p build32reference
cd build32reference
../configure reference
make -j4 BLIS_ENABLE_DYNAMIC_BUILD=yes CC=i686-w64-mingw32-gcc CPICFLAGS=""
for i in reference dunnington sandybridge haswell piledriver carrizo bulldozer; do
  mkdir -p ../build64$i
  cd ../build64$i
  ../configure $i
  make -j4 BLIS_ENABLE_DYNAMIC_BUILD=yes CC=x86_64-w64-mingw32-gcc CPICFLAGS=""
done
cd ../build32reference
cp /usr/i686-w64-mingw32/sys-root/mingw/bin/lib*.dll .
make -j4 test BLIS_ENABLE_DYNAMIC_BUILD=yes CC=i686-w64-mingw32-gcc CPICFLAGS=""
for i in reference dunnington sandybridge haswell piledriver carrizo bulldozer; do
  cd ../build64$i
  cp /usr/x86_64-w64-mingw32/sys-root/mingw/bin/lib*.dll .
  make -j4 test BLIS_ENABLE_DYNAMIC_BUILD=yes CC=x86_64-w64-mingw32-gcc CPICFLAGS=""
done
