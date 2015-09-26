##
## Makefile for minishell1 in /home/menich_a/rendu/PSU_2013_minishell1
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Fri Dec  6 11:42:23 2013 menich_a
## Last update Sun Jun  1 18:06:58 2014 menich_a
##

NAME	= mysh

SRCS	= srcs/main.c				\
	  srcs/termcaps/keys.c			\
	  srcs/termcaps/ctrl_keys.c		\
	  srcs/termcaps/history_keys.c		\
	  srcs/termcaps/dynamic_completion.c	\
	  srcs/termcaps/completion_tools.c	\
	  srcs/termcaps/buff_is_specialkey.c	\
	  srcs/termcaps/tc_get_next_line.c	\
	  srcs/termcaps/tc_tools.c		\
	  srcs/termcaps/tc_init.c		\
	  srcs/launch_command.c			\
	  srcs/exec_command.c			\
	  srcs/redirections.c			\
	  srcs/builtins/magic_tools.c		\
	  srcs/builtins/binary_ops.c		\
	  srcs/builtins/my_help.c		\
	  srcs/builtins/my_echo.c		\
	  srcs/builtins/globing.c		\
	  srcs/builtins/unalias.c		\
	  srcs/builtins/alias.c			\
	  srcs/builtins/alias_tools.c		\
	  srcs/builtins/my_exit.c		\
	  srcs/builtins/brackets.c		\
	  srcs/builtins/magic_quotes.c		\
	  srcs/builtins/var_local.c		\
	  srcs/builtins/setenv.c		\
	  srcs/builtins/last_history_cmd.c	\
	  srcs/builtins/history.c		\
	  srcs/builtins/unsetenv.c		\
	  srcs/builtins/my_env2.c		\
	  srcs/builtins/my_env.c			\
	  srcs/builtins/change_dir.c		\
	  srcs/builtins/job_control.c		\
	  srcs/builtins/my_jobs.c		\
	  srcs/tools/get_next_line.c		\
	  srcs/tools/signals.c			\
	  srcs/tools/init_builtins_tab.c	\
	  srcs/tools/get_fd.c			\
	  srcs/tools/tools.c			\
	  srcs/tools/msg_error.c		\
	  srcs/tools/buff_to_cmdtab.c		\
	  srcs/tools/get.c			\
	  srcs/my/my_str_isprintable.c		\
	  srcs/my/my_remove_spaces.c		\
	  srcs/my/my_find_in_env.c		\
	  srcs/my/my_find_in_tab.c		\
	  srcs/my/my_find_in_str.c		\
	  srcs/my/my_path_to_tab.c		\
	  srcs/my/my_free_tab.c			\
	  srcs/my/my_putchar.c			\
	  srcs/my/my_put_nbr.c			\
	  srcs/my/my_strndup.c			\
	  srcs/my/my_getnbr.c			\
	  srcs/my/my_putstr.c			\
	  srcs/my/my_strcat.c			\
	  srcs/my/my_strcmp.c			\
	  srcs/my/my_strcpy.c			\
	  srcs/my/my_strdup.c			\
	  srcs/my/my_strlen.c			\
	  srcs/my/my_tablen.c			\
	  srcs/my/my_tabcpy.c			\
	  srcs/my/my_syntax.c			\
	  srcs/my/my_remove.c			\
	  srcs/my/my_process_errors.c		\
	  srcs/my/my_jump_inhibitors.c		\
	  srcs/my/my_perror.c


OBJS	= $(SRCS:.c=.o)

CFLAGS	= -W -Wall -Wextra -I./include

CC	= gcc

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) -lncurses
clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
