#!/bin/sh

if test -d all-build
then
	rm -rf all-build
fi

if test -d bin
then
	rm -rf source/data/color.data
	cp bin/color.data source/data/color.data 
	rm -rf bin
fi
###############fix ok
