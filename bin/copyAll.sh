#!/bin/bash
Target=test/libthrift-0.11.0.so
lib_array=`ldd $Target | grep -o "/.*" | grep -o "/.*/[^[:space:]]*"`
LibDir=/home/mi/project/slicePro/sliceapi/bin/test
for Variable in ${lib_array}
do
	    cp "$Variable" $LibDir
done
