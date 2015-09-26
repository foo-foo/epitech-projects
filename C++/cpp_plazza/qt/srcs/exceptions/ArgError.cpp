//
// ArgError.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs/exceptions
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Apr 23 10:38:20 2015 Anatole Menichetti
// Last update Thu Apr 23 10:49:45 2015 Anatole Menichetti
//

#include "../../includes/ArgError.hpp"

ArgError::ArgError(std::string const &type, std::string const &message) : PlazzaError(type, message)
{}

ArgError::~ArgError() throw()
{}
