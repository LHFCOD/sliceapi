#!/bin/bash
LIB_QTDIR=/usr/lib/x86_64-linux-gnu
INC_QTDIR=/usr/include/x86_64-linux-gnu/qt5
LIB_TARGET=/root/workspace/bin
INC_TARGET=/root/workspace/include

if [ ! -d $LIB_TARGET ];then
	echo "not exist!"
	mkdir -p $LIB_TARGET
fi
if [ ! -d $INC_QTDIR ];then
	mkdir -p $INC_TARGET 
fi
cp $LIB_QTDIR/libQt5Core.so.5 $LIB_TARGET
cp $LIB_QTDIR/libQt5Gui.so.5 $LIB_TARGET
cp $LIB_QTDIR/libQt5Xml.so.5 $LIB_TARGET
cp -r $INC_QTDIR $INC_TARGET

