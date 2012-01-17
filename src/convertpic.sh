#!/bin/bash

for filename in tmp/*
do
   convert $filename -geometry 600x800 donepic/$filename.jpg
   rm $filename
done;