//
// graph.hh for  in /home/bencha_a/Nibler
// 
// Made by Aniss Bencharif
// Login   <bencha_a@epitech.net>
// 
// Started on  Wed Mar 25 10:57:23 2015 Aniss Bencharif
// Last update Sun Apr  5 21:37:13 2015 Anatole Menichetti
//

#ifndef Gui_HH_
# define Gui_HH_

# include "../includes/AGui.hh"
# include "../includes/NibError.hh"
# include <SDL/SDL_ttf.h>
# include <SDL/SDL_image.h>
# include <vector>
# include <SDL/SDL.h>
# include <string>
# include <iostream>
# include <fstream>
# include <sstream>


class Gui : public AGui
{
  SDL_Surface	*screen;

public:
  Gui(Nibbler &);
  virtual ~Gui();

  virtual void	handleEvents();
  virtual void	dump();

private:
  void		init_picture() const;

  void		adjust_size(int *x, int *y, const int i) const;
  void		get_pos(int *x, int *y, char map, int i) const;
  void		load_img(const char player, SDL_Rect pos, std::vector<SDL_Surface*> &screens) const;

  void		aff_score(const int) const;
  void		aff_retry(std::string const &, std::string const &) const;
  void		gameOver();
};

#endif
