/*
** my.h for libmy in /home/menich_a/rendu/Piscine-C-include
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Oct 10 16:46:02 2013 menich_a
** Last update Sat Feb 15 11:41:34 2014 menich_a
*/

#ifndef MY_H_
# define MY_H_

int	my_strncmp(char *, char *, int);

int	my_find_in_tab(char **, char);

int	my_find_in_str(char *, char);

char	*my_find_in_env(char **, char *);

void	my_free_tab(char **);

void	my_putchar(char);

void	my_putstr(char*);

int	my_strlen(char*);

int	my_getnbr(char *);

#endif	/* !MY_H_ */
