#!/bin/bash

echo clear asc19f6gc ... 

if [ -d debug ]; then
echo 'deleting directory debug'
rm -r debug
fi

if [ -d release ]; then
echo 'deleting directory release'
rm -r release
fi

if [ -d asc19f6gc_autogen ]; then
echo 'deleting directory asc19f6gc_autogen'
rm -r asc19f6gc_autogen
fi

if [ -d autom4te ]; then
echo 'deleting directory autom4te'
rm -r autom4te
fi

if [ -d autom4te.cache ]; then
echo 'deleting directory autom4te.cache'
rm -r autom4te.cache
fi

if [ -d CMakeFiles ]; then
echo 'deleting directory CMakeFiles'
rm -r CMakeFiles
fi

if [ -d build ]; then
echo 'deleting directory build'
rm -r build
fi

if [ -d bin ]; then
echo 'deleting directory bin'
rm -r bin
fi

if [ -f asc19f6gc_resource.rc ]; then
echo 'deleting file asc19f6gc_resource.rc'
rm asc19f6gc_resource.rc
fi

if [ -f cmake_install.cmake ]; then
echo 'deleting file cmake_install.cmake'
rm cmake_install.cmake
fi


if [ -f CMakeCache.txt ]; then
echo 'deleting file CMakeCache.txt'
rm CMakeCache.txt
fi

if [ -f Makefile.Debug ]; then
echo 'deleting file Makefile.Debug'
rm Makefile.Debug
fi

if [ -f Makefile.Release ]; then
echo 'deleting file Makefile.Release'
rm Makefile.Release
fi

if [ -f object_script.asc19f6gc.Debug ]; then
echo 'deleting file object_script.asc19f6gc.Debug'
rm object_script.asc19f6gc.Debug
fi

if [ -f object_script.asc19f6gc.Release ]; then
echo 'deleting file object_script.asc19f6gc.Release'
rm object_script.asc19f6gc.Release
fi

if [ -f Makefile ]; then
echo 'deleting file Makefile'
rm Makefile
fi

if [ -f asc19f6gc.pro.user ]; then
echo 'deleting file asc19f6gc.pro.user'
rm asc19f6gc.pro.user
fi

if [ -f asc19f6gc ]; then
echo 'deleting file asc19f6gc'
rm asc19f6gc
fi

if [ -f .qmake.stash ]; then
echo 'deleting .qmake.stash'
rm .qmake.stash
fi
#rm -r *.log
#rm -r *.tab

echo Complite

