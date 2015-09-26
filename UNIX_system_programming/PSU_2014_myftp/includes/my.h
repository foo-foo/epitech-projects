/*
** my.h for myftp in /home/menich_a/rendu/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Mar 12 13:04:56 2015 Anatole Menichetti
** Last update Thu Mar 26 11:29:16 2015 Anatole Menichetti
*/

#ifndef MY_H_
# define MY_H_

int	putstr(char *);

int	fputstr(int, char *);

void	*my_free(void *);

char	*my_get_str(int);

int	my_cmdcmp(char *, char *);

#endif /* !MY_H_ */
