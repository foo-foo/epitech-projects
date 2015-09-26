/*
** wolf3d.h for wolf3d in /home/menich_a/rendu/MUL_2013_wolf3d
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan  8 11:34:55 2014 menich_a
** Last update Sun Jan 12 20:23:27 2014 menich_a
*/

#ifndef WOLF3D_H_
# define WOLF3D_H_
# define ESCAPE		(65307)
# define UP		(65362)
# define DOWN		(65364)

typedef struct	s_mlx
{
  void		*mlx_ptr;
  void		*win_ptr;
  void		*img_ptr;
}		t_mlx;

typedef struct	s_img
{
  char		*data;
  int		endian;
  int		sizeline;
  int		x;
  int		y;
  int		bpp;
}		t_img;

typedef struct	s_color
{
  int		r;
  int		g;
  int		b;
}		t_color;

t_img	g_img;

int	draw_img(int, int);

int	gerekey(int, void*);

int	expose(t_mlx *);

int	mlx_pixel_put_img(int, int, t_color);

void	init_img(t_mlx, int, int);

t_color	init_color(int, int, int);

#endif	/* !WOLF3D_H_ */
