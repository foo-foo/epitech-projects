//
// PlazzaError.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs/exceptions
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Apr 23 10:46:05 2015 Anatole Menichetti
// Last update Thu Apr 23 10:46:11 2015 Anatole Menichetti
//

#include "PlazzaError.hpp"

PlazzaError::PlazzaError(std::string const &type, std::string const &message) : m_message(message), m_type(type)
{}

PlazzaError::~PlazzaError() throw()
{}

const char    *PlazzaError::what() const throw()
{
  return ((m_type + " error: " + m_message).c_str());
}
