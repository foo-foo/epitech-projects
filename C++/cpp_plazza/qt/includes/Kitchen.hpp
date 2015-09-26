//
// Kitchen.hpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/includes
//
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
//
// Started on  Wed Apr 15 18:00:51 2015 Anatole Menichetti
// Last update Sat Apr 25 12:20:18 2015 Sebastien Lauret
//

#ifndef KITCHEN_HPP_
# define KITCHEN_HPP_

# include <time.h>
# include <sstream>
# include <unistd.h>
# include <vector>
# include "SafeQueue.hpp"
# include "Resources.hpp"
# include "Command.hpp"
# include "Cook.hpp"
# include "Parser.hpp"
# include "NamedPipe.hpp"

class	Kitchen
{
  Resources				_resources;
  SafeQueue< Command * >		_commands;
  SafeQueue< Command * >		_cmdFinished;
  std::vector< Cook * >			_cooks;
  size_t const				_replaceTime;
  pid_t					_pid;
  size_t				_id;
  std::stringstream			_name;
  KitchenStat					_state;
  NamedPipe				*_pipe1;
  NamedPipe				*_pipe2;
  int					_receive;
  int					_send;
  time_t				_timerEnd;
  time_t				_timerRessoure;
  std::map<std::string, PizzaSize>	_mPizzaSize;
  std::map<std::string, PizzaType>	_mPizzaType;

public:
  Kitchen(Parser const &, std::queue<Command *>&, size_t,
	  std::map<std::string, PizzaSize>&,
	  std::map<std::string, PizzaType>&); // Init parameters and fork.
  ~Kitchen();

  bool	isOpen();
  int	getState();
  Resources &getResources();

  int	start(); // Start the job (if we are in child process).
  void	sendCommand(Command &);
  void	sendUpdate();
  void	receiveUpdate();
  int	nbBusyCook();
private:
  void	selfTakeCommands(size_t, double, std::queue<Command *> &);
  void	takeCommand(); // Add a new command to the queue.
  void	displayCmd();

  void	operator<<(Resources &);
  void	operator<<(t_cmd &);
  void	operator<<(KitchenStat);

  void	operator>>(t_resource &);
  void	operator>>(KitchenStat&);
  int	operator>>(t_cmd &);
};

#endif /* !KITCHEN_HPP_ */
