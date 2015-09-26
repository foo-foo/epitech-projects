//
// Teub.cpp for  in /home/menich_a/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 16:26:29 2015 Anatole Menichetti
// Last update Sat Jun 13 10:40:34 2015 Anatole Menichetti
//

#include "Teub.hpp"

Teub::Teub(Character* const character, size_t const id) :
  Undecided(character, id)
{}

int	Teub::getNbrHit(std::vector<std::vector <AObject*> > const &, size_t const, size_t const) const
{
  return (rand() % 4);
}
