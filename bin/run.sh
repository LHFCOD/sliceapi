#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/root/workspace/bin
javac com/platform/util/ExtractFile.java
java com/platform/util/ExtractFile
