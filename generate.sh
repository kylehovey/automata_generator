#!/bin/bash

for file in `ls -L tmp/png/ | sort -V | grep "png"`; do
  echo -n "`stat -f%z tmp/png/$file`,"
done
echo
