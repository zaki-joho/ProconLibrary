#!/bin/bash

cat FOLDERS| while read line
do
	cd $line
	for file in `find | grep -E "\.(c|h)pp$"`
	do
		echo $file
	done
	cd ../
done