#!/bin/bash
## launch.sh for lemipc in /home/menich_a/rendu/PSU_2014_lemipc
## 
## Made by Anatole Menichetti
## Login   <menich_a@epitech.net>
## 
## Started on  Sat Mar  7 16:51:22 2015 Anatole Menichetti
## Last update Sat Mar  7 18:38:06 2015 Anatole Menichetti
##

tNbr="2"
pNbr="6"
mSize="20"
path="/"
gui="enable"

for i in "$@" 
do 
    if [ $i == "-t" ] || [ $i == "-p" ] || [ $i == "-m" ] || [ $i == "-h" ] || [ $i == "-d" ]
    then
	if [ $i == "-h" ]
	then
	    echo -e `cat man`
	    exit 0
	fi
	if [ $mCheck ]
	then
	    echo "lemipc: option" $mCheck "takes parameter. Use lemipc -h for help about usage."
	    exit 0
	fi
	mCheck=$i
    else
	if [ "$mCheck" == "" ]
	then
	    if [ $i == "-i" ]
	    then
		gui=""
	    else
		echo "lemipc: unknown option" $i "."
		exit 0
	    fi
	fi
	if [ "$mCheck" == "-d" ]
	then
	    path=$i
	fi
	if [ "$mCheck" == "-t" ]
	then
	    tNbr=$i
	fi
       	if [ "$mCheck" == "-p" ]
	then
	    pNbr=$i
	fi
	if [ "$mCheck" == "-m" ]
	then
	    mSize=$i
	fi
	mCheck=""
    fi
done

if [ $mCheck ]
then
    echo "lemipc: option" $mCheck "takes parameter. Use lemipc -h for help about usage."
    exit 0
fi

echo "Battle begun: use launch.sh -h for help about usage."

for t in `seq 1 $tNbr`
do
    for p in `seq 1 $pNbr`
    do
	./lemipc $t $mSize &
	if [ $gui ]
	then
	 ./gui &
	 gui=""
	fi
    done
done
