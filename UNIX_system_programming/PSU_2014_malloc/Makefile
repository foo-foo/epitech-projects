##
## Makefile for malloc in /home/menich_a/rendu/PSU_2014_malloc
## 
## Made by Anatole Menichetti
## Login   <menich_a@epitech.net>
## 
## Started on  Mon Feb  2 17:41:22 2015 Anatole Menichetti
## Last update Sun Feb 15 21:51:17 2015 Anatole Menichetti
##

NAME1	= libmy_malloc_$(HOSTTYPE).so

NAME2	= libmy_malloc.so

SRCS	= malloc.c \
	  alloc.c \
	  blocks.c

OBJS	= $(SRCS:.c=.o)

RM	= rm -f

CC	= gcc

CFLAGS	= -W -Wall -Wextra -Werror

all:		$(NAME1)

$(NAME1):	$(OBJS)
		$(CC) -shared -fpic $(SRCS) -o $(NAME1)
		ln -fs $(NAME1) $(NAME2)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME1) $(NAME2)

re:		fclean all

.PHONY:		all clean fclean re

