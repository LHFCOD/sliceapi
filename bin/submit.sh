#!/bin/bash

if [ -n "$1" ]; then
	msg=$1
else
	msg=debug
fi
git add .
git commit -m "$msg"

