//
// Gui.cpp for nibbler in /home/menich_a/bkp_nib4
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sun Apr  5 10:03:59 2015 Anatole Menichetti
// Last update Sun Apr  5 23:26:42 2015 audurier julien
//

#include <unistd.h>
#include <algorithm>
#include <sstream>
#include "Gui.hh"

/*
**	Constructor: init termcaps and nibbler.
*/
Gui::Gui(Nibbler &nibbler) :
  AGui(nibbler), m_win(0)
{
  initTermcaps();
  initMap();
}

/*
**	Destructor: display score, destroy main window and tc window.
*/
Gui::~Gui()
{
  destroyWindow();
  endwin();
}

/*
**	Init every termcaps attribute.
*/
void	Gui::initTermcaps()
{
  if (initscr() == NULL)
    throw (NibError("ncurses_initscr", "fail"));

  if (cbreak() == -1)  // To receive chars when they are typed and still catch SIGINT, SIGTERM (!= raw()).
    throw (NibError("ncurses_cbreak", "fail"));
  if (keypad(stdscr, TRUE) == -1) // To catch special keys.
    throw (NibError("ncurses_keypad", "fail"));
  if (noecho() == -1) // To hide user keys typed.
    throw (NibError("ncurses_noecho", "fail"));
  if (curs_set(0) == -1) // To hide cursor.
    throw (NibError("ncurses_curs_set", "fail"));
  if (start_color() == -1)
    throw (NibError("ncurses_start_color", "fail"));
  init_pair(1, COLOR_BLACK, COLOR_GREEN);
  init_pair(2, COLOR_RED, COLOR_WHITE);
  init_pair(3, COLOR_MAGENTA, COLOR_WHITE);
  init_pair(4, COLOR_YELLOW, COLOR_GREEN);
  init_pair(5, COLOR_BLACK, COLOR_WHITE);
  createWindow();
}

/*
**	Init the map.
*/
void	Gui::initMap() const
{
  size_t	x = 0;
  size_t	y = 1;
  size_t const	width = m_nibbler.getWidth();
  size_t const	height = m_nibbler.getHeight();
  std::string	map = m_nibbler.getMap();

  while (x < width * height)
    {
      if (wmove(m_win, y++, 1) == -1)
	throw (NibError("ncurses_wmove", "fail"));
      if (wrefresh(m_win) == -1)
	throw (NibError("ncurses_wrefresh", "fail"));
      if (waddstr(m_win, map.substr(x, width).c_str()) == -1)
	throw (NibError("ncurses_waddstr", "fail"));
      x += width;
    }
  if (wmove(m_win, height + 1, 0) == -1)
    throw (NibError("ncurses_wmove", "fail"));
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
  x = 0;
  while (x++ <= width)
    {
      if (waddch(m_win, '#') == -1)
	throw (NibError("ncurses_waddch", "fail"));
    }
  
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
  if (wmove(m_win, height + 2, width / 2) == -1)
    throw (NibError("ncurses_wmove", "fail"));
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
  if (waddch(m_win, '0') == -1)
    throw (NibError("ncurses_waddch", "fail"));
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_refresh", "fail"));
}

/*
**	Create the main window and center it.
*/
void	Gui::createWindow()
{
  size_t	x;
  size_t	y;
  size_t const	width = m_nibbler.getWidth();
  size_t const	height = m_nibbler.getHeight();

  x = (COLS - width) / 2;
  y = (LINES - height) / 2;
  m_win = newwin(height + 4, width + 2, y - 1, x - 1);
  if (m_win == NULL)
    throw (NibError("ncurses_newwin", "fail"));
  if (wborder(m_win, '#', '#', '#', '#', '#', '#', '#', '#') == -1)
    throw (NibError("ncurses_wborder", "fail"));
  if (keypad(m_win, TRUE) == -1)
    throw (NibError("ncurses_keypad", "fail"));
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
  if (wbkgd(m_win, COLOR_PAIR(2)) == -1)
      throw (NibError("ncurses_wbkgd", "fail"));
  wtimeout(m_win, 3000); // To set wgetch blocking delay to 3s.
}

