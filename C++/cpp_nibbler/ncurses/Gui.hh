//
// Gui.hh for nibbler in /home/menich_a/rendu/cpp_nibbler
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sun Apr  5 17:35:56 2015 Anatole Menichetti
// Last update Sun Apr  5 22:32:27 2015 audurier julien
//

#ifndef GUI_HH_
# define GUI_HH_

# include <ncurses.h>
# include "../includes/AGui.hh"
# include "../includes/NibError.hh"

/*
** Keys
*/
# define ESCAPE	(27)
# define ENTER	(10)

class		Gui : public AGui
{
private:
  WINDOW	*m_win; // Main window.

public:
  Gui(Nibbler &); // Dtor
  virtual ~Gui(); // Ctor

  virtual void	handleEvents(); // Handle events (arrows, space, esc...)
  virtual void	dump(); // Refresh the map

  virtual bool	getEvent() const; // Return event handler

private:
  void		createWindow();  // Create main window.
  void		destroyWindow(); // Destroy main window.

  void		initTermcaps(); // Init termcaps.
  void		initMap() const; // Init the map.

  void		tcPutchar(char) const; // Display a char with attributes according to its role.
  void		tcPutstr(size_t const &, size_t const &) const; // Clear (with blank) the screen.
  void		tcPutmsg(size_t, size_t const &, std::string const &) const; // Display a message after game is over
  void		tcPutchoice(size_t, size_t const &, bool const, std::string const &) const; // Display a choice after game is over
  bool		gameOver(int); // Display a game over panel by calling tcPut methods.
};

#endif  /* !GUI_HH_ */
