/*
** verif_fd.c for verif_fd in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:35:35 2015 Sebastien Lauret
** Last update Sun Jul  5 15:35:37 2015 Sebastien Lauret
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "header/fonction.h"

static char	*parse_line(char *line)
{
  int		i;

  i = 0;
  while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
    ++i;
  line  = &line[i];
  i = 0;
  while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
    ++i;
  line[i] = '\0';
  return (line);
}

int		verif_fd()
{
  FILE		*fd;
  int		fd_max;
  char		*line;
  char		*tab;
  size_t	i;

  i = 0;
  line = NULL;
  if ((fd = fopen("/proc/sys/fs/file-nr", "r")) == NULL
      || (getline(&line, &i, fd)) <= 0)
    return (-1);
  line = parse_line(line);
  fd_max = strtol(line, &tab, 10);
  if (tab[0] != '\0' || fd_max < MAX_FD)
    {
      fprintf(stderr, "Nombre de fd disponible trop petit\n");
      return (-1);
    }
  fclose(fd);
  return (0);
}

