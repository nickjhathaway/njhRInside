#!/usr/bin/env bash


#check args
if [ $# -ne 1 ]; then
	echo Need two arguments 
	echo "1) unit directory"
	echo "runUnitTest.sh [TEST_DIR]"
exit
fi

cd $1
make 
for f in bin/*
do
	$f
done
