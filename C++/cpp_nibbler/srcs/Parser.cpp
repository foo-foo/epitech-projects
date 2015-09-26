//
// Parser.cpp for nibbler in /home/menich_a/rendu/cpp_nibbler/srcs
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Apr  2 15:14:57 2015 Anatole Menichetti
// Last update Fri Apr  3 21:57:18 2015 Anatole Menichetti
//

#include <cstdlib>
#include <sstream>
#include "../includes/Parser.hh"

Parser::Parser(int ac, char **av) : status(EXIT_SUCCESS), gui("")
{
  checkUsage(ac, av[0]);
  if (!status)
    {
      width = setSize(av[1], "width");
      height = setSize(av[2], "height");
      setGui(av[3]);
    }
}

Parser::~Parser()
{}

void		Parser::checkSizeFlow(size_t size, std::string const &type, size_t limit, std::string const &flow, std::string const &lim)
{
  if ((flow == "underflow" && size < limit) || (flow == "overflow" && size > limit))
    {
      std::cerr << "nibbler: error: " << flow << " in paramer " << type << " (" << size << "): " << lim << " value is " << limit << "." << std::endl;
      status = EXIT_FAILURE;
    }
}

size_t		Parser::setSize(std::string const &size, std::string const &type)
{
  size_t	s = 0;

  if (size.find_first_not_of("0123456789") != std::string::npos)
    {
      std::cerr << "nibbler: error: invalid paramer " << size << ": " << type << " must be an unsigned integer." << std::endl;
      status = EXIT_FAILURE;
    }
  else
    {
      std::istringstream	is(size);

      is >> s;
      checkSizeFlow(s, type, MIN_SIZE, "underflow", "minimum");
      checkSizeFlow(s, type, MAX_SIZE, "overflow", "maximum");
    }
  return (s);
}

void		Parser::checkUsage(int ac, std::string const &binaryName)
{
  if (ac != 4)
    {
      std::cerr << "nibbler: usage: " << binaryName << " " << USAGE_MSG << std::endl;
      status = EXIT_FAILURE;
    }
}

int		Parser::getStatus() const
{
  return (status);
}

size_t		Parser::getWidth() const
{
  return (width);
}

size_t		Parser::getHeight() const
{
  return (height);
}

void		Parser::setGui(std::string const &name)
{
  if (name[0] != '.' && name[1] != '/')
    gui = "./";
  gui += name;
  if (gui != LNCURSES && gui != LSDL && gui != LOPENGL)
    {
      std::cerr << ELIB_MSG << std::endl;
      status = EXIT_FAILURE;
    }
}

std::string const	&Parser::getGui() const
{
  return (gui);
}
