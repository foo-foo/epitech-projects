/*
** basic_printf.c for my_printf in /home/menich_a/rendu/PSU_2013_my_printf
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Nov 14 14:36:07 2013 menich_a
** Last update Sun Nov 17 20:34:43 2013 menich_a
*/

#include <stdarg.h>
#include "myprintf.h"
#include "my.h"

int		printf_unprintable_string(va_list ap, unsigned int width)
{
  char		*str;

  str = va_arg(ap, char *);
  while (width > my_strlen(str))
    {
      my_putchar(' ');
      width = width - 1;
    }
  my_showstr_oct(str);
  return (0);
}

int             printf_pointer(va_list ap, unsigned int width)
{
  char		*ptr;
  unsigned int  nb;
  unsigned int  size;

  nb = va_arg(ap, unsigned int);
  ptr = from_base_ten(nb, HEX);
  size = my_strlen(ptr) + 2;
  while (size < width)
    {
      my_putchar(' ');
      size = size + 1;
    }
  my_putstr("0x");
  my_putstr(ptr);
  return (0);
}

int             printf_string(va_list ap, unsigned int width)
{
  char          *str;

  str = va_arg(ap, char *);
  while (width > my_strlen(str))
    {
      my_putchar(' ');
      width = width - 1;
    }
  my_putstr(str);
  return (0);
}

int             printf_char(va_list ap, unsigned int width)
{
  char          c;
  int		size;

  c = (char)va_arg(ap, int);
  size = 1;
  while (size < width)
    {
      my_putchar(' ');
      size = size + 1;
    }
  my_putchar(c);
  return (0);
}

int             printf_int(va_list ap, unsigned int width)
{
  int           nb;
  unsigned int  size;

  nb = va_arg(ap, unsigned int);
  size = my_nbrlen(nb);
  while (size < width)
    {
      my_putchar(' ');
      size = size + 1;
    }
  my_put_nbr(nb);
  return (0);
}
