//
// main.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed Apr 15 17:39:52 2015 Anatole Menichetti
// Last update Sun Apr 26 15:25:16 2015 Francois Rosain
//

#include <cstdlib>
#include <pthread.h>
#include "../includes/Parser.hpp"
#include "../includes/Reception.hpp"
#include "../includes/PlazzaError.hpp"

void* main_ui(void *reception);

int		main(int ac, char **av)
{
  pthread_t   ui_thread;

  try
    {
      Parser	parser(ac, av);
      Reception	reception(parser);

      pthread_create(&ui_thread, NULL, &main_ui, &reception);
      reception.start();
    }
  catch (PlazzaError &e)
    {
      std::cerr << std::string(av[0]) << ": " << e.what() << "." << std::endl;
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
