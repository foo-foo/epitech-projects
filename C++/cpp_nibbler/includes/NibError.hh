//
// NibError.hh for nibbler in /home/menich_a/rendu/cpp_nibbler
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Fri Apr  3 10:52:32 2015 Anatole Menichetti
// Last update Fri Apr  3 11:37:40 2015 Anatole Menichetti
//

#ifndef NIBERROR_HH_
# define NIBERROR_HH_

# include <iostream>

class	NibError : public std::exception
{
public:
  NibError(std::string const &, std::string const &);
  virtual ~NibError() throw();

  virtual const char	*what() const throw();

private:
  std::string		m_message;
  std::string		m_type;
};

#endif /* !ERRORS_HH_ */
