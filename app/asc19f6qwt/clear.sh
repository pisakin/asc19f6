#!/bin/bash

echo clear cascemkalman ... 


if [ -d ascemkalman_autogen ]; then
echo 'deleting directory ascemkalman_autogen'
rm -r ascemkalman_autogen
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

if [ -f cmake_install.cmake ]; then
echo 'deleting file cmake_install.cmake'
rm cmake_install.cmake
fi


if [ -f CMakeCache.txt ]; then
echo 'deleting file CMakeCache.txt'
rm CMakeCache.txt
fi

if [ -f Makefile ]; then
echo 'deleting file Makefile'
rm Makefile
fi

if [ -f ascemkalman.pro.user ]; then
echo 'deleting file ascemkalman.pro.user'
rm ascemkalman.pro.user
fi

if [ -f ascemkalman ]; then
echo 'deleting file ascemkalman'
rm ascemkalman
fi

if [ -f .qmake.stash ]; then
echo 'deleting .qmake.stash'
rm .qmake.stash
fi
#rm -r *.log
#rm -r *.tab

echo Complite

