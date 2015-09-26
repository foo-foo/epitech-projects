//
// BadCommandError.hpp for avm in /home/menich_a/rendu/avm
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sat Feb 21 14:41:49 2015 Anatole Menichetti
// Last update Thu Apr 23 10:51:58 2015 Anatole Menichetti
//

#ifndef ARGERROR_HPP_
# define ARGERROR_HPP_

# include <iostream>
# include "PlazzaError.hpp"

class	BadCommandError : public PlazzaError
{
public:
  BadCommandError(std::string const &, std::string const &);
  virtual ~BadCommandError() throw();
};

#endif /* !ARGERROR_HPP_ */
