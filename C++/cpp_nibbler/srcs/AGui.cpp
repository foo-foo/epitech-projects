//
// AGui.cpp for nibbler in /home/menich_a/bkp_nib4
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sun Apr  5 10:03:21 2015 Anatole Menichetti
// Last update Sun Apr  5 17:08:38 2015 Anatole Menichetti
//

#include "../includes/AGui.hh"

AGui::AGui(Nibbler &nibbler) : m_nibbler(nibbler), m_state(ENABLE)
{}

AGui::~AGui()
{}

bool	AGui::isActive() const
{
  return (m_state);
}

bool	AGui::gaming() const
{
  return (m_nibbler.isActive());
}

bool	AGui::getEvent() const
{
  return (false);
}
