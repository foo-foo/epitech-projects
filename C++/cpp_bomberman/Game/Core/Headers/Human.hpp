//
// Human.hpp for  in /home/menich_a/Downloads/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 11:11:22 2015 Anatole Menichetti
// Last update Sun Jun 14 15:38:38 2015 Anatole Menichetti
//

#ifndef _HUMAN_HPP_
# define _HUMAN_HPP_

# include <SFML/Audio.hpp>
# include <iostream>
# include <vector>

/* Objects */

# include "Clock.hh"
# include "Input.hh"
# include "Field.hpp"

/* Human */

# include "APlayer.hpp"
# include "Bomb.hpp"
# include "ABonus.hpp"

enum	e_inputKey
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    PUT_BOMB
  };

class	Human : public APlayer
{
private:
  std::vector<int>	_inputKeys;
  gdl::Input		&_input;
  sf::Sound		&_pickBonusSound;
  sf::Sound		&_putBombSound;

  bool			_checkInput(float const y, float const x, Field& map);
  std::vector<int>&	getInputKeys();
  void			setInputKeys(int const, int const, int const, int const, int const);
  bool			tryMove(Field &field, int const move, float const x, float const y, float const add);

public:

  Human(Character* const character, gdl::Input &input, size_t const id, sf::Sound &, sf::Sound &);
  virtual ~Human() {};

  virtual void	update(gdl::Clock const &, Field&);

  virtual bool	isHuman() const;
};

#endif /* !_HUMAN_HPP_ */
