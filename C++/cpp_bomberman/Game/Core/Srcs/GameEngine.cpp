//
// GameEngine.cpp for GameEngine in /home/rosain_f/projects/BomberMan/cube/v2
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Tue May  5 10:51:46 2015 Francois Rosain
// Last update Sun Jun 14 17:45:44 2015 Sebastien Lauret
//

#include <SFML/Audio.hpp>
#include "GameEngine.hpp"
#include <algorithm>

GameEngine::GameEngine(Field &field, int humans, int const bots, int botLevel)
  : _field(field), _humans(humans), _bots(bots), _state(0), _soundBuffers(5), _sounds(5)
{
  std::cout << "bot = " << bots << std::endl;
  size_t	monsters = 0;
  botGenerator	botGenerators[6];

  if (humans < 1 || humans > 2)
    {
      humans = 2;
      _humans = 2;
    }
  if (humans == 1 && !bots && !monsters)
    monsters = 1;
  for (int p = 0; p < humans; p++)
    {
      _characters.push_back(new Character(p + 1));
      _players.push_back(new Human(_characters[p], _input, p, _sounds[1], _sounds[2]));
    }

  botGenerators[0] = &GameEngine::_createNewTeub;
  botGenerators[1] = &GameEngine::_createNewUndecided;
  botGenerators[2] = &GameEngine::_createNewRecruit;
  botGenerators[3] = &GameEngine::_createNewSoldier;
  botGenerators[4] = &GameEngine::_createNewWarrior;
  botGenerators[5] = &GameEngine::_createNewLegend;
  if (botLevel < 1)
    botLevel = 1;
  if (botLevel > 6)
    botLevel = 6;
  for (int b = humans; b < bots + humans; b++)
    {
      if (_humans == 1 && _bots == 1)
	_characters.push_back(new Character(2));
      else
	_characters.push_back(new Character());
      _players.push_back((this->*botGenerators[botLevel])(b));
    }
  for (size_t m = humans + bots; m < humans + bots + monsters; m++)
    {
      _characters.push_back(new Character(3));
      _monsters.push_back(_characters[m]);
      _players.push_back(new Monster(_characters[m], m));
    }
}

/* ----------- */
/*  Functions  */
/* ----------- */

APlayer	*GameEngine::_createNewTeub(const int b)
{
  return (new Teub(_characters[b], b));
}

APlayer	*GameEngine::_createNewUndecided(const int b)
{
  return (new Undecided(_characters[b], b));
}

APlayer	*GameEngine::_createNewRecruit(const int b)
{
  return (new Recruit(_characters[b], b));
}

APlayer	*GameEngine::_createNewSoldier(const int b)
{
  return (new Soldier(_characters[b], b));
}

APlayer	*GameEngine::_createNewWarrior(const int b)
{
  return (new Warrior(_characters[b], b, _characters));
}

APlayer	*GameEngine::_createNewLegend(const int b)
{
  return (new Legend(_characters[b], b, _characters));
}

int	randSpawnGen(const int i)
{
  return (rand() % i);
}

void	GameEngine::_deleteBlock(size_t y, size_t x) const
{
  int i = -1;
  while (i <= 1)
    {
      if (y + i > 1 && y + i < _field.getHeight() - 1)
	_field.getMap()[y + i][x] = NULL;
      if (x + i > 1 && x + i < _field.getWidth() - 1)
	_field.getMap()[y][x + i] = NULL;
      i++;
    }
}

std::vector<std::pair<size_t, size_t> > const	GameEngine::_generateSpawnPoints() const
{

  size_t	pNbr = _players.size(), i = 0;
  size_t	y = 1 , x = 1;
  double	pasH = _field.getHeight() / sqrt(pNbr) + 1 ,
    pasW = _field.getWidth() / sqrt(pNbr) + 1;
  
  std::vector<std::pair<size_t, size_t> >	spawnPoints;

  std::cout << "width : " << _field.getWidth() << " height : " << _field.getHeight() <<std::endl
	    << "nb joueur : " << pNbr << std::endl
	    << "pash : "<< pasH << " pasW : " << pasW << std::endl
	    << std::endl;
  while (pNbr > i)
    {
      std::cout << "y : " << y << " x : " << x <<std::endl;
      y = (y % (_field.getHeight() - 2)) + 1;
      x = (x % (_field.getWidth() - 2)) + 1;
	
      spawnPoints.push_back(std::pair<size_t, size_t>(y, x));
      this->_deleteBlock(y, x);
      
      ++i;
      x += pasW;
      if (x > _field.getWidth())
	{
	  y += pasH;
	  x = 1;
	}
    }
  std::random_shuffle(spawnPoints.begin(), spawnPoints.end(), randSpawnGen);
  return (spawnPoints);
}

