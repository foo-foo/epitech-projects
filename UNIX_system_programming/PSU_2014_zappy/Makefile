##
## Makefile for zappy in /home/toma_i/rendu/PSU_2014_zappy/server_src
##
## Created by Ivan Toma
## Login   <@epitech.eu>
##
## Started on  Sun Jun 21 16:27:32 2015 Ivan Toma
## Last update Sun Jul  5 16:18:45 2015 Bastos-Fix
##

NAME1	= zappy_server

NAME2	= zappy_ui

NAME3	= zappy_ai

SSRCPATH	= Server/

SCRCPATH	= Client/

SRCS1	= ./Sockets/sockets_handler.c		\
	  $(SSRCPATH)main.c			\
	  $(SSRCPATH)argument.c			\
	  $(SSRCPATH)argument2.c		\
	  $(SSRCPATH)server.c			\
	  $(SSRCPATH)server_fd.c		\
	  $(SSRCPATH)server_fd2.c		\
	  $(SSRCPATH)get_next_line.c		\
	  $(SSRCPATH)str_to_wordtab.c		\
	  $(SSRCPATH)fptr_action.c		\
	  $(SSRCPATH)init_env.c			\
	  $(SSRCPATH)init_action.c		\
	  $(SSRCPATH)action.c			\
	  $(SSRCPATH)delete_env.c		\
	  $(SSRCPATH)utils.c			\
	  $(SSRCPATH)pose.c			\
	  $(SSRCPATH)prend.c			\
	  $(SSRCPATH)fptr_voir.c		\
	  $(SSRCPATH)expulse.c			\
	  $(SSRCPATH)death.c			\
	  $(SSRCPATH)fork.c			\
	  $(SSRCPATH)incantation.c		\
	  $(SSRCPATH)avance.c			\
	  $(SSRCPATH)init_player.c		\
	  $(SSRCPATH)init_player2.c		\
	  $(SSRCPATH)droite.c			\
	  $(SSRCPATH)gauche.c			\
	  $(SSRCPATH)incantation_send.c		\
	  $(SSRCPATH)nb_connect.c		\
	  $(SSRCPATH)graphic.c			\
	  $(SSRCPATH)graphic2.c			\
	  $(SSRCPATH)graphic3.c			\
	  $(SSRCPATH)graphic4.c			\
	  $(SSRCPATH)graphic5.c			\
	  $(SSRCPATH)graphic6.c			\
	  $(SSRCPATH)graphic7.c			\
	  $(SSRCPATH)graphic8.c			\
	  $(SSRCPATH)broadcast.c		\
	  $(SSRCPATH)verif_fd.c			\
	  $(SSRCPATH)regen_food.c

SRCS2	= GraphicEngine/Client/main.cpp			\
	  GraphicEngine/Client/Client.cpp		\
	  GraphicEngine/Client/ClientException.cpp	\
	  GraphicEngine/Client/get_next_line.cpp	\
	  GraphicEngine/Srcs/GraphicEngine.cpp		\
	  GraphicEngine/Srcs/Map.cpp			\
	  GraphicEngine/Srcs/Ground.cpp			\
	  GraphicEngine/Srcs/AObject.cpp		\
	  GraphicEngine/Srcs/ARessource.cpp		\
	  GraphicEngine/Srcs/Character.cpp		\
	  GraphicEngine/Srcs/Egg.cpp

SRCS3	= $(SCRCPATH)actions.c			\
	  $(SCRCPATH)broadcast.c		\
	  $(SCRCPATH)broadcast2.c		\
	  $(SCRCPATH)clear_vision.c		\
	  $(SCRCPATH)client.c			\
	  $(SCRCPATH)contact_server.c		\
	  $(SCRCPATH)errors.c			\
	  $(SCRCPATH)execute_action.c		\
	  $(SCRCPATH)extern_actions.c		\
	  $(SCRCPATH)get_best_way_to_survive.c	\
	  $(SCRCPATH)get_next_line.c		\
	  $(SCRCPATH)get_vision.c		\
	  $(SCRCPATH)get_vision_priorities.c	\
	  $(SCRCPATH)init_player.c		\
	  $(SCRCPATH)look.c			\
	  $(SCRCPATH)main.c			\
	  $(SCRCPATH)received_msg.c		\
	  $(SCRCPATH)rise.c			\
	  $(SCRCPATH)str.c			\
	  $(SCRCPATH)tab.c			\
	  $(SCRCPATH)visited_squares.c

INC	= -I./GraphicEngine/LibGDL_linux_x64/includes
INC	+=  -I./GraphicEngine/Headers

LIB	=  -L./GraphicEngine/LibGDL_linux_x64/libs

OBJS1	= $(SRCS1:.c=.o)

OBJS2	= $(SRCS2:.cpp=.o)

OBJS3	= $(SRCS3:.c=.o)

CC	= gcc

GPP	= g++

GFLAGS	= -lgdl_gl -lGL -lGLEW -lfbxsdk -lSDL2 -lm -ldl -lrt -lpthread -g3 -std=c++11

CFLAGS	= -W -Wall -Werror -Wextra -g3

RM	= rm -f

all: $(NAME1) $(NAME3) $(NAME2)

zappy_s: $(NAME1)

zappy_u: $(NAME2)

zappy_a: $(NAME3)

$(NAME1): $(OBJS1)
	$(CC) $(OBJS1) -o $(NAME1)

$(NAME2): $(OBJS2)
	$(GPP) $(OBJS2) $(LIB) $(CFLAGS) $(GFLAGS) -o $(NAME2)

$(NAME3): $(OBJS3)
	$(CC) $(OBJS3) -o $(NAME3)

%.o:%.cpp
	$(GPP) $< -o $@ $(INC) $(CFLAGS) $(GFLAGS) -fpic -c

clean:
	$(RM) $(OBJS1) $(OBJS2) $(OBJS3)

fclean: clean
	$(RM) $(NAME1) $(NAME2) $(NAME3)

re: fclean all

.PHONY: all clean fclean re
