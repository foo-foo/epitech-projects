##
## Makefile for my_ftp in /home/menich_a/rendu/PSU_2014_myftp
## 
## Made by Anatole Menichetti
## Login   <menich_a@epitech.net>
## 
## Started on  Mon Mar  9 15:50:57 2015 Anatole Menichetti
## Last update Sat Mar 28 18:18:21 2015 Anatole Menichetti
##

SERVER_NAME	= serveur

CLIENT_NAME	= client

SERVER_SRCS	= srcs/server/main.c		\
		  srcs/server/handle_clients.c	\
		  srcs/server/handle_cmd.c	\
		  srcs/server/my_ls.c		\
		  srcs/server/my_pwd.c		\
		  srcs/server/my_cd.c		\
		  srcs/server/my_user.c		\
		  srcs/server/connect_user.c	\
		  srcs/server/my_put.c		\
		  srcs/server/my_get.c		\
		  srcs/server/my_noop.c		\
		  srcs/server/my_dele.c		\
		  srcs/server/my_acct.c		\
		  srcs/server/my_appe.c		\
		  srcs/server/my_mkd.c		\
		  srcs/server/my_nls.c		\
		  srcs/server/my_rn.c		\
		  srcs/server/my_stou.c		\
		  srcs/server/conf.c		\
		  srcs/server/errors.c

CLIENT_SRCS	= srcs/client/main.c		\
		  srcs/client/client.c		\
		  srcs/client/cmd.c		\
		  srcs/client/my_user.c		\
		  srcs/client/my_lcd.c		\
		  srcs/client/my_lpwd.c		\
		  srcs/client/my_lls.c		\
		  srcs/client/my_get.c		\
		  srcs/client/my_put.c		\
		  srcs/client/transfert.c	\
		  srcs/client/my_help.c		\
		  srcs/client/tools.c		\
		  srcs/client/error.c

TOOLS_SRCS	= srcs/tools/get_pwd.c		\
		  srcs/tools/my.c

SERVER_OBJS	= $(SERVER_SRCS:.c=.o)

CLIENT_OBJS	= $(CLIENT_SRCS:.c=.o)

TOOLS_OBJS	= $(TOOLS_SRCS:.c=.o)

CC		= gcc -g

CFLAGS		= -W -Wall -Wextra -Werror

RM		= rm -f

all:		$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME):	$(SERVER_OBJS) $(TOOLS_OBJS)
		$(CC) -o $(SERVER_NAME) $(SERVER_OBJS) $(TOOLS_OBJS)

$(CLIENT_NAME):	$(CLIENT_OBJS) $(TOOLS_OBJS)
		$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJS) $(TOOLS_OBJS)

clean:
		$(RM) $(SERVER_OBJS) $(CLIENT_OBJS) $(TOOLS_OBJS)

fclean:		clean
		$(RM) $(SERVER_NAME) $(CLIENT_NAME)

re:		fclean all

.PHONY:		all clean fclean re
