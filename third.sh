#!/usr/bin/env bash

set -e # exit on failure

[ ! -d "tmp/third/pbm" ] && mkdir -p "tmp/third/pbm"
[ ! -d "tmp/third/png" ] && mkdir -p "tmp/third/png"

for ruleNo in {131074..196608}
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
    rm -rf tmp/third/pbm/*
    rm -rf tmp/third/png/*

    echo "Running simulation..."
    ./run $ruleNo third

    echo "Compressing frames..."
    pushd tmp/third/pbm > /dev/null
    mogrify -format png *.pbm
    mv *.png ../png/
    popd > /dev/null

    echo "Generating report for trial $trial..."
    echo -n "Trial $trial," >> $CSVFile
    ./generate.sh third >> $CSVFile
  done
done
