#!/bin/bash

echo "Dependencies check..."

if brew ls --versions pkg-config > /dev/null; then
	echo "pkg-config found"
else
	echo "pkg-config missing, installing it with brew..."
	brew install pkg-config && brew link pkg-config
fi

if brew ls --versions libsndfile > /dev/null; then
	echo "libsndfile found"
else
	echo "libsndfile missing, installing it with brew..."
	brew install libsndfile && brew link libsndfile
fi

if brew ls --versions openal-soft > /dev/null; then
	echo "openal-soft found"
else
	echo "openal-soft missing, installing it with brew..."
	brew install openal-soft && brew link openal-soft
fi

if brew ls --versions libpng > /dev/null; then
	echo "libpng found"
else
	echo "libpng missing, installing it with brew..."
	brew install libpng && brew link libpng
fi

if brew ls --versions bzip2 > /dev/null; then
	echo "bzip2 found"
else
	echo "bzip2 missing, installing it with brew..."
	brew install bzip2 && brew link bzip2
fi

if ls stock/part1.bz2 stock/part2.bz2 stock/part3.bz2 stock/part4.bz2 2>/dev/null; then
	echo "Decompressing archive file..."
	bzip2 -d stock/part1.bz2 stock/part2.bz2 stock/part3.bz2 stock/part4.bz2
fi

a=0
b=0

if ls resources.archi 2>/dev/null; then
	exit
fi

echo "Decompressing archive"
for i in `ls -d1 stock/*`
do
	bzip2 -d $i
	if [ "$a" -eq "$b" ]; then
		cat ${i%.*} > resources.archi
	else
		cat ${i%.*} >> resources.archi
	fi
	a+=1
done

