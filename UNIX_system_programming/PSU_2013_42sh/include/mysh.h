/*
** mysh.h for minishell in /home/menich_a/rendu/PSU_2013_minishell1/include
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Dec 12 17:46:15 2013 menich_a
** Last update Sun Jun  1 19:33:59 2014 menich_a
*/

#ifndef MYSH_H_
# define MYSH_H_

# define INF		(-60)
# define SUP		(-62)
# define AND		(-38)
# define PIPE		(-124)
# define MAGIC_QUOTE	(-96)
# define O_BRACKET	(-40)
# define C_BRACKET	(-41)
# define SUCCESS	(0)
# define FAILURE	(-1)
# define CHILD_PID	(0)
# define CHECK_NEXT_CMD	(1)
# define INIT_CD	"cd ."
# define SUBSHELL_MODE	".mysh_conf"
# define MAGIC_S_ERROR	"mysh: syntax error near unexpected '`' token.\n"
# define HELP_LIST	"GNU mysh, version 4.7\nThese shell \
commands are defined internally.\nType `help' to see this list.\nUse `man' or \
`man -k' to find out more about commands not in this list.\n\n    ./filename \
[arguments]                               execute file with arguments.\n    cd \
[dir]                                             change current directory.\n \
   clear                                                clear window.\n    echo\
 [-ne] [expression]                              display expression.\n    env \
[-0] [-i] [-u [var]] [NAME=VALUE] [[cmd] [args]] execute command in modified \
environnement.\n    exit [n]                                             \
terminate the process.\n    help                                               \
  show this list.\n    kill [-lt [SIGNAL]] | [-s [SIGNAL] [PID]]            \
kill specified process.\n    printenv [var]                                    \
   print specified environnement variable.\n    setenv [var] [value]     \
                            change value of specified environnement variable.\n\
    unsetenv [var]                                       remove specified \
environnement variable.\n\n"

typedef struct	s_env
{
  int		i;
  int		j;
  int		check;
  char		**env;
}		t_env;

typedef struct	s_job
{
  int		pid;
  char		*cmd;
  struct s_job	*next;
}		t_job;

typedef struct	s_cmd
{
  char		**argv;
  char		*path;
}		t_cmd;

typedef struct	s_builtin
{
  char		*name;
  char		**(*fptr)(char **, char **);
}		t_builtin;

typedef struct	s_state
{
  int		e_state;
  int		n_state;
}		t_state;

/*
**	Builtins.
*/
char	**my_change_dir(char **, char **);

char	**my_unsetenv(char **, char **);

char	**my_setenv(char **, char **);

char	**my_env(char **, char **);

char	**my_echo(char **, char **);

char	**my_exit(char **, char **);

char	**display_history(char **, char **);

char	**unalias(char **, char **);

char	**my_help(char **, char **);

/*
**	Execution.
*/
int	display_prompt(char **, int, int);

char	**launch_cmd(char *, char **, int);

char	**execute_current_process(char **, char **);

char	**launch_appropriate_cmd(char **, char **);

int	launch_exec_cmd(char **, char **);

char	**exec_pipe_cmd(char **, char **);

char	*get_next_line(int, char **);

char	*fget_next_line(int);

/*
**	Job control
*/
char	**my_fg(char **, char **);

void	my_sigstop(int);

char	**my_jobs(char **, char **);

int	add_one_job(t_job **, int);

int	remove_one_job(t_job **, int);

char	*get_job_cmd(int);

t_job	*save_pid(int, int);

/*
**	Get tools
*/
int	get_pipes(int, int);

char	*get_tild(char *, char **);

char	*get_cmd_path(char *, char **);

char	**get_next_cmd(char **, char **, int);

char	**get_clean_cmd(char *, char ***, int);

char	**get_magic_quotes(char **, char ***);

char	**get_globing_datas(char **, int, int);

char	**get_last_cmd(char **, char *, char **);

/*
**	Builtins tools
*/
int	check_brackets(char **);

int	check_magic_quote(char **);

int	check_valid_local_var(char *);

int	my_history(char *, char **, int);

char	**cut_cmd(char **, int);

char	**exec_brackets(char **);

char	**overwrite_var(char **, char **);

char	**add_new_var(char **, char **, int);

char	**check_redirections(char **, char **);

char	**process_binary_ops(char **, char **, int);

int	my_printenv(char **, char **, int);

char	**unset_env_option(char **, int, char **);

int	launch_options_process(char **, char **, char **, int);

/*
**	Tools
*/
void	disable_sigint(int);

int	init_termios(char **);

void	my_sigint(int);

void	init_builtins_tab(t_builtin [13]);

int	my_process_errors(int);

int	launch_exiting(int);

#endif	/* !MYSH_H_ */
