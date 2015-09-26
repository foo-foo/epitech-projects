##
## Makefile for lemipc in /home/menich_a/rendu/PSU_2014_lemipc
## 
## Made by Anatole Menichetti
## Login   <menich_a@epitech.net>
## 
## Started on  Mon Mar  2 15:51:55 2015 Anatole Menichetti
## Last update Sun Mar  8 22:30:48 2015 Anatole Menichetti
##

NAME	= lemipc

NAME2	= gui

SRCS	= srcs/main.c \
	  srcs/init.c \
	  srcs/lemipc.c \
	  srcs/move.c \
	  srcs/pos.c \
	  srcs/map.c \
	  srcs/ipc.c \
	  srcs/tools.c

SRCS2	= srcs/graph.c \
	  srcs/init_picture.c \
	  srcs/graph_calcul.c \
	  srcs/graph_shared_mem.c

OBJS2	= $(SRCS2:.c=.o)

OBJS	= $(SRCS:.c=.o)

CC	= gcc

CFLAGS	= -W -Wall -Wextra -Werror

RM	= rm -f

all:		$(NAME) $(NAME2)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS)

$(NAME2):	$(OBJS2)
		$(CC) -lSDL -lSDLmain -o $(NAME2) $(OBJS2)

clean:
		$(RM) $(OBJS) $(OBJS2)

fclean:		clean
		$(RM) $(NAME) $(NAME2)

re:		fclean all

.PHONY:		all clean fclean re
