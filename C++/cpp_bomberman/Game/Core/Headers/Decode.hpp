//
// Decode.hh for Decode in /home/rosain_f/rendu/cpp_abstractvm
//
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
//
// Started on  Tue Feb 17 21:19:22 2015 Francois Rosain
// Last update Sat Jun 13 10:25:19 2015 Anatole Menichetti
//

#ifndef _DECODE_HH_
# define _DECODE_HH_

# include <string>
# include <map>
# include "BombEngine.hpp"
# include "AObject.hpp"

class BombEngine;
typedef void (BombEngine::*pfctreac)(int const y, int const x, int &tmp, int power);
typedef void (BombEngine::*pfctdiff)(int const y, int const x);

class	Decode
{
private:
  std::map<e_object, pfctreac>      _flameReac;
  std::map<e_object, pfctdiff>      _flameDiffus;

public:
  Decode();
  ~Decode();

  void		reaction(e_object const type, BombEngine *bombEngine,
			 int const y, int const x, int &tmp, int power = 0) const;
  void		diffusion(e_object const type, BombEngine *bombEngine,
			  int const y, int const x) const;
};

#endif /* !_DECODE_HH_ */