bool	GameEngine::initialize()
{
  glm::mat4	projection;
  glm::mat4	transformation;

  if (!_context.start(WIDTH, HEIGHT, "Bomberman"))
    {
      std::cout << "Error : Can\'t create sdl context." << std::endl;
      return (false);
    }
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    {
      std::cout << "Error : Can\'t load shader." << std::endl;
      return (false);
    }
  projection = glm::perspective(60.0f, (float)WIDTH/(float)HEIGHT, 0.1f, 10000.0f);
  // - - - - - -
  transformation = glm::lookAt(glm::vec3(_field.getWidth()/2 + 0.5f, 15, _field.getHeight()/2 + LFOV),
  			       glm::vec3(_field.getWidth()/2 + 0.5f, 1, _field.getHeight()/2 + 0.5f),
  			       glm::vec3(0, 1, 0));

  _shader.bind();
  _shader.setUniform("projection", projection);
  _shader.setUniform("view", transformation);

  /* Music & Sounds */

  _theme.OpenFromFile("./Assets/Sounds/theme.wav");
  _theme.SetVolume(50);
  _theme.SetLoop(true);
  _theme.Play();

  _soundBuffers[0].LoadFromFile("./Assets/Sounds/died.wav");
  _sounds[0].SetBuffer(_soundBuffers[0]);
  _soundBuffers[1].LoadFromFile("./Assets/Sounds/pickedBonus.wav");
  _sounds[1].SetBuffer(_soundBuffers[1]);
  _sounds[2].SetVolume(70);
  _soundBuffers[2].LoadFromFile("./Assets/Sounds/putBomb.wav");
  _sounds[2].SetBuffer(_soundBuffers[2]);
  _sounds[2].SetVolume(20);
  _soundBuffers[3].LoadFromFile("./Assets/Sounds/won.wav");
  _sounds[3].SetBuffer(_soundBuffers[3]);
  _soundBuffers[4].LoadFromFile("./Assets/Sounds/lost.wav");
  _sounds[4].SetBuffer(_soundBuffers[4]);

  /* Chargement des textures */

  _field.initialize();

  /* Initialisation des stats */

  /* Player ONE */

  _profils[ONE] = new Ground(_field.getTextures()["Face_One"]);
  _profils[ONE]->initialize();
  _profils[ONE]->translate(glm::vec3(1.75f, 1.7f, 0.4f));
  _profils[ONE]->rotate(glm::vec3(0,1,0), 180);
  _pipes[0] = new Ground(_field.getTextures()["RightPipe"]);
  _pipes[0]->initialize();
  _pipes[0]->translate(glm::vec3(10, ICON_SIZE + .1, 7));
  _pipes[0]->scale(glm::vec3(20,10,14));
  _pipes[0]->rotate(glm::vec3(0,1,0), 180);
  _pipes[1] = new Ground(_field.getTextures()["LeftPipe"]);
  _pipes[1]->initialize();
  _pipes[1]->translate(glm::vec3(30, ICON_SIZE + .1, 27));
  _pipes[1]->scale(glm::vec3(20,10,14));
  _pipes[1]->rotate(glm::vec3(0,1,0), 180);
  if (_humans == 2)
    {
      _profils[TWO] = new Ground(_field.getTextures()["Face_Two"]);
      _profils[TWO]->initialize();
      _profils[TWO]->translate(glm::vec3(19.25f, 1.7f, 20.4f));
      _profils[TWO]->rotate(glm::vec3(0,1,0), 180);
    }
  _profils[2] = new Ground(_field.getTextures()["Icon_Speed"]);
  _profils[2]->initialize();
  _profils[2]->translate(glm::vec3(1.75f, 5, 0.4f));
  _profils[2]->rotate(glm::vec3(0,1,0), 180);
  for (int i = 0; i < MAX_BOMBS; i++)
    {
      _statBombs[ONE].push_back(new Ground(_field.getTextures()["Icon_Bomb"]));
      _statBombs[ONE][i]->initialize();
      _statBombs[ONE][i]->translate(glm::vec3(4 - 1.3f * i - 1,ICON_SIZE, -3));
      _statBombs[ONE][i]->rotate(glm::vec3(0,1,0), 180);
      _statBombs[ONE][i]->rotate(glm::vec3(0,0,1), -180);
    }
  for (int i = 0; i < MAX_POWER; i++)
    {
      _statPower[ONE].push_back(new Ground(_field.getTextures()["Icon_Power"]));
      _statPower[ONE][i]->initialize();
      _statPower[ONE][i]->translate(glm::vec3(4 - 1.3f * i,ICON_SIZE, 0));
      _statPower[ONE][i]->rotate(glm::vec3(0,1,0), 180);
    }
  for (int i = 0; i < MAX_SPEED; i++)
    {
      _statSpeed[ONE].push_back(new Ground(_field.getTextures()["Icon_Speed"]));
      _statSpeed[ONE][i]->initialize();
      _statSpeed[ONE][i]->translate(glm::vec3(4 - 1.3f * i,ICON_SIZE, 3));
      _statSpeed[ONE][i]->rotate(glm::vec3(0,1,0), 180);
    }
  /* Player TWO */

  if (_humans == 2)
    {
      for (int i = 0; i < MAX_BOMBS; i++)
	{
	  _statBombs[TWO].push_back(new Ground(_field.getTextures()["Icon_Bomb"]));
	  _statBombs[TWO][i]->initialize();
	  _statBombs[TWO][i]->translate(glm::vec3(17 + 1.3f * i, ICON_SIZE, 17));
	  _statBombs[TWO][i]->rotate(glm::vec3(0,1,0), 180);
	}
      for (int i = 0; i < MAX_POWER; i++)
	{
	  _statPower[TWO].push_back(new Ground(_field.getTextures()["Icon_Power"]));
	  _statPower[TWO][i]->initialize();
	  _statPower[TWO][i]->translate(glm::vec3(17 + 1.3f * i, ICON_SIZE, 20));
	  _statPower[TWO][i]->rotate(glm::vec3(0,1,0), 180);
	}
      for (int i = 0; i < MAX_SPEED; i++)
	{
	  _statSpeed[TWO].push_back(new Ground(_field.getTextures()["Icon_Speed"]));
	  _statSpeed[TWO][i]->initialize();
	  _statSpeed[TWO][i]->translate(glm::vec3(17 + 1.3f * i, ICON_SIZE, 23));
	  _statSpeed[TWO][i]->rotate(glm::vec3(0,1,0), 180);
	}
    }

  /* Chargement des block */

  for (size_t y = 0; y < _field.getHeight(); ++y)
    for (size_t x = 0; x < _field.getWidth(); ++x)
      if (_field.getMap()[y][x] != NULL)
	{
	  if (!_field.getMap()[y][x]->initialize())
	    {
	      std::cerr << "Error: _field.getMap()[" << y 
			<< "][" << x 
			<< "]->initialize()" << std::endl;
	      return (false);
	    }
	  _field.getMap()[y][x]->translate(glm::vec3(x, 0, y));
	}

  for (size_t y = 0; y < _field.getHeight(); ++y)
    for (size_t x = 0; x < _field.getWidth(); ++x)
      {
	_field.getGround()[y][x]->initialize();
	_field.getGround()[y][x]->translate(glm::vec3(x, 0, y));
      }

  _field.getBackground()->initialize();
  _field.getBackground()->scale(glm::vec3(_field.getHeight() + 30, 1, _field.getWidth() + 30));
  _field.getBackground()->translate(glm::vec3(-15, -0.5f, -15));

  /* Chargement des players */

  std::vector<std::pair<size_t, size_t> >	spawnPoints = _generateSpawnPoints();

  for (size_t i = 0; i < _characters.size(); i++)
    _characters[i]->initialize(spawnPoints[i].first, spawnPoints[i].second);
  return (true);
}

