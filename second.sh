#!/usr/bin/env bash

set -e # exit on failure

[ ! -d "tmp/second/pbm" ] && mkdir -p "tmp/second/pbm"
[ ! -d "tmp/second/png" ] && mkdir -p "tmp/second/png"

for ruleNo in {65538..131073}
do
  echo "Running rule $ruleNo"

  ruleDir="rules/$ruleNo"
  CSVFile="$ruleDir/trials.csv"

  [ ! -d $ruleDir ] && mkdir -p $ruleDir
  [ -f $CSVFile ] && rm $CSVFile

  for trial in {1..10}
  do
    echo "Running trial $trial for rule $ruleNo"
    echo "Removing last images..."
    rm -rf tmp/second/pbm/*
    rm -rf tmp/second/png/*

    echo "Running simulation..."
    ./run $ruleNo second

    echo "Compressing frames..."
    pushd tmp/second/pbm > /dev/null
    mogrify -format png *.pbm
    mv *.png ../png/
    popd > /dev/null

    echo "Generating report for trial $trial..."
    echo -n "Trial $trial," >> $CSVFile
    ./generate.sh second >> $CSVFile
  done
done
