##
## Makefile for wolf3d in /home/menich_a/rendu/MUL_2013_wolf3d
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Fri Jan 10 11:45:43 2014 menich_a
## Last update Sun Jan 12 20:35:50 2014 menich_a
##

NAME	= wolf3d

SRCS	= sources/main.c \
	  sources/draw_img.c \
	  sources/my_tools.c

OBJS	= main.o \
	  draw_img.o \
	  my_tools.o

CLIB	= -lmlx -lXext -lX11 -I./include

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
		cc -o $(NAME) $(OBJS) $(CLIB)

$(OBJS):	$(SRCS)
		cc -c $(SRCS) $(CLIB)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
