//
// NibError.cpp for nibbler in /home/menich_a/rendu/cpp_nibbler
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Fri Apr  3 10:55:23 2015 Anatole Menichetti
// Last update Fri Apr  3 11:30:10 2015 Anatole Menichetti
//

#include "../includes/NibError.hh"

NibError::NibError(std::string const &type, std::string const &message) : m_message(message), m_type(type)
{}

NibError::~NibError() throw()
{}

const char    *NibError::what() const throw()
{
  return ((m_type + " error: " + m_message).c_str());
}
