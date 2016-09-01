#!/bin/sh
file="./build.sh"

if [ -r $file ]
then
   	echo "-- build the module"
   	make
	echo "-- build with success"
else
   echo "-- error"
fi