//
// NamedPipe.hpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sun Apr 26 16:32:31 2015 Anatole Menichetti
// Last update Sun Apr 26 16:32:36 2015 Anatole Menichetti
//

#ifndef NAMEDPIPE_HPP_
# define NAMEDPIPE_HPP_

# include <string>

class	NamedPipe
{
private:
  std::string	_path;
  int		_fd;

public:
  NamedPipe(std::string const &str);
  ~NamedPipe();

  int	openPipeRd();
  int	openPipeWr();
};

#endif