void	GameEngine::_killId(int id)
{
  if (_characters[id]->isMonster())
    {
      std::vector<Character*>::iterator mIt = _monsters.begin();
      while (mIt != _monsters.end() && *mIt != _characters[id])
	++mIt;
      if (mIt != _monsters.end())
	_monsters.erase(mIt);
    }
  std::vector<Character*>::iterator cIt = _characters.begin() + id;
  Character *c = *cIt;
  _characters.erase(cIt);
  delete c;
  std::vector<APlayer*>::iterator pIt = _players.begin() + id;
  APlayer *p = *pIt;
  _players.erase(pIt);
  id = p->getId();
  delete p;
  std::cout << std::endl;
  std::cout << "------------------------" << std::endl;
  std::cout << "     Player " << id + 1 << " DIE !" << std::endl;
  std::cout << "------------------------" << std::endl;
  std::cout << std::endl;
}

bool	GameEngine::_thereIsMonster(const int id) const
{
  size_t	mNbr = _monsters.size();
  int		x = _characters[id] ->getX();
  int		y = _characters[id] ->getY();

  for (size_t i = 0; i < mNbr; i++)
    if (static_cast<int>(_monsters[i]->getX()) == x && static_cast<int>(_monsters[i]->getY()) == y)
      return (true);
  return (false);
}

