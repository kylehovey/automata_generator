#!/usr/bin/env bash

set -e # exit on failure

[ ! -d "tmp/first/pbm" ] && mkdir -p "tmp/first/pbm"
[ ! -d "tmp/first/png" ] && mkdir -p "tmp/first/png"

for ruleNo in {1..65537}
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
    rm -rf tmp/first/pbm/*
    rm -rf tmp/first/png/*

    echo "Running simulation..."
    ./run $ruleNo first

    echo "Compressing frames..."
    pushd tmp/first/pbm > /dev/null
    mogrify -format png *.pbm
    mv *.png ../png/
    popd > /dev/null

    echo "Generating report for trial $trial..."
    echo -n "Trial $trial," >> $CSVFile
    ./generate.sh first >> $CSVFile
  done
done
