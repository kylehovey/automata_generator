#!/usr/bin/env bash

set -e # exit on failure

[ ! -d "tmp/pbm" ] && mkdir -p "tmp/pbm"
[ ! -d "tmp/png" ] && mkdir -p "tmp/png"

[ -f "out.csv" ] && rm out.csv

for trial in {1..10}
do
  echo "Running trial $trial"
  echo "Removing last images..."
  rm -rf tmp/pbm/*
  rm -rf tmp/png/*

  echo "Running simulation..."
  ./run

  echo "Compressing frames..."
  pushd tmp/pbm > /dev/null
  mogrify -format png *.pbm
  mv *.png ../png/
  popd > /dev/null

  echo "Generating report for trial $trial..."
  echo -n "Trial $trial," >> out.csv
  ./generate.sh >> out.csv
done