/*
**	Clear refresh and delete the main window.
*/
void	Gui::destroyWindow()
{
  if (wborder(m_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ') == -1)
    throw (NibError("ncurses_wborder", "fail"));
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
  if (delwin(m_win) == -1)
    throw (NibError("ncurses_delwin", "fail"));
}

/*
**	Refresh the map.
*/
void	Gui::dump()
{
  size_t	x = 0;
  size_t	y = 1;
  size_t const	width = m_nibbler.getWidth();
  size_t const	height = m_nibbler.getHeight();
  std::string	map = m_nibbler.getMap();
  std::ostringstream	os;

  os << m_nibbler.getScore();
  if (wmove(m_win, height + 2, width / 2 - os.str().size() / 2) == -1)
    throw (NibError("ncurses_wmove", "fail"));
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
  if (waddstr(m_win, os.str().c_str()) == -1)
    throw (NibError("ncurses_waddstr", "fail"));
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
  while (x < width * height)
    {
      if (wmove(m_win, y++, 1) == -1)
	throw (NibError("ncurses_wmove", "fail"));
      if (wrefresh(m_win) == -1)
	throw (NibError("ncurses_wrefresh", "fail"));
      std::string line(map.substr(x, width).c_str());
      std::for_each(line.begin(), line.end(), bind1st(std::mem_fun(&Gui::tcPutchar), this));
      x += width;
    }
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
}

/*
**	Display a character with attributes according to its role.
*/
void	Gui::tcPutchar(char c) const
{
  int	color = 2;
  int	colors[] = { 1, 4, 3, 3, 3 };
  char	chars[] = { 'X', 'x', 'o', '@', '@'};

  if (c >= '0' && c <= '4')
    {
      c -= 48;
      color = colors[c];
      c = chars[c];
    }
  if ( wattron(m_win, COLOR_PAIR(color)) == -1)
    throw (NibError("ncurses_wattron", "fail"));
  if (waddch(m_win, c) == -1)
    throw (NibError("ncurses_waddch", "fail"));
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
  if (wattroff(m_win, COLOR_PAIR(color)) == -1)
    throw (NibError("ncurses_wattroff", "fail"));
}

/*
**	Clear window (or part of) with some blank spaces.
*/
void	Gui::tcPutstr(size_t const &height, size_t const &width) const
{
  size_t	x;
  size_t	y = 0;

  while (++y <= height)
    {
      x = 0;
      while (++x < width + 1)
	{
	  if (wmove(m_win, y, x) == -1)
	    throw (NibError("ncurses_wmove", "fail"));
	  if (wrefresh(m_win) == -1)
	    throw (NibError("ncurses_refresh", "fail"));
	  if (waddch(m_win, ' ') == -1)
	    throw (NibError("ncurses_waddch", "fail"));
	}
    }
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
}

/*
**	Display a message for Game Over panel.
*/
void	Gui::tcPutmsg(size_t y, size_t const &width, std::string const &msg) const
{
  size_t	x = 0;

  while (++x < width + 1)
    {
      if (wmove(m_win, y, x) == -1)
	throw (NibError("ncurses_wmove", "fail"));
      if (wrefresh(m_win) == -1)
	throw (NibError("ncurses_wmove", "fail"));
      if (x == width / 2 - msg.size() / 2)
	{
	  if (wattron(m_win, COLOR_PAIR(5)) == -1)
	    throw (NibError("ncurses_wattron", "fail"));
	  x += msg.size() - 1;
	  if (waddstr(m_win, msg.c_str()) == -1)
	    throw (NibError("ncurses_waddstr", "fail"));
	  if (wrefresh(m_win) == -1)
	    throw (NibError("ncurses_wrefresh", "fail"));
	  if (wattroff(m_win, COLOR_PAIR(5)) == -1)
	    throw (NibError("ncurses_wattroff", "fail"));
	}
      else
	if (waddch(m_win, ' ') == -1)
	  throw (NibError("ncurses_waddch", "fail"));
    }
}

/*
**	Display a choice for Game Over panel.
*/
void	Gui::tcPutchoice(size_t y, size_t const &width, bool const retry, std::string const &choice) const
{
  size_t	x = 0;

  while (++x < width + 1)
    {
      if (wmove(m_win, y, x) == -1)
	throw (NibError("ncurses_wmove", "fail"));
      if (wrefresh(m_win) == -1)
	throw (NibError("ncurses_wrefresh", "fail"));
      if (x == width / 2 - choice.size() / 2)
	{
	  x += choice.size() - 1;
	  if (retry == true)
	    {
	      if (wattroff(m_win, COLOR_PAIR(5)) == -1)
		throw (NibError("ncurses_wattroff", "fail"));
	      if (wattron(m_win, COLOR_PAIR(2)) == -1)
		throw (NibError("ncurses_wattron", "fail"));
	      if (wattron(m_win, A_UNDERLINE) == -1)
		throw (NibError("ncurses_wattron", "fail"));
	    }
	  if (waddstr(m_win, choice.c_str()) == -1)
	    throw (NibError("ncurses_waddstr", "fail"));
	  if (wrefresh(m_win) == -1)
	    throw (NibError("ncurses_wrefresh", "fail"));
	  if (retry == true)
	    {
	      if (wattroff(m_win, COLOR_PAIR(2)) == -1)
		throw (NibError("ncurses_wattroff", "fail"));
	      if (wattron(m_win, COLOR_PAIR(5)) == -1)
		throw (NibError("ncurses_wattron", "fail"));
	      if (wattroff(m_win, A_UNDERLINE) == -1)
		throw (NibError("ncurses_wattron", "fail"));
	    }
	}
      else
	if (waddch(m_win, ' ') == -1)
	  throw (NibError("ncurses_waddch", "fail"));
    }
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
}

/*
**	Display a Game Over panel using tcPut* methods.
*/
bool	Gui::gameOver(int key)
{
  size_t const	height = m_nibbler.getHeight();
  size_t const	width = m_nibbler.getWidth();
  bool		retry = false;

  usleep(100000);
  if (wattron(m_win, COLOR_PAIR(2)) == -1)
    throw (NibError("ncurses_wattron", "fail"));
  tcPutstr(height, width);
  tcPutmsg(height, width, "SCORE");
  tcPutmsg(height / 3, width, "GAME OVER");
  if (wattroff(m_win, COLOR_PAIR(2)) == -1)
    throw (NibError("ncurses_wattroff", "fail"));
  if (wattron(m_win, COLOR_PAIR(5)) == -1)
    throw (NibError("ncurses_wattron", "fail"));
  while (key != ESCAPE && key != '\n')
    {
      key = 0;
      tcPutchoice(height / 2, width, retry, "RETRY");
      tcPutchoice(height / 2 + 2, width, !retry, "QUIT");
      while ((key = wgetch(m_win)) != ESCAPE && key != ENTER &&
	     key != KEY_UP && key != KEY_DOWN);
      if (key == KEY_DOWN || key == KEY_UP)
	retry = !retry;
    }
  if (wrefresh(m_win) == -1)
    throw (NibError("ncurses_wrefresh", "fail"));
  if (retry)
    {
      m_nibbler.retry();
      usleep(25000);
      return (false);
    }
  return (true);
}

/*
**	Handle events received (arrows, space, esc...).
*/
void	Gui::handleEvents()
{
  int	key = wgetch(m_win);

  if (key == -1)
    throw (NibError("ncurses_wgetch", "fail"));

  while (m_state == ENABLE)
    {
      while (key != ESCAPE && m_nibbler.isActive())
	{
	  if (key == KEY_LEFT)
	    m_nibbler.turn_left();
	  if (key == KEY_RIGHT)
	    m_nibbler.turn_right();
	  key = 0;
	  while ((key = wgetch(m_win)) != ESCAPE && key != ' ' && m_nibbler.isActive() &&
		 key != KEY_LEFT && key != KEY_RIGHT);
	  if (key == ' ')
	    m_nibbler.boost();
	}
      if (key == ESCAPE)
	m_nibbler.disable();
      if (gameOver(key) == true)
	m_state = DISABLE;
    }
}

/*
**	Return event handler capability.
*/
bool	Gui::getEvent() const
{
  return (true);
}

/*
**	Return a new abstract class AGui of real type Gui.
*/
extern "C"
{
  AGui	*create(Nibbler &nibbler)
  {
    return (new Gui(nibbler));
  }
}
