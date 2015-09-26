//
// RuntimeError.hpp for avm in /home/menich_a/rendu/avm
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sat Feb 21 14:41:49 2015 Anatole Menichetti
// Last update Thu Apr 23 11:12:01 2015 Anatole Menichetti
//

#ifndef RUNTIMEERROR_HPP_
# define RUNTIMEERROR_HPP_

# include <iostream>
# include "PlazzaError.hpp"

class	RuntimeError : public PlazzaError
{
public:
  RuntimeError(std::string const &, std::string const &);
  virtual ~RuntimeError() throw();
};

#endif /* !RUNTIMEERROR_HPP_ */
