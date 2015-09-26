/*
** myprintf.h for my_printf in /home/menich_a/rendu/PSU_2013_my_printf
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Nov 13 14:45:16 2013 menich_a
** Last update Sun Nov 17 19:01:44 2013 menich_a
*/

#ifndef		MYPRINTF_H_
# define	MYPRINTF_H_
# define	HEX		"0123456789ABCDEF"
# define	LOW_HEX		"0123456789abcdef"
# define	OCT		"01234567"

#include <stdarg.h>

typedef struct	s_fmt
{
  char		fmt;
  int		(*fptr)(va_list ap, unsigned int width);
}		g_fmt;

#endif /* !MYPRINTF_H_ */
