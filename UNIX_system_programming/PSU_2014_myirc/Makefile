##
## Makefile for my_irc in /home/menich_a/rendu/PSU_2014_myirc
## 
## Made by Anatole Menichetti
## Login   <menich_a@epitech.net>
## 
## Started on  Tue Apr  7 14:07:55 2015 Anatole Menichetti
## Last update Sun Apr 12 12:43:40 2015 Anatole Menichetti
##

client		= client

server		= server

CLIENT_SRCS	= srcs/client/main.c			\
		  srcs/client/client.c			\
		  srcs/client/handle_stdin.c		\
		  srcs/client/handle_connection.c	\
		  srcs/client/prefix.c			\
		  srcs/client/err_serv.c		\
		  srcs/client/str_to_cmdtab.c		\
		  srcs/tools/circular_read.c		\
		  srcs/tools/put.c			\
		  srcs/tools/tab.c			\
		  srcs/tools/my_memset.c		\
		  srcs/tools/errors.c

SERVER_SRCS	= srcs/server/main.c			\
		  srcs/server/handler.c			\
		  srcs/server/channels.c		\
		  srcs/server/check_channel_name.c	\
		  srcs/server/messages.c		\
		  srcs/server/err_serv.c		\
		  srcs/server/quit.c			\
		  srcs/server/names.c			\
		  srcs/server/nickname.c		\
		  srcs/server/fd_list.c			\
		  srcs/server/str_to_cmdtab.c		\
		  srcs/server/dest_tab.c		\
		  srcs/tools/circular_read.c		\
		  srcs/tools/char_check.c		\
		  srcs/tools/tab.c			\
		  srcs/tools/put.c			\
		  srcs/tools/my_memset.c		\
		  srcs/tools/errors.c

CLIENT_OBJS	= $(CLIENT_SRCS:.c=.o)

SERVER_OBJS	= $(SERVER_SRCS:.c=.o)

CC		= gcc

CFLAGS		= -W -Wall -Wextra -Werror

RM		= rm -f

all:		$(client) $(server)

$(client):	$(CLIENT_OBJS)
		$(CC) -o $(client) $(CLIENT_OBJS)

$(server):	$(SERVER_OBJS)
		$(CC) -o $(server) $(SERVER_OBJS)

clean:
		$(RM) $(CLIENT_OBJS) $(SERVER_OBJS)

fclean:		clean
		$(RM) $(client) $(server)

re:		fclean all

.PḦONY:		all clean fclean re

