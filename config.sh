#!/bin/bash

for i in {1..9}
do
    rm -rf level$i
    mkdir level$i
    cp level0/Readme.md level$i
    touch level$i/flag
    touch level$i/source
    touch level$i/Information.png
    mkdir level$i/Resources
done
