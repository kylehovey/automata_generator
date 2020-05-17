#!/usr/bin/env bash

set -e # exit on failure

[ ! -d "tmp/fourth/pbm" ] && mkdir -p "tmp/fourth/pbm"
[ ! -d "tmp/fourth/png" ] && mkdir -p "tmp/fourth/png"

for ruleNo in {196609..262143}
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
    rm -rf tmp/fourth/pbm/*
    rm -rf tmp/fourth/png/*

    echo "Running simulation..."
    ./run $ruleNo fourth

    echo "Compressing frames..."
    pushd tmp/fourth/pbm > /dev/null
    mogrify -format png *.pbm
    mv *.png ../png/
    popd > /dev/null

    echo "Generating report for trial $trial..."
    echo -n "Trial $trial," >> $CSVFile
    ./generate.sh fourth >> $CSVFile
  done
done
