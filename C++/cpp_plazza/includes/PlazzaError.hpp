//
// PlazzaError.hpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/includes
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Apr 23 10:46:56 2015 Anatole Menichetti
// Last update Thu Apr 23 10:52:14 2015 Anatole Menichetti
//

#ifndef PLAZZAERROR_HPP_
# define PLAZZAERROR_HPP_

#include <iostream>

class	PlazzaError : public std::exception
{
public:
  PlazzaError(std::string const &, std::string const &);
  virtual ~PlazzaError() throw();

  virtual const char	*what() const throw();

private:
  std::string		m_message;
  std::string		m_type;
};

#endif /* !PLAZZAERROR_HPP_ */
