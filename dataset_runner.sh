#!/usr/bin/env sh

if [ "$1" == "--save" ]
then
	save=true
	shift
fi

[ -f "$1" ] || exit
[ -z "$2" ] && datasets="a b c d e" || datasets="$2"

for dataset_letter in $datasets
do
	ln -sf datasets/"$dataset_letter".h dataset.h
	g++ "$1"

	if [ -z "$save" ]
	then
		./a.out
	else
		./a.out > "$1"."$dataset_letter".solution
	fi
done
