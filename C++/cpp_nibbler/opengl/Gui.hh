//
// graph.hh for  in /home/bencha_a/Nibler
// 
// Made by Aniss Bencharif
// Login   <bencha_a@epitech.net>
// 
// Started on  Wed Mar 25 10:57:23 2015 Aniss Bencharif
// Last update Sun Apr  5 23:32:56 2015 audurier julien
// Last update Sun Apr  5 21:28:24 2015 audurier julien
//

#ifndef Gui_HH_
# define Gui_HH_

#include "../includes/AGui.hh"
#include "../includes/Nibbler.hh"
#include "../includes/NibError.hh"
#include <SDL/SDL.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/gl.h>

class Gui : public AGui 
{
  std::string	map;
  double	height_base;
  double	weight_base;

public:
  Gui(Nibbler &map);
  virtual  ~Gui();

  virtual void		dump();
  virtual void		handleEvents();

  void		init_picture(std::string const &map) const;  
  void		Draw_quads(int const, int const, int const r, int const g, int const b) const;
  void		adjust_size(int *x, int *y, int const i) const;
  void		get_pos(int *x, int *y, char const map, int const i) const;
  int		manage_event(int s_event, SDL_Event event);

  void          aff_score(int const) const;
  void          aff_retry(std::string const &, std::string const &) const;
  void          gameOver();
  SDL_Surface *screen;
};


#endif
