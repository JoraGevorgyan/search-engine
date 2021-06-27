#!/bin/bash

echo ... install packages ...

apt-get update
i='apt-get install'
$i g++
$i cmake
$i make
$i mysql-client
$i mysql-server
$i mysql-shell
$i libcurlpp-dev
$i libgumbo-dev
$i libmysql++-dev
$i libcpprest-dev
$i libgtest-dev
$i nlohmann-json3-dev

echo ... done!
echo ... creating database schema ...

#### this code part will be complete in future

echo ... done!
echo ... building components ...

mkdir -p bin/{Crawler,Search,UI} || exit

echo ... build Crawler ...
cd ./bin/Craler || exit
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" ../../Crawler/ || exit
make -j 4 || exit

echo ... build Search ...
cd ../Search || exit
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" ../../Search/ || exit
make -j 4 || exit

echo ... build UI ...
cd ../UI || exit
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" ../../UI/ || exit
make -j 4 || exit

# copy binaries into bin dir for easily running
find .. -iname *run \( ! -name . \) -exec bash -c "cp '{}' ../" \;

echo ready for run
