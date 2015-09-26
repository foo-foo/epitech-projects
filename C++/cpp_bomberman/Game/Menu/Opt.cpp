//
// Opt.cpp for bomberman in /home/arthur/rendu/cpp_bomberman/Game/config
// 
// Made by Arthur Le Meur
// Login   <le-meu_a@epitech.net>
// 
// Started on  Sat Jun 13 17:11:46 2015 Arthur Le Meur
// Last update Sat Jun 13 17:49:26 2015 Arthur Le Meur
//

#include <iostream>
#include <sstream>
#include "Opt.hpp"

Opts::Opts(std::string filename)
{
  m_file.open(filename.c_str(), std::ios::in);
  if (m_file)
    {
      std::string	l;
      while (std::getline(m_file, l))
	{
	  std::vector<std::string> temp = split(l, ':');
	  m_content.push_back(temp[1]);
	}
      m_file.close();
      m_nbIa = std::stoi(m_content[3]);
      m_levelIa = std::stoi(m_content[4]);
    }
  else
    {
      m_nbIa = 1;
      m_levelIa = 1;
    }
}

Opts::~Opts()
{
}

int	Opts::getNbIa() const
{
  return (m_nbIa);
}

int	Opts::getLevelIa() const
{
  return (m_levelIa);
}

void	Opts::debug() const
{
  std::cout << "nb IA : " << m_nbIa << std::endl << "level IA : " << m_levelIa << std::endl;
}

std::vector<std::string>	Opts::split(std::string str, char delimiter)
{
  std::vector<std::string> internal;
  std::stringstream ss(str);
  std::string tok;

  while(getline(ss, tok, delimiter))
    {
      internal.push_back(tok);
    }
  return internal;
}
