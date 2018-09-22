#!/bin/bash
Target=libmds.so
lib_array=`ldd $Target | grep -o "/.*" | grep -o "/.*/[^[:space:]]*"`
LibDir=/root/workspace/bin
for Variable in ${lib_array}
do
	    cp "$Variable" $LibDir
done
cp -r /usr/lib/x86_64-linux-gnu/qt5/plugins/imageformats /root/workspace/bin
cp -r /usr/lib/x86_64-linux-gnu/qt5/plugins/platforms /root/workspace/bin
cp $Target /root/workspace/bin
