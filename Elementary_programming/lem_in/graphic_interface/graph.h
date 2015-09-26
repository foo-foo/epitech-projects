/*
** graph.h for my_struct.h in /home/benoit_l/rendu/lem-in
** 
** Made by Benoit Leo
** Login   <benoit_l@epitech.net>
** 
** Started on  Thu Apr 24 09:29:33 2014 Benoit Leo
** Last update Sun May  4 19:18:41 2014 menich_a
*/

#ifndef GRAPH_H_
# define GRAPH_H_

# define ANT_IMG       "\
00000000000000000000\n\
00000000000000000000\n\
00100000000000100000\n\
00010000000001000000\n\
00001000000010000000\n\
00000100000100000000\n\
00000111111000000000\n\
00001111111100000000\n\
01001111111100100000\n\
00100111111001000000\n\
01010111111010100000\n\
00101111111101000000\n\
00010111111010000000\n\
00001111111100000000\n\
00000111111000000000\n\
00001011110100000000\n\
00010111111010000000\n\
00010000000010000000\n\
00010000000010000000\n\
00000000000000000000\n"

typedef struct		s_coord
{
  char			*room_name;
  char			**connection;
  int			check;
  int			x;
  int			y;
  struct s_coord	*next;
}			t_coord;

typedef struct	s_ant
{
  int		nbr;
  int		moving;
  int		old_x;
  int		old_y;
  int		new_x;
  int		new_y;
  struct s_ant	*next;
}		t_ant;

typedef struct s_img
{
  void		*init;
  void		*window;
  void		*img_ptr;
  unsigned int  width;
  unsigned int  height;
  int           bpp;
  int           szline;
  int           end;
  char          *data;
}               t_img;

int	adjust_list(t_coord *rooms, t_ant *list, char *turn);

int	square_power(int x);

int	ant_case_one(t_img *lem, int x1,int y1,int x2,int y2, int i);

int	ant_case_two(t_img *lem, int y1, int x1, int y2, int x2, int i);

int	my_search_in_list(t_coord *begun, char *str, int i, int a);

int	check_connection(char *str);

int	my_put_in_list(t_coord **begun, char *line, int check);

int	check_space(char *str);

int	my_getnbr(char *nbr);

void	draw_case_one(t_img *img, int x1,int y1,int x2,int y2);

void	draw_case_two(t_img *img, int x1,int y1,int x2,int y2);

void	sky(t_img *img);

void	grass(t_img *img);

void	ground(t_img *img);

int	put_pixel_image(t_img *img, int x, int y, int c1, int c2, int c3);

int	put_pixel_image_lem(t_img *img, int x, int y, int color);

int	get_nbr_ants(char *str);

void	my_putstr(char *str);

void	put_square(t_img *img, char *buff);

int	put_circle(t_img *img, int x, int y, int r);

void	move_ants(char **way, t_coord *coord, t_ant *ants, t_img *lem);

int	draw_line(t_img *img, int x1, int y1, int x2, int y2);

int	gereexpose_coord(t_img*, int, int);

int	gereexpose(t_img*);

char	**get_way(char **tab);

char	**my_realloc(char **tab);

t_img	*creat_img(t_img *img);

t_img	*creat_ants(t_img *lem, t_img *img);

char	**my_tab_dup(char **tab);

t_ant	*create_ants_list(int ants_nbr, t_coord *rooms);

char	**get_data();

t_coord	*get_room_coord(char **tab, t_coord *coord, int i);

#endif /* !GRAPH_H */
