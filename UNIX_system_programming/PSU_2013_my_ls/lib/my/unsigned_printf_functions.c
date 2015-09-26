/*
** unsigned_printf.c for mu_printf in /home/menich_a/rendu/PSU_2013_my_printf
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Nov 14 14:34:53 2013 menich_a
** Last update Sun Nov 17 20:46:57 2013 menich_a
*/

#include <stdarg.h>
#include "myprintf.h"
#include "my.h"

int             printf_unsigned_oct(va_list ap, unsigned int width)
{
  char		*nbr;
  unsigned int  nb;
  unsigned int	size;

  nb = va_arg(ap, unsigned int);
  nbr = from_base_ten(nb, OCT);
  size = my_strlen(nbr);
  while (size < width)
    {
      my_putchar(' ');
      size = size + 1;
    }
  my_putstr(nbr);
  return (0);
}

int             printf_low_unsigned_hex(va_list ap, unsigned int width)
{
  char		*nbr;
  unsigned int  nb;
  unsigned int	size;

  nb = va_arg(ap, unsigned int);
  nbr = from_base_ten(nb, LOW_HEX);
  size = my_strlen(nbr);
  while (size < width)
    {
      my_putchar(' ');
      size = size + 1;
    }
  my_putstr(nbr);
  return (0);
}

int             printf_unsigned_hex(va_list ap, unsigned int width)
{
  char		*nbr;
  unsigned int  nb;
  unsigned int	size;

  nb = va_arg(ap, unsigned int);
  nbr = from_base_ten(nb, HEX);
  size = my_strlen(nbr);
  while (size < width)
    {
      my_putchar(' ');
      size = size + 1;
    }
  my_putstr(nbr);
  return (0);
}

int		printf_unsigned_binary(va_list ap, unsigned int width)
{
  char		*nbr;
  unsigned int  nb;
  unsigned int	size;

  nb = va_arg(ap, unsigned int);
  nbr = from_base_ten(nb, "01");
  size = my_strlen(nbr);
  while (size < width)
    {
      my_putchar(' ');
      size = size + 1;
    }
  my_putstr(nbr);
  return (0);
}

int		printf_unsigned_int(va_list ap, unsigned int width)
{
  unsigned int  nb;
  unsigned int	size;

  nb = va_arg(ap, unsigned int);
  size = my_nbrlen(nb);
  while (size < width)
    {
      my_putchar(' ');
      size = size + 1;
    }
  my_put_unsigned_nbr(nb);
  return (0);
}
