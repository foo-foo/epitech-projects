//
// GameEngine.hpp for GameEngine in /home/rosain_f/projects/BomberMan/cube/v2
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Tue May  5 10:49:49 2015 Francois Rosain
// Last update Tue Sep 15 10:08:50 2015 Anatole Menichetti
//

#ifndef _GAME_ENGINE_HPP_
# define _GAME_ENGINE_HPP_

# include <unistd.h>
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <list>

/* GameEngine */

# include "Game.hh"
# include "SdlContext.hh"
# include "Clock.hh"
# include "Input.hh"
# include "BasicShader.hh"
# include "Texture.hh"

/* Objects */

# include "AObject.hpp"
# include "Field.hpp"
# include "Wall.hpp"
# include "Box.hpp"
# include "APlayer.hpp"
# include "Character.hpp"
# include "BonusSpeed.hpp"
# include "Human.hpp"

/* IA */

# include "Teub.hpp"
# include "Undecided.hpp"
# include "Recruit.hpp"
# include "Soldier.hpp"
# include "Warrior.hpp"
# include "Legend.hpp"
# include "Monster.hpp"

/* Window */

# define WIDTH	1600
# define HEIGHT	1000

# define ATH_HEIGHT	200
# define MAP_HEIGHT	200

/* Stats */

# define ICON_SIZE	10

/* Gameplay */

# define SCORE_TO_WIN	3
# define SLFOV	15
# define LFOV	8

enum	e_player
  {
    ONE,
    TWO
  };

class	GameEngine : public gdl::Game
{
private:
  gdl::SdlContext	_context;
  gdl::Clock		_clock;
  gdl::Input		_input;
  gdl::BasicShader	_shader;
  Field&		_field;
  int			_humans;
  int			_bots;
  std::vector<Character*> _characters;
  std::vector<Character*> _monsters;
  std::vector<APlayer*>	_players;
  Ground*		_profils[3];
  Ground*		_pipes[2];
  std::vector<Ground*>	_statBombs[2];
  std::vector<Ground*>	_statPower[2];
  std::vector<Ground*>	_statSpeed[2];
  int			_state;
  sf::Music		_theme;
  std::vector<sf::SoundBuffer>		_soundBuffers;
  std::vector<sf::Sound>		_sounds;

  bool			_checkDead(int const);
  bool			_thereIsMonster(const int) const;
  bool			_thereIsNoMoreHuman() const;
  void			_killId(int);

  void			_drawGame(glm::mat4&, int const);
  void			_drawStatOne(glm::mat4&);
  void			_drawStatTwo();

  APlayer		*_createNewTeub(const int);
  APlayer		*_createNewUndecided(const int);
  APlayer		*_createNewRecruit(const int);
  APlayer		*_createNewSoldier(const int);
  APlayer		*_createNewWarrior(const int);
  APlayer		*_createNewLegend(const int);

  void			_deleteBlock(size_t y,size_t x) const;  
  std::vector<std::pair<size_t, size_t> > const	_generateSpawnPoints() const;

public:
  GameEngine(Field&, bool);
  virtual ~GameEngine() {};

  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();

  static void	drawMap();

  gdl::SdlContext&	getContext();
  int			getGameStatus() const;
};

typedef APlayer *(GameEngine::*botGenerator)(const int);

#endif /* !_GAME_ENGINE_HPP_ */
