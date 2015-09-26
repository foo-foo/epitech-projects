//
// main.cpp for nibbler in /home/menich_a/bkp_nib4
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sun Apr  5 10:03:28 2015 Anatole Menichetti
// Last update Sun Apr  5 22:18:32 2015 audurier julien
//

#include <thread>
#include <cstdlib>
#include <unistd.h>
#include "../includes/AGui.hh"
#include "../includes/Parser.hh"
#include "../includes/DLLoader.hh"
#include "../includes/NibError.hh"
#include "../includes/Nibbler.hh"

void		my_call_event(AGui *gui)
{
  if (gui->getEvent())
    gui->handleEvents();
}

int		main(int ac, char **av)
{
  try
    {
      Parser	parser(ac, av);
      AGui	*gui;

      if (parser.getStatus() == EXIT_FAILURE)
	{
	  throw (NibError("parseur", "fail"));
	  return (EXIT_FAILURE);
	}

      Nibbler	nibbler(parser.getWidth(), parser.getHeight());
      DLLoader	loader(parser.getGui(), nibbler);

      gui = loader.getInstance();

      std::thread	event(my_call_event, gui);

      while (gui->isActive())
	if (gui->gaming())
	  {
	    nibbler.go();
	    gui->dump();
	    usleep(nibbler.getSpeed());
	    if (nibbler.getSpeed() > ACCELERATION)
	      nibbler.speed(ACCELERATION);
	  }
      event.join();
      delete gui;
    }
  catch (NibError const &e)
    {
      std::cerr << av[0] << ": " << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
