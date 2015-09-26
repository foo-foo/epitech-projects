//
// Gui.cpp for  in /home/bencha_a/Nibler
// 
// Made by Aniss Bencharif
// Login   <bencha_a@epitech.net>
// 
// Started on  Wed Mar 25 11:07:01 2015 Aniss Bencharif
// Last update Sun Apr  5 21:53:19 2015 Anatole Menichetti
//

#include "Gui.hh"
#include <SDL/SDL.h>
#include <stdio.h>
#include <unistd.h>

Gui::Gui(Nibbler &nibbler) : AGui(nibbler)
{
  screen = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw (NibError("SDL_init", "fail"));
  atexit(SDL_Quit);
  TTF_Init();
  screen = SDL_SetVideoMode(nibbler.getWidth() * 25, nibbler.getHeight() * 25, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("NIBBLER", NULL);
  if (screen == NULL)
    throw (NibError("Video_mode", "fail"));   
}

void	Gui::gameOver()
{
  bool	retry = false;
  int	s_event = 0;
  SDL_Event event;

  aff_score(1);
  aff_retry("QUIT" , "RETRY");
  while (!s_event)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
	case SDL_QUIT:
	  {
	    s_event = 1;
	    break;
	  }
	case SDL_KEYDOWN:
	  {
	    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
	      {
		retry = !retry;
		SDL_FillRect(screen, NULL, 0);
		aff_score(1);
		if (retry)
		  aff_retry("RETRY" , "QUIT");
		else
		  aff_retry("QUIT" , "RETRY");
	      }
	    if (event.key.keysym.sym == SDLK_RETURN)
	      s_event = 1;
	    if (event.key.keysym.sym == SDLK_ESCAPE)
	      s_event = 1;
	    break;
	  }
	}
    }
  if (!retry)
    m_state = DISABLE;
  else
    {
      m_nibbler.retry();
      usleep(25000);
    }
}

void	Gui::handleEvents()
{
  int	s_event = 0;
  SDL_Event event;

  SDL_PollEvent(&event);
  switch(event.type)
    {
    case SDL_QUIT:
      {
	s_event = 1;
	break;
      }
    case SDL_KEYDOWN:
      {
	switch(event.key.keysym.sym)
	  {
	  case SDLK_LEFT:
	    {
	      m_nibbler.turn_left();
	      break;
	    }
	  case SDLK_RIGHT:
	    {
	      m_nibbler.turn_right();
	      break;
	    }
	  case SDLK_ESCAPE:
	    {
	      s_event = 1;
	      break;
	    }
	  case SDLK_SPACE:
	    {
	      m_nibbler.boost();
	      break;
	    }
	  }
	break;
      }
    }
  if (s_event == 1)
    {
      m_state = DISABLE;
      m_nibbler.disable();
      SDL_Quit();
    }
  else
    if (!m_nibbler.isActive())
      gameOver();
}

void	Gui::dump()
{
  init_picture();
  SDL_FillRect(screen, NULL, 0);
  aff_score(0);
  handleEvents();
}

Gui::~Gui()
{}

void            Gui::load_img(const char player, SDL_Rect pos, std::vector<SDL_Surface*> &screens) const
{
  std::vector<SDL_Surface*>::iterator it;
  std::string const	imgsNames[] = { "sdl/snake_img/Space_jaune.bmp", "sdl/snake_img/Space_vert.bmp", "sdl/snake_img/Space_rouge.bmp", "sdl/snake_img/Space_turquoise.bmp" };


  if (player >= '0' && player <= '4')
    {
      screens.push_back(SDL_LoadBMP(imgsNames[player - 48].c_str()));
      it = screens.end() - 1;
    }
  else
    throw (NibError("Data", "missing data one the map"));
  SDL_BlitSurface(*it, NULL, screen, &pos);
  SDL_Flip(screen);
}

void             Gui::init_picture() const
{
  SDL_Rect      pos;
  int           i;
  int           x;
  int           y;
  std::string const	map = m_nibbler.getMap();

  std::vector<SDL_Surface*> screens;
  i = 0;

  while (i < map.size())
    {
      get_pos(&x, &y, map[i], i);
      if (x != -42)
        {
	  pos.y = y;
          pos.x = x;
          load_img(map[i], pos, screens);
	}
      i++;
    }
}

void           Gui::adjust_size(int *x, int *y, const int i) const
{
  const size_t        width = m_nibbler.getWidth();
  const size_t        height = m_nibbler.getHeight();

  *x = i % width * 25;
  *y = ((i - i % width) / width) * 25;
}

void            Gui::get_pos(int *x, int *y, char map, int i) const
{
  if (map != ' ')
    adjust_size(x, y, i);
  else
    *x = -42;
}

void            Gui::aff_score(int const game_over) const
{
  SDL_Surface	*texte;
  SDL_Rect	position;
  TTF_Font	*police;
  const SDL_Color	white = {255, 255, 255};
  std::ostringstream	os;

  os << m_nibbler.getScore();
  os.str();
  if (game_over == 0)
    {
      police = TTF_OpenFont("./sdl/police/geek.ttf",40);  
      texte = TTF_RenderText_Blended(police, os.str().c_str(), white);
      position.x = 0;
      position.y = 0;  
    }
  else
    {
      police = TTF_OpenFont("./sdl/police/geek.ttf", 50);
      texte = TTF_RenderText_Blended(police, "GAME OVER", white);
      position.y = (((m_nibbler.getHeight() * 25) / 4));
      position.x = (((m_nibbler.getWidth() * 25)  / 2) - ((9 * 25) / 2));
    }
  SDL_BlitSurface(texte, NULL, screen, &position);
  TTF_CloseFont(police); 
  SDL_FreeSurface(texte);
}

void            Gui::aff_retry(std::string const &aff, std::string const &aff2) const
{
  SDL_Surface	*texte;
  SDL_Surface	*texte2;
  SDL_Rect	position;
  TTF_Font	*police;
  const SDL_Color	white = {255, 255, 255};

  police = TTF_OpenFont("./sdl/police/geek.ttf", 100);  
  texte = TTF_RenderText_Blended(police, aff.c_str(), white);
   position.y = (((m_nibbler.getHeight() * 25) / 2));
   position.x = (((m_nibbler.getWidth() * 25)  / 2) - ((aff.size() * 50) / 2)); 
  SDL_BlitSurface(texte, NULL, screen, &position);
  police = TTF_OpenFont("./sdl/police/geek.ttf", 50);
  texte2 = TTF_RenderText_Blended(police, aff2.c_str(), white);
  position.y = (((m_nibbler.getHeight() * 25) / 2)) + 150;
  position.x = (((m_nibbler.getWidth() * 25)  / 2) - ((aff2.size() * 25) / 2));
  SDL_BlitSurface(texte2, NULL, screen, &position);
 
  TTF_CloseFont(police); 
  SDL_FreeSurface(texte);
  SDL_Flip(screen);
}
  
extern "C"
{
  AGui	*create(Nibbler &map)
  {
    return (new Gui(map));
  }
}
