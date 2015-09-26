//
// main.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed Apr 15 17:39:52 2015 Anatole Menichetti
// Last update Sun Apr 26 16:37:54 2015 Anatole Menichetti
//

#include <cstdlib>
#include "Parser.hpp"
#include "Reception.hpp"
#include "PlazzaError.hpp"

int		main(int const ac, char** const av)
{
  try
    {
      Parser const	parser(ac, av);
      Reception		reception(parser);

      reception.start();
    }
  catch (PlazzaError const &e)
    {
      std::cerr << std::string(av[0]) << ": " << e.what() << "." << std::endl;
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
