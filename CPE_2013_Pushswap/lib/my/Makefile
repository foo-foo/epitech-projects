##
## Makefile for libmy.a in /home/menich_a/rendu/Piscine-C-lib/my
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Mon Oct 21 08:04:46 2013 menich_a
## Last update Mon Jan  6 22:40:15 2014 menich_a
##

NAME	= libmy.a

SRCS	= my_strlen.c \
	  my_getnbr.c \
	  my_putchar.c \
	  my_strcmp.c \
	  my_putstr.c \
	  msg_error_exit.c

OBJS	= my_strlen.o \
	  my_getnbr.o \
	  my_putchar.o \
	  my_strcmp.o \
	  my_putstr.o \
	  msg_error_exit.o

all:		$(NAME)

$(NAME):	$(OBJS)
		ar rc	$(NAME) $(OBJS)
		ranlib	$(NAME)
		cp	$(NAME) ..

$(OBJS):	$(SRCS)
		cc -c $(SRCS) -I../../include

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all
