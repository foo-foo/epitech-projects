#ifndef NAMEDPIPE_HPP_
# define NAMEDPIPE_HPP_

# include <string>

class	NamedPipe
{
private:
  std::string	_path;
  int		_fd;

public:
  NamedPipe(std::string str);
  ~NamedPipe();

  int	openPipeRd();
  int	openPipeWr();
};

#endif
