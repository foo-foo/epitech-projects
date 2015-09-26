//
// Kitchen.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs
//
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
//
// Started on  Wed Apr 15 21:40:06 2015 Anatole Menichetti
// Last update Sat Apr 25 16:02:12 2015 Sebastien Lauret
//

#include <cerrno>
#include <cstring>
#include <cstdlib>
#include "../includes/Kitchen.hpp"
#include "../includes/NamedPipe.hpp"
#include "../includes/RuntimeError.hpp"

Kitchen::Kitchen(Parser const &parameters, std::queue<Command *> &commands, size_t name,
		 std::map<std::string, PizzaSize> &mPizzaSize,
		 std::map<std::string, PizzaType> &mPizzaType) :
  _resources(),
  _replaceTime(parameters.getReplaceTime()),
  _id(name),
  _name(),
  _state(NOFULL),
  _mPizzaSize(mPizzaSize),
  _mPizzaType(mPizzaType)
{
  Command	*cmd;
  size_t	nb = 0;

  _name << _id;
  _pipe1 = new NamedPipe("./." + _name.str() + "a");
  _pipe2 = new NamedPipe("./." + _name.str() + "b");
  if ((_pid = fork()) == -1)
    throw (RuntimeError("fork", strerror(errno)));
  while (nb < parameters.getCooksNbr() * 2)
    {
      if (!commands.empty())
	{
	  cmd = commands.front();
	  commands.pop();
	  cmd->setKitchen(_id);
	  _commands.push(cmd);
	}
      if (!_pid && nb % 2)
	_cooks.push_back(new Cook(_commands, _cmdFinished, parameters.getMultiplier(),
				  _resources, nb, _state, mPizzaSize, mPizzaType));
      nb++;
    }
  t_cmd cmd1;
  cmd1.kitchen = 42;
  if (!_pid)
    {
      _receive = _pipe1->openPipeRd();
      _send = _pipe2->openPipeWr();
      cmd1.kitchen = 0;
      read(this->_receive, &cmd, sizeof(t_cmd));
      std::cout << cmd1.kitchen<<std::endl;
    }
  else
    {
      _send = _pipe1->openPipeWr();
      _receive = _pipe2->openPipeRd();
      write(this->_send, &cmd1, sizeof(t_cmd));
    }
}

Kitchen::~Kitchen()
{
  delete _pipe1;
  delete _pipe2;
}

/* ---------------- */
/* Public functions */
/* ---------------- */

//		Start the job (only if we are in child process).
int		Kitchen::start()
{
  Command	cmd(XL, Regina);

  if (!_pid)
    {
      time(&_timerEnd);
      time(&_timerRessoure);
      while (_state != CLOSE)
	{
	  if (difftime(time(NULL), _timerRessoure) >= _replaceTime)
	    {
	      _resources.regeneResources();
	      time(&_timerRessoure);
	    }
	  if (_commands.size() + nbBusyCook() == 0 && difftime(time(NULL), _timerEnd) >= 5)
	    _state = CLOSE;
	  if (_commands.size() + nbBusyCook() > 0)
	    time(&_timerEnd);
	  sendUpdate();
	  takeCommand();
	  displayCmd();
	}
      return (1);
    }
  return (0);
}

void	Kitchen::displayCmd()
{
  std::map<std::string, PizzaSize>::const_iterator it2 = _mPizzaSize.begin();
  std::map<std::string, PizzaType>::const_iterator it1 = _mPizzaType.begin();
  Command       *cmd;

  while (_cmdFinished.tryPop(&cmd))
    {
      while (it1 != _mPizzaType.end() && it1->second != cmd->getType())
	++it1;
      while (it2 != _mPizzaSize.end() && it2->second != cmd->getSize())
	++it2;
      std::cout << "K : "<< cmd->getKitchen()
		<<" > C : " << cmd->getCook()
		<< " Command prete: " << it1->first << " " << it2->first << "." << std::endl;
      delete cmd;
    }
}

int	Kitchen::nbBusyCook()
{
  size_t	nb = 0, nbBusy = 0;

  while (nb < _cooks.size())
    {
      if (!_cooks[nb]->isFree())
	nbBusy++;
      nb++;
    }
  return (nbBusy);
}

bool	Kitchen::isOpen()
{
  return (_state != CLOSE);
}

int	Kitchen::getState()
{
  return (_state);
}

Resources	&Kitchen::getResources()
{
  return (_resources);
}

void	Kitchen::sendCommand(Command &cmd)
{
  t_cmd	command;

  command = cmd.getCmd();
  *(this) <<  command;
}

void	Kitchen::sendUpdate()
{
  if (_state != CLOSE)
    {
      if (_commands.size() + nbBusyCook() < _cooks.size() * 2)
	_state = NOFULL;
      else
	_state = FULL;
    }
  *(this) << _state;
  *(this) << _resources;
}

/* ----------------- */
/* Private functions */
/* ----------------- */

//	Add a new command to the queue.
void	Kitchen::takeCommand()
{
  t_cmd	cmd;

  if ((*(this) >> cmd) > 0)
    {
      cmd.kitchen = _id;
      _commands.push(new Command(cmd));
    }
}

void	Kitchen::receiveUpdate()
{
  t_resource	res;

  *(this) >> _state;
  *(this) >> res;
}

/* -------------------- */
/* Operators (privates) */
/* -------------------- */

void    Kitchen::operator<<(Resources &)
{
  int	ret;
  t_resource	&val = _resources.getResources();
  ret = write(this->_send, &val, sizeof(t_resource));
  if (ret == -1)
    sleep(2);
  delete &val;
}

void	Kitchen::operator<<(t_cmd &cmd)
{
  int ret;

  ret = write(this->_send, &cmd, sizeof(t_cmd));
  if (ret == -1)
    sleep(2);
}

void    Kitchen::operator<<(KitchenStat nb)
{
  int ret;

  ret = write(this->_send, &nb, sizeof(KitchenStat));
  if (ret == -1)
    sleep(2);
}

void    Kitchen::operator>>(t_resource &res)
{
  int ret;
  if ((ret = read(this->_receive, &res, sizeof(t_resource))) > 0)
    _resources.setResources(res);
  if (ret == -1)
    sleep(2);
}
void    Kitchen::operator>>(KitchenStat &nb)
{
  int	ret;

  ret = read(this->_receive, &nb, sizeof(KitchenStat));
  if (ret == -1)
    sleep(2);
}

int	Kitchen::operator>>(t_cmd &cmd)
{
  int ret;

  ret = read(this->_receive, &cmd, sizeof(t_cmd));
  if (ret == -1)
    sleep(2);
  return (ret);
}
