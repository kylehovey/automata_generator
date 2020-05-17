#!/usr/bin/env bash

for file in `ls -L tmp/$1/png/ | sort -V | grep "png"`; do
  [[ "$OSTYPE" == "linux-gnu" ]] && echo -n "`stat --printf=%s tmp/$1/png/$file`,"
  [[ "$OSTYPE" == "darwin"* ]] && echo -n "`stat -f%z tmp/$1/png/$file`,"
done
echo
