#!/bin/bash

 if [ $# -ne 2 ]; then
    echo "Usage: sh create_packages.sh VERSION DESTINATION_PATH "
    echo "Example: sh create_packages.sh 0.0.1 . "
    exit
 fi


path="$PWD"
cd "$2"

echo "Downloading last SVN..."

svn checkout https://forja.rediris.es/svn/csl2-pfootball/trunk/ProjectFootball
cd ProjectFootball && find . -name .svn -print0 | xargs -0 rm -rf
rm -rf .settings
rm .cproject
rm .project
cd ..

echo "Making directories..."
cp -R ProjectFootball ProjectFootball-$1-src
cp -R ProjectFootball ProjectFootball-$1
mkdir ProjectFootball-$1-Win32
cp -R ProjectFootball/data ProjectFootball-$1-Win32/data

echo "Compiling..."
cd $path
cp -R ../../../Release "$2/ProjectFootball-$1-src"

cd "$2/ProjectFootball-$1-src/Release"
make clean
make all
cp ./ProjectFootball ../../ProjectFootball-$1
make clean

echo "Cleaning directories..."
cd ../../ProjectFootball-$1
rm -rf src
rm -rf doc
rm build.sh

echo "Making bz2 packages..."
cd ..
tar -cjvf ProjectFootball-$1-src.tar.bz2 ProjectFootball-$1-src
tar -cjvf ProjectFootball-$1.tar.bz2 ProjectFootball-$1
rm -rf ProjectFootball-$1-src
rm -rf ProjectFootball-$1
rm -rf ProjectFootball
echo "Packages creation process finished"