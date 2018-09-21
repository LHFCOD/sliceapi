#!/bin/bash
for file in /home/mi/project/slicePro/sliceapi/bin/test/*
do
echo $file
patchelf --ser-rpath '$ORIGIN' $file
done
