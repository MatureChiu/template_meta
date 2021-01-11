#!/bin/sh
make clean;
if [ "$1" != "" ]
then
	make all LOCAL_MODULE=$1;
else
	make all;
fi

#make 2>&1 |tee make.log;

