##
## Makefile for minitalk in /home/menich_a/rendu/PSU_2013_minitalk
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Tue Mar  4 12:12:50 2014 menich_a
## Last update Sun Mar 23 14:01:54 2014 menich_a
##

NAME1	= server/server

NAME2	= client/client

SRCS1	= server/server.c \
	  server/multi_client.c \
	  my/my_tools.c \
	  my/my.c

SRCS2	= client/client.c \
	  my/my_getnbr.c \
	  my/my.c

OBJS1	= $(SRCS1:.c=.o)

OBJS2	= $(SRCS2:.c=.o)

RM	= rm -f

all:		$(NAME1) $(NAME2)

$(NAME1):	$(OBJS1)
		cc -o $(NAME1) $(OBJS1)

$(NAME2):	$(OBJS2)
		cc -o $(NAME2) $(OBJS2)
clean:
		$(RM) $(OBJS1)
		$(RM) $(OBJS2)

fclean:		clean
		$(RM) $(NAME1)
		$(RM) $(NAME2)

re:		fclean all

.PHONY:		all clean fclean re
