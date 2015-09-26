/*
** my_printf.c for my_printf in /home/menich_a/rendu/PSU_2013_my_printf
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Nov 11 10:47:31 2013 menich_a
** Last update Fri Nov 15 16:18:06 2013 menich_a
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "myprintf.h"
#include "my.h"

/*
**	printf %b et %q a gerer ? page internet ouverte (wiki.bash-hackers.org)
**	gerer cas ou 2 % de suite %%
**	printf %zdz = %d ?
**	printf %25d = printf 15 espaces, nombre de 10 chiffres ?
**	printf %       _d = printf %d ?
*/

static const g_fmt	fmt_tab[11] =
  {
    {'S', &printf_unprintable_string},
    {'b', &printf_unsigned_binary},
    {'x', &printf_low_unsigned_hex},
    {'X', &printf_unsigned_hex},
    {'u', &printf_unsigned_int},
    {'o', &printf_unsigned_oct},
    {'p', &printf_pointer},
    {'s', &printf_string},
    {'c', &printf_char},
    {'d', &printf_int},
    {'i', &printf_int},
  };

int		find_fmt(va_list ap, char *format, unsigned int i, unsigned int width)
{
  int		j;
  int		check;

  j = 0;
  check = 0;
  while (format[i] != fmt_tab[j].fmt && j < 11)
    j = j + 1;
  if (j == 11 && format[i] != '%')
    {
      my_putchar('%');
      my_putchar(format[i]);
    }
  else
    check = fmt_tab[j].fptr(ap, width);
  if (check != 0)
    return (1);
  return (0);
}

unsigned int	find_width(char *format, unsigned int i)
{
  char		*str;
  unsigned int	width;
  unsigned int	j;

  width = 0;
  j = i;
  while (format[i] >= '0' && format[i] <= '9')
    i = i + 1;
  str = malloc(sizeof(*str) * (j - i) + 1);
  i = 0;
  while (format[j] >= '0' && format[j] <= '9')
    {
      str[i] = format[j];
      i = i + 1;
      j = j + 1;
    }
  str[i] = '\0';
  width = my_getnbr(str);
  return (width);
}

int		my_printf(char *format, ...)
{
  va_list	ap;
  unsigned int	i;
  unsigned int	width;

  va_start(ap, format);
  i = 0;
  width = 0;
  while (format[i] != '\0')
    {
      if (format[i] != '%')
	my_putchar(format[i]);
      else
	{
	  i = i + 1;
	  while (format[i] == ' ')
	    i = i + 1;
	  if (format[i] >= '0' && format[i] <= '9')
	    {
	      width = find_width(format, i);
	      i = i + my_nbrlen(width);
	    }
	  if (format[i] == '%')
	    my_putchar(format[i]);
	  else
	      find_fmt(ap, format, i, width);
	}
      i = i + 1;
    }
  va_end(ap);
  return (0);
}
