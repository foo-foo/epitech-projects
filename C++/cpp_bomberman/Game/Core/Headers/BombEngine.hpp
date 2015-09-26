//
// BombEngine.hpp for  in /home/menich_a/rendu/bomberbkp/Game/Game/Headers
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sat Jun 13 09:32:01 2015 Anatole Menichetti
// Last update Sat Jun 13 09:46:50 2015 Anatole Menichetti
//

#ifndef BOMBENGINE_HPP_
# define BOMBENGINE_HPP_

/* BombEngine */

# include <typeinfo>
# include <iostream>
# include <unistd.h>
# include <cstdlib>
# include <ctime>

/* Objects */

# include "Thread.hpp"
# include "Field.hpp"
# include "Decode.hpp"
# include "Bomb.hpp"
# include "Flame.hpp"
# include "ABonus.hpp"
/* Bonus */
# include "BonusSpeed.hpp"
# include "BonusPower.hpp"
# include "BonusBomb.hpp"

class Decode;

typedef AObject* (*fct_ptr)(int const, int const, Field &);

class	BombEngine
{
private:

  Thread<BombEngine, char>	_thread;
  Decode			*_decode;
  bool				_boxFlag;
  Field				&_map;
  bool				_flagExit;
  fct_ptr			_bonus[NB_BONUS];

  void		_putFlame(int const y, int const x, int &tmp, int const power);
  void		_diffusionFlame(int const y, int const x, int const power);
  AObject*	_getRandomBonus(int const y, int const x) const;
  static AObject*	_createBonusSpeed(int const, int const, Field &);
  static AObject*	_createBonusPower(int const, int const, Field &);
  static AObject*	_createBonusBomb(int const, int const, Field &);

public:
  BombEngine(Field &map);
  ~BombEngine();

  Field&	getMap() const;
  void	nothingReac(int const y, int const x, int &tmp, int power);
  void	flameReacFlame(int const y, int const x, int &tmp, int power);
  void	flameReacBox(int const y, int const x, int &tmp, int power);
  void	flameReacBomb(int const y, int const x, int &tmp, int power);
  void	flameReacBonus(int const y, int const x, int &tmp, int power);

  void	nothing(int const y, int const x);
  void	flameDiffusBomb(int const y, int const x);
  void	flameDiffusFlame(int const y, int const x);

  void	exitThread();
  void	operator()(char const);
};

#endif //!BOMBENGINE_HPP_
