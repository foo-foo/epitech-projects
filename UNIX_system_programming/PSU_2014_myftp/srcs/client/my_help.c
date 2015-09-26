/*
** my_help.c for myftp in /home/menich_a/rendu/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Mar 26 15:30:54 2015 Anatole Menichetti
** Last update Sat Mar 28 18:25:52 2015 Anatole Menichetti
*/

#include <string.h>
#include "../../includes/client.h"
#include "../../includes/my.h"

void	init_help_macros(char *help_msgs[2][22])
{
  help_msgs[1][0] = CD_HELP;
  help_msgs[1][1] = LCD_HELP;
  help_msgs[1][2] = LS_HELP;
  help_msgs[1][3] = LLS_HELP;
  help_msgs[1][4] = PWD_HELP;
  help_msgs[1][5] = LPWD_HELP;
  help_msgs[1][6] = USER_HELP;
  help_msgs[1][7] = GET_HELP;
  help_msgs[1][8] = MGET_HELP;
  help_msgs[1][9] = PUT_HELP;
  help_msgs[1][10] = MPUT_HELP;
  help_msgs[1][11] = HELP_HELP;
  help_msgs[1][12] = STOU_HELP;
  help_msgs[1][13] = APPE_HELP;
  help_msgs[1][14] = MKD_HELP;
  help_msgs[1][15] = ACCT_HELP;
  help_msgs[1][16] = NLST_HELP;
  help_msgs[1][17] = RNFR_HELP;
  help_msgs[1][18] = RNTO_HELP;
  help_msgs[1][19] = NOOP_HELP;
  help_msgs[1][20] = RMD_HELP;
  help_msgs[1][21] = DELE_HELP;
}

void	init_help_msgs(char *help_msgs[2][22])
{
  help_msgs[0][0] = "CWD";
  help_msgs[0][1] = "LCWD";
  help_msgs[0][2] = "LIST";
  help_msgs[0][3] = "LLIST";
  help_msgs[0][4] = "PWD";
  help_msgs[0][5] = "LPWD";
  help_msgs[0][6] = "USER";
  help_msgs[0][7] = "RETR";
  help_msgs[0][8] = "MRETR";
  help_msgs[0][9] = "STOR";
  help_msgs[0][10] = "MSTOR";
  help_msgs[0][11] = "HELP";
  help_msgs[0][12] = "STOU";
  help_msgs[0][13] = "APPE";
  help_msgs[0][14] = "MKD";
  help_msgs[0][15] = "ACCT";
  help_msgs[0][16] = "NLST";
  help_msgs[0][17] = "RNFR";
  help_msgs[0][18] = "RNTO";
  help_msgs[0][19] = "NOOP";
  help_msgs[0][20] = "RMD";
  help_msgs[0][21] = "DELE";
  init_help_macros(help_msgs);
}

char	*my_help(char *param)
{
  int	i;
  char	*help_msgs[2][22];

  i = 0;
  init_help_msgs(help_msgs);
  while (param[0] == ' ' || param[0] == '\t')
    param += 1;
  if (param[0] == '\n')
    {
      putstr(HELP_MSG);
      return (strdup(""));
    }
  while (i < 22 && my_cmdcmp(param, help_msgs[0][i]))
    i += 1;
  if (i < 22)
    {
      putstr(help_msgs[1][i]);
      return (strdup(""));
    }
  putstr("?Invalid help command `");
  param[strlen(param) - 1] = '\0';
  putstr(param);
  param[strlen(param)] = '\n';
  putstr("'\n");
  return (strdup(""));
}
