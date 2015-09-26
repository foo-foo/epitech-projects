//
// BadCommandError.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs/exceptions
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Apr 23 10:38:20 2015 Anatole Menichetti
// Last update Thu Apr 23 11:34:12 2015 Anatole Menichetti
//

#include "BadCommandError.hpp"

BadCommandError::BadCommandError(std::string const &type, std::string const &message) : PlazzaError(type, message)
{}

BadCommandError::~BadCommandError() throw()
{}
