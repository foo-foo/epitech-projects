#!/bin/bash

n=11
m=101

while test $n != $m
do
echo $n
./creator $n > ../Maps/zMap$n
n=$(($n + 2))
done
