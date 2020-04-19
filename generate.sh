#!/usr/bin/env bash

for file in `ls -L tmp/png/ | sort -V | grep "png"`; do
  [[ "$OSTYPE" == "linux-gnu" ]] && echo -n "`stat --printf=%s tmp/png/$file`,"
  [[ "$OSTYPE" == "darwin"* ]] && echo -n "`stat -f%z tmp/png/$file`,"
done
echo
