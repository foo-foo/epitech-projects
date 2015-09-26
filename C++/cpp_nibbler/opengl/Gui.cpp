//
// Gui.cpp for  in /home/bencha_a/Nibler
// 
// Made by Aniss Bencharif
// Login   <bencha_a@epitech.net>
// 
// Started on  Wed Mar 25 11:07:01 2015 Aniss Bencharif
// Last update Sun Apr  5 23:34:35 2015 audurier julien
// Last update Sun Apr  5 21:35:05 2015 audurier julien
// Last update Sun Apr  5 20:25:54 2015 audurier julien
//

#include "Gui.hh"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <unistd.h>

Gui::Gui(Nibbler &nibbler) : AGui(nibbler)
{
  size_t	height = nibbler.getHeight();
  size_t	width = nibbler.getWidth();

  height_base = static_cast<double>(2) / static_cast<double>(height);
  weight_base = static_cast<double>(2) / static_cast<double>(width);
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw (NibError("opengl_SDL_init", "fail"));
  if (atexit(SDL_Quit) != 0)
    throw (NibError("opengl_atexit", "fail"));
  TTF_Init();
  if (SDL_SetVideoMode(width * 25,  height * 25, 16, SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF) == NULL)
    throw (NibError("opengl_SDL_SetVideoMode", "fail"));
  SDL_WM_SetCaption("nibbler OpenGL", NULL);
}

void            Gui::aff_score(int const game_over) const
{
  SDL_Surface   *texte;
  SDL_Rect      position;
  TTF_Font      *police;
  const SDL_Color     white = {255, 255, 255};
  std::ostringstream    os;

  os << m_nibbler.getScore();
  os.str();
  if (game_over == 0)
    {
      police = TTF_OpenFont("./sdl/police/geek.ttf",40);
      texte = TTF_RenderText_Blended(police, os.str().c_str(), white);
      position.x = 300;
      position.y = 300;
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
  SDL_Surface   *texte;
  SDL_Surface   *texte2;
  SDL_Rect      position;
  TTF_Font      *police;
  SDL_Color const     white = {255, 255, 255};

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

void    Gui::gameOver()
{
  bool  retry = false;
  int   s_event = 0;
  SDL_Event event;

  screen = SDL_SetVideoMode(m_nibbler.getWidth() * 25, m_nibbler.getHeight() * 25, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
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
  m_state = DISABLE;
  SDL_Quit();
}

void    Gui::handleEvents()
{
  int   s_event = 0;
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

    }
  else
    if (!m_nibbler.isActive())
      gameOver();
}

void             Gui::init_picture(std::string const &nibbler) const
{
  int           i;
  int           x;
  int           y;

  i = 0;
  while (i < nibbler.size())
    {
      get_pos(&x, &y, nibbler[i], i);
      if (x != -42)
	{
	  if (nibbler[i] == '2')
	    Draw_quads(x, y, 255, 0,0);
	  else if (nibbler[i] == '3' || nibbler[i] == '4')
	    Draw_quads(x, y, 255, 51, 153);
	  else if (nibbler[i] == '0')
	    Draw_quads(x, y, 51, 255, 0);
	  else
	    Draw_quads(x, y, 51, 102, 0);
	}
      i++;
    }

}

void	Gui::Draw_quads(int const x, int const y, int const r, int const g, int const b) const
{
  double	X;
  double	Y; 

  glBegin(GL_QUADS);
  glColor3ub(r,g,b);

  X = (static_cast<double>(x) - (static_cast<double>(m_nibbler.getWidth()) / static_cast<double>(2) )) * static_cast<double>(weight_base);
  if (x > ((static_cast<int>(m_nibbler.getWidth()))))
    X = X * (- 1); 
  Y = (static_cast<double>(y) - (static_cast<double>(m_nibbler.getHeight()) / static_cast<double>(2) )) * static_cast<double>(height_base);
  if (y < ((static_cast<int>(m_nibbler.getHeight()))))
    Y = Y * (- 1); 
  glVertex2d(X , (Y - height_base));
  glVertex2d(X , Y);
  glVertex2d((X + weight_base), Y);
  glVertex2d((X + weight_base), (Y - height_base));
}

void	Gui::dump() 
{
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  init_picture(m_nibbler.getMap());
  glEnd();
  glFlush();
  aff_score(0);
  SDL_GL_SwapBuffers();   
  handleEvents(); 
}

void           Gui::adjust_size(int *x, int *y, int const i) const
{
  size_t const        width = m_nibbler.getWidth();
  size_t const        height = m_nibbler.getHeight();

  *x = i % width;
  *y = ((i - i % width) / width);
}

void            Gui::get_pos(int *x, int *y, char const map, int const i) const
{
  if (map != ' ')
    adjust_size(x, y, i);
  else
    *x = -42;
}

Gui::~Gui()
{

}

extern "C"
{
  AGui  *create(Nibbler &nibbler)
  {
    return (new Gui(nibbler));
  }
}