bool	GameEngine::_thereIsNoMoreHuman() const
{
  size_t	pNbr = _players.size();

  for (size_t i = 0; i < pNbr; i++)
    if (_players[i]->isHuman())
      return (false);
  return (true);
}

bool	GameEngine::_checkDead(int const id)
{
  int const x = static_cast<int>(_characters[id]->getX());
  int const y = static_cast<int>(_characters[id]->getY());

  if ((_field.getMap()[y][x] && _field.getMap()[y][x]->getType() == FLAME) ||
      (!_characters[id]->isMonster() && _thereIsMonster(id)))
    {
      _killId(id);

      bool		noHumans;
      size_t		pNbr = _characters.size();

      if ((noHumans = _thereIsNoMoreHuman()) == true || pNbr <= 1)
	{
	  int	soundNbr;

	  if (noHumans)
	    soundNbr = 4;
	  else
	    soundNbr = 3;
	  _theme.Stop();
	  _sounds[soundNbr].Play();
	  while (_sounds[soundNbr].GetStatus() == sf::Sound::Playing);
	  if (pNbr > 1)
	    _state = _players[rand() % pNbr]->getId() + 1;
	  else
	    _state = _players[0]->getId() + 1;
	  return (true);
	}
      else
	{
	  _theme.Pause();
	  _sounds[0].Play();
	}
    }
  return (false);
}

bool	GameEngine::update()
{
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    {
      _state = -1;
      return (false);
    }
  _context.updateClock(_clock);
  _context.updateInputs(_input);

  for (size_t i = 0; i < _characters.size(); i++)
    if (_checkDead(i))
      return (false);
  if (_theme.GetStatus() == sf::Music::Paused && _sounds[0].GetStatus() == sf::Sound::Stopped)
    _theme.Play();
  for (size_t i = 0; i < _players.size(); i++)
    _players[i]->update(_clock, _field);
  return (true);
}

void	GameEngine::_drawGame(glm::mat4& transformation, int const id)
{
  _shader.setUniform("view", transformation);

  /* Objects and Ground */
  size_t	min_x = 0;
  size_t	min_y = 0;
  size_t	max_x = _field.getWidth();
  size_t	max_y = _field.getHeight();

  if (id != -1)
    {
      min_x = (static_cast<int>(_characters[id]->getX()) - VISION >= 0) ? static_cast<size_t>(_characters[id]->getX()) - VISION : 0;
      min_y = (static_cast<int>(_characters[id]->getY()) - VISION >= 0) ? static_cast<size_t>(_characters[id]->getY()) - VISION : 0;
      max_x = (static_cast<int>(_characters[id]->getX()) + VISION < static_cast<int>(_field.getWidth())) ? static_cast<size_t>(_characters[id]->getX()) + VISION : _field.getWidth() ;
      max_y = (static_cast<int>(_characters[id]->getY()) + VISION < static_cast<int>(_field.getHeight())) ? static_cast<size_t>(_characters[id]->getY()) + VISION : _field.getHeight() ;
    }
  if ((id == -1 && _field.getHeight() <= 23 && _field.getWidth() <= 23)
      || id != -1)
    for (size_t y = min_y; y < max_y; ++y)
      for (size_t x = min_x; x < max_x; ++x)
	{
	  _field.getGround()[y][x]->draw(_shader, _clock);
	  if (_field.getMap()[y][x] != NULL)
	    _field.getMap()[y][x]->draw(_shader, _clock);
	}
  else if (id == -1)
    {
      transformation = glm::lookAt(glm::vec3(1.2f,4,-0.1f),
				   glm::vec3(1.2f, 5, -0.11f),
				   glm::vec3(0,1,0));
      _shader.setUniform("view", transformation);
      _profils[2]->draw(_shader, _clock);
    }
  _field.getBackground()->draw(_shader, _clock);
  
  /* Draw Characters */
  for (size_t i = 0; i < _characters.size(); i++)
    _characters[i]->draw(_shader, _clock);
}

