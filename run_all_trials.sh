#!/usr/bin/env bash

set -e # exit on failure

[ ! -d "tmp/pbm" ] && mkdir -p "tmp/pbm"
[ ! -d "tmp/png" ] && mkdir -p "tmp/png"

for ruleNo in {1..262143}
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
    rm -rf tmp/pbm/*
    rm -rf tmp/png/*

    echo "Running simulation..."
    ./run $ruleNo

    echo "Compressing frames..."
    pushd tmp/pbm > /dev/null
    mogrify -format png *.pbm
    mv *.png ../png/
    popd > /dev/null

    echo "Generating report for trial $trial..."
    echo -n "Trial $trial," >> $CSVFile
    ./generate.sh >> $CSVFile
  done
done
