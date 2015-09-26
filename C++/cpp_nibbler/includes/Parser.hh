//
// Parser.hh for nibbler in /home/menich_a/rendu/cpp_nibbler/includes
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Apr  2 15:20:52 2015 Anatole Menichetti
// Last update Sun Apr  5 19:34:19 2015 Anatole Menichetti
//

#ifndef PARSER_HH_
# define PARSER_HH_

# include <iostream>

/*
** Messages
*/
# define USAGE_MSG	"[WIDTH] [HEIGHT] [GUI]"
# define ELIB_MSG	\
"nibbler: error: invalid parameter gui: \
must be [lib_nibbler_ncurses | lib_nibbler_sdl.so | lib_nibbler_opengl.so]."

/*
** Limits
*/
# define MIN_SIZE	(20)
# define MAX_SIZE	(40)

/*
** Dynamic librairies
*/
# define LNCURSES	"./lib_nibbler_ncurses.so"
# define LSDL		"./lib_nibbler_sdl.so"
# define LOPENGL	"./lib_nibbler_opengl.so"

class			Parser
{
  int			status; // Status of the parsing (to catch many errors).
  std::string		gui; // The library name.
  size_t		width; // The GUI width
  size_t		height; // The GUI height.

public:
  Parser(int ac, char **av);
  ~Parser();

  int			getStatus() const;
  std::string const &	getGui() const;
  size_t		getWidth() const;
  size_t		getHeight() const;

private:
  void			setGui(std::string const &);
  void			checkSizeFlow(size_t, std::string const &, size_t, std::string const &, std:: string const &);
  size_t		setSize(std::string const &, std::string const &);
  void			checkUsage(int, std::string const &);
};

#endif /* !PARSER_HH_ */
