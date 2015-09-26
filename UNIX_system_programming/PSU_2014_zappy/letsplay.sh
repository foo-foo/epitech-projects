#!/bin/sh
## launch.sh for  in /home/menich_a/rendu/zappy/client_zappy
## 
## Made by Anatole Menichetti
## Login   <menich_a@epitech.net>
## 
## Started on  Thu Jun 18 00:01:40 2015 Anatole Menichetti
## Last update Sun Jul  5 12:03:22 2015 Francois Rosain
##

if test $# != 3
then
    echo -e "\033[31musage: launch.sh nbr_clients team_name port\033[0m"
    exit 1
fi

for i in `seq 1 $1`
do ./zappy_ai -n $2 -p $3 &
done

echo -e "\033[32mClients launched. You can look at logs files in logs directory\033[0m"
exit 0
