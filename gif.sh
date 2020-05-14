#!/usr/bin/env bash

set -e # exit on failure

[ ! -d "tmp/pbm" ] && mkdir -p "tmp/pbm"
[ ! -d "tmp/png" ] && mkdir -p "tmp/png"

rm -rf tmp/pbm/*
rm -rf tmp/png/*

echo "Running simulation..."
./run

echo "Compressing frames..."
pushd tmp/pbm > /dev/null
mogrify -format png *.pbm
mv *.png ../png/
popd > /dev/null

echo "Creating gif..."
pushd tmp/png > /dev/null
convert -delay 10 -loop 1 {0..254}.png ca.gif
popd > /dev/null
mv tmp/png/ca.gif ./
