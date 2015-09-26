##
## Makefile for lem_in in /home/menich_a/rendu/prog_elem/lem_in
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Fri Dec  6 11:42:23 2013 menich_a
## Last update Sun May  4 19:50:58 2014 menich_a
##

NAME	= lem_in

GR_NAME	= visu-hex

SRCS	= srcs/main.c			\
	  srcs/lem_in.c			\
	  srcs/init_anthill.c		\
	  srcs/find_short_way.c		\
	  srcs/tools/get_next_line.c	\
	  srcs/tools/init_rooms.c	\
	  srcs/tools/tools.c		\
	  srcs/tools/ants.c		\
	  srcs/tools/tab.c		\
	  srcs/tools/my.c		\
	  srcs/tools/my2.c		\
	  srcs/tools/my3.c

GR_SRCS	= graphic_interface/graph.c	\
	  graphic_interface/prog.c	\
	  graphic_interface/tunnel.c	\
	  graphic_interface/lemmings.c	\
	  graphic_interface/read_data.c	\
	  graphic_interface/gere_img.c	\
	  graphic_interface/tools.c	\
	  graphic_interface/gere_list.c	\
	  graphic_interface/background.c	\
	  graphic_interface/gere_move_ants.c	\
	  graphic_interface/get_next_line.c	\
	  graphic_interface/get_next_line2.c	\
	  graphic_interface/put_circle.c	\
	  graphic_interface/search_in_list.c	\
	  graphic_interface/put_in_list.c	\
	  graphic_interface/tools2.c

OBJS	= $(SRCS:.c=.o)

GR_OBJS	= $(GR_SRCS:.c=.o)

CFLAGS	= -I./includes

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS) $(GR_OBJS)
		cc -o $(NAME) $(OBJS)
		cc -o $(GR_NAME) $(GR_OBJS) -lmlx -lXext -lX11 -lm
clean:
		$(RM) $(OBJS)
		$(RM) $(GR_OBJS)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(GR_NAME)

re:		fclean all

.PHONY:		all clean fclean re
