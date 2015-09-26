//
// RuntimeError.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs/exceptions
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Apr 23 10:38:20 2015 Anatole Menichetti
// Last update Thu Apr 23 11:11:26 2015 Anatole Menichetti
//

#include "RuntimeError.hpp"

RuntimeError::RuntimeError(std::string const &type, std::string const &message) : PlazzaError(type, message)
{}

RuntimeError::~RuntimeError() throw()
{}
