#!/bin/bash

cd ~/apue

git pull

cd ~/apue/refreshTime

g++ refreshTime.cpp -o refreshTime

./refreshTime


git add refreshTime.txt

git commit -m "refresh time"

git push
