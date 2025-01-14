#!/bin/bash

echo clear cascemtorque ... 

if [ -d debug ]; then
echo 'deleting directory debug'
rm -r debug
fi

if [ -d release ]; then
echo 'deleting directory release'
rm -r release
fi

if [ -d ascemtorque_autogen ]; then
echo 'deleting directory ascemtorque_autogen'
rm -r ascemtorque_autogen
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

if [ -f ascemtorque_resource.rc ]; then
echo 'deleting file ascemtorque_resource.rc'
rm ascemtorque_resource.rc
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

if [ -f object_script.ascemtorque.Debug ]; then
echo 'deleting file object_script.ascemtorque.Debug'
rm object_script.ascemtorque.Debug
fi

if [ -f object_script.ascemtorque.Release ]; then
echo 'deleting file object_script.ascemtorque.Release'
rm object_script.ascemtorque.Release
fi

if [ -f Makefile ]; then
echo 'deleting file Makefile'
rm Makefile
fi

if [ -f ascemtorque.pro.user ]; then
echo 'deleting file ascemtorque.pro.user'
rm ascemtorque.pro.user
fi

if [ -f ascemtorque ]; then
echo 'deleting file ascemtorque'
rm ascemtorque
fi

if [ -f .qmake.stash ]; then
echo 'deleting .qmake.stash'
rm .qmake.stash
fi
#rm -r *.log
#rm -r *.tab

echo Complite