void	GameEngine::_drawStatOne(glm::mat4& transformation)
{
  _shader.setUniform("view", transformation);
  _profils[ONE]->draw(_shader, _clock);
  for (int i = 0; i < _players[ONE]->getBomb(); i++)
    _statBombs[ONE][i]->draw(_shader, _clock);
  for (int i = 0; i < _players[ONE]->getPower(); i++)
    _statPower[ONE][i]->draw(_shader, _clock);
  for (int i = 0; i < (int)_players[ONE]->getSpeed(); i++)
    _statSpeed[ONE][i]->draw(_shader, _clock);
}

void	GameEngine::_drawStatTwo()
{
  _profils[TWO]->draw(_shader, _clock);
  for (int i = 0; i < _players[TWO]->getBomb(); i++)
    _statBombs[TWO][i]->draw(_shader, _clock);
  for (int i = 0; i < _players[TWO]->getPower(); i++)
    _statPower[TWO][i]->draw(_shader, _clock);
  for (int i = 0; i < (int)_players[TWO]->getSpeed(); i++)
    _statSpeed[TWO][i]->draw(_shader, _clock);
}

gdl::SdlContext&	GameEngine::getContext()
{
  return (_context);
}

int	GameEngine::getGameStatus() const
{
  return (_state);
}

void	GameEngine::draw()
{
  glm::mat4	transformation;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();

  /* Player 1 */

  if (_humans == 1)
    glViewport(0,0, WIDTH, HEIGHT - ATH_HEIGHT);
  else if (_humans == 2)
    glViewport(0,0, WIDTH/2, HEIGHT - ATH_HEIGHT);
  transformation = glm::lookAt(glm::vec3(_characters[0]->getX() + 0.5f, 10, _characters[0]->getY() + 0.5f + 3),
  			       glm::vec3(_characters[0]->getX() + 0.5f, 1, _characters[0]->getY() + 0.5f),
  			       glm::vec3(0, 1, 0));
  _drawGame(transformation, ONE);

  /* Player 2 */

  if (_humans == 2)
    {
      glViewport(WIDTH/2,0, WIDTH/2, HEIGHT - ATH_HEIGHT);
      transformation = glm::lookAt(glm::vec3(_characters[1]->getX() + 0.5f, 10, _characters[1]->getY() + 0.5f + 3),
				   glm::vec3(_characters[1]->getX() + 0.5f, 1, _characters[1]->getY() + 0.5f),
				   glm::vec3(0, 1, 0));
      _drawGame(transformation, TWO);
    }

  /* Mini Map */

  glViewport(WIDTH/2 - MAP_HEIGHT/2, HEIGHT - ATH_HEIGHT, MAP_HEIGHT, MAP_HEIGHT);
  transformation = glm::lookAt(glm::vec3(_field.getWidth()/2 + 0.5f, 20, _field.getHeight()/2 + 0.51f),
  			       glm::vec3(_field.getWidth()/2 + 0.5f, 1, _field.getHeight()/2 + 0.5f),
  			       glm::vec3(0, 1, 0));
  _drawGame(transformation, -1);

  /* Stats Player 1 */
  

  glViewport(0, HEIGHT - ATH_HEIGHT, WIDTH/2 - MAP_HEIGHT/2, ATH_HEIGHT);
  transformation = glm::lookAt(glm::vec3(0,0,0),
  			       glm::vec3(0, 1, 0.01f),
  			       glm::vec3(0,1,0));
  _drawStatOne(transformation);
  _pipes[0]->draw(_shader, _clock);
  /* Stats Player 2 */

  glViewport(WIDTH/2 + MAP_HEIGHT/2, HEIGHT - ATH_HEIGHT, WIDTH/2 - MAP_HEIGHT/2, ATH_HEIGHT);
  transformation = glm::lookAt(glm::vec3(20,0,20),
			       glm::vec3(20, 1, 20.01f),
			       glm::vec3(0,1,0));
  _shader.setUniform("view", transformation);
  _pipes[1]->draw(_shader, _clock);
  if (_humans == 2)
    _drawStatTwo();


  /* Draw */

  _context.flush();
}
