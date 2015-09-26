//
// GraphicEngine.cpp for GraphicEngine in /home/rosain_f/projects/zappy/graphic
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Jun 29 09:06:33 2015 Francois Rosain
// Last update Sun Jul  5 12:01:22 2015 Francois Rosain
//

#include "../Client/header/ClientException.hh"
#include "GraphicEngine.hpp"

#include "Egg.hpp"

GraphicEngine::GraphicEngine()
{
  _map = 0;
  _initialized = false;
  fct_tab["msz"] = &GraphicEngine::msz;
  fct_tab["bct"] = &GraphicEngine::bct;
  fct_tab["pnw"] = &GraphicEngine::pnw;
  fct_tab["ppo"] = &GraphicEngine::ppo;
  fct_tab["pfk"] = &GraphicEngine::pfk;
  fct_tab["pdi"] = &GraphicEngine::pdi;
  fct_tab["seg"] = &GraphicEngine::seg;
  _goDraw = false;
  _over = false;
}

std::map<std::string, GraphicEngine::fct_ptr>&  GraphicEngine::getFctTab()
{
  return (fct_tab);
}

bool	GraphicEngine::getGoDraw() const
{
  return (_goDraw);
}

bool	GraphicEngine::getOver() const
{
  return (_over);
}

Map*	GraphicEngine::getMap()
{
  return (_map);
}

/* ------- */
/* Private */
/* ------- */

void	GraphicEngine::_drawGround()
{
  size_t	x = 0;
  size_t	y = 0;

  while (y < _map->getSizeY())
    {
      x = 0;
      while (x < _map->getSizeX())
	{
	  _map->getGround()[MAP_TO_VECTOR(x, y, _map->getSizeX())]->draw(_shader, _clock);
	  x++;
	}
      y++;
    }
}

void	GraphicEngine::_drawRessources()
{
  size_t				x = 0;
  size_t				y = 0;
  Ground*				ground;

  while (y < _map->getSizeY())
    {
      x = 0;
      while (x < _map->getSizeX())
	{
	  ground = static_cast<Ground*>(_map->getGround()[MAP_TO_VECTOR(x, y, _map->getSizeX())]);
	  for (std::vector<AObject*>::iterator it = ground->getRessources().begin();
	       it != ground->getRessources().end();
	       it++)
	    (*it)->draw(_shader, _clock);
	  x++;
	}
      y++;
    }
}

void	GraphicEngine::_drawCharacters()
{
  std::vector<Character*>&	v =  _map->getCharacters();
  for (std::vector<Character*>::iterator it = v.begin(); it != v.end(); it++)
    {
      if ((*it)->getDie() && (*it)->getTurn() <= TURN_BEFORE_ERASE)
	(*it)->addTurn();
      if ((*it)->getTurn() <= TURN_BEFORE_ERASE)
	(*it)->draw(_shader, _clock);
    }
}

void	GraphicEngine::_drawEggs()
{
  std::vector<Egg*>&	v = _map->getEggs();
  for (std::vector<Egg*>::iterator it = v.begin(); it != v.end(); it++)
    (*it)->draw(_shader, _clock);
}

/* --------- */
/* Functions */
/* --------- */

bool	GraphicEngine::initialize()
{
  glm::mat4	projection;
  glm::mat4	transformation;

  sleep(2);
  if (!_context.start(WIDTH, HEIGHT, "Zappy - Client Graphic"))
    {
      std::cout << "Error : Can\'t create SdlContext." << std::endl;
      return (false);
    }
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./GraphicEngine/Shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./GraphicEngine/Shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    {
      std::cout << "Error : Can\'t load shader." << std::endl;
      return (false);
    }
  projection = glm::perspective(60.0f, (float)WIDTH/(float)HEIGHT, 0.1f, 10000.0f);
  transformation = glm::lookAt(glm::vec3(_map->getSizeX() / 2,25,_map->getSizeY() / 2 + 3), glm::vec3(_map->getSizeX() / 2,1,_map->getSizeY() / 2), glm::vec3(0,1,0));
  _shader.bind();
  _shader.setUniform("projection", projection);
  _shader.setUniform("view", transformation);
  _map->initialize();
  return (true);
}

bool	GraphicEngine::update()
{
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return (false);
  _context.updateClock(_clock);
  _context.updateInputs(_input);
  if (_input.getKey(SDLK_LEFT))
    _camera.x += MOVE_PADDING;
  else if (_input.getKey(SDLK_RIGHT))
    _camera.x -= MOVE_PADDING;
  else if (_input.getKey(SDLK_UP))
    _camera.z += MOVE_PADDING;
  else if (_input.getKey(SDLK_DOWN))
    _camera.z -= MOVE_PADDING;
  if (_input.getKey(SDLK_KP_MINUS))
    _camera.y += MOVE_PADDING;
  else if (_input.getKey(SDLK_KP_PLUS))
    _camera.y -= MOVE_PADDING;
  return (true);
}

void	GraphicEngine::draw()
{
  glm::mat4	transformation;

  transformation = glm::lookAt(glm::vec3(_camera.x, _camera.y, _camera.z - LFOV),
			       glm::vec3(_camera.x, 0, _camera.z + 0.1f),
			       glm::vec3(0,1,0));
  _shader.setUniform("view", transformation);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _drawGround();
  _drawRessources();
  _drawCharacters();
  _drawEggs();
  _context.flush();
}

bool	GraphicEngine::isInit() const
{
  return (_initialized);
}

void	GraphicEngine::exec(std::string const & input)
{
  if (fct_tab[input.substr(0, 3)])
    (this->*fct_tab[input.substr(0, 3)])(input);
}

/* ------- */
/* Fct Tab */
/* ------- */

void    GraphicEngine::bct(std::string const & input)
{
  size_t	x, y;
  int	q = 0;
  size_t	pos_start = 4;
  size_t	pos_end;
  std::stringstream	ss;

  pos_end = input.find_first_of(" \n", 4);
  ss << input.substr(pos_start, pos_end);
  ss >> x;
  ss.clear();

  pos_start = pos_end + 1;
  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> y;
  ss.clear();

  _map->resetGround(x, y);

  for (size_t cptype = 1; cptype < 8; cptype++)
    {
      q = 0;
      pos_start = pos_end + 1;
      pos_end = input.find_first_of(" \n", pos_start);
      ss << input.substr(pos_start, pos_end - pos_start);
      ss >> q;
      ss.clear();
      if (q > 0)
	_map->addRessource(x, y, static_cast<e_object>(cptype));
    }
  if (!_goDraw
      && x == _map->getSizeX() - 1
      && y == _map->getSizeY() - 1)
    _goDraw = true;
}

void    GraphicEngine::msz(std::string const & input)
{
  std::stringstream     ss;
  size_t        msz_x = 0;
  size_t        msz_y = 0;

  ss << input.substr(4, input.find_first_of(" ", 4) - 4);
  ss >> msz_x;
  ss.clear();
  ss << input.substr(input.find_first_of(" ", 4), input.find_first_of(" \n",input.find_first_of(" ", 4)));
  ss >> msz_y;
  if (msz_x < MAP_MIN_SIZE
      || msz_y < MAP_MIN_SIZE)
    throw ClientException("Map is to small : 5 is minimum size.");
  _map = new Map(msz_x, msz_y);
  _camera.x = _map->getSizeX() / 2 + 0.5f;
  _camera.y = _map->getSizeX();
  _camera.z = _map->getSizeY() / 2 + 0.5f;
  _initialized = true;
  if (!this->initialize())
    throw ClientException("Can\'t initialize GraphicEngine.");
}

void	GraphicEngine::pnw(std::string const & input)
{
  float			x, y;
  int			o, l;
  size_t		id;
  std::string		n;
  std::stringstream	ss;
  size_t	pos_start = 4;
  size_t	pos_end;

  // ID
  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> id;
  ss.clear();

  // X
  pos_start = pos_end + 1;
  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> x;
  ss.clear();

  // Y
  pos_start = pos_end + 1;
  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> y;
  ss.clear();

  // O
  pos_start = pos_end + 1;
  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> o;
  ss.clear();

  // L
  pos_start = pos_end + 1;
  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> l;
  ss.clear();

  // N
  pos_start = pos_end + 1;
  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> n;
  ss.clear();

  Character*	character = new Character(_map->getModels()["Mario"], id, x, y, l, o);
  _map->addCharacter(character);
}

void	GraphicEngine::ppo(std::string const & input)
{
  size_t		id, x, y, o;
  std::stringstream	ss;
  size_t	pos_start = 4;
  size_t	pos_end;

  // ID
  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> id;
  ss.clear();

  // X
  pos_start = pos_end + 1;
  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> x;
  ss.clear();

  // Y
  pos_start = pos_end + 1;
  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> y;
  ss.clear();

  // O
  pos_start = pos_end + 1;
  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> o;
  ss.clear();

  std::vector<Character*>&	v = _map->getCharacters();
  for (size_t i = 0; i < v.size(); i++)
    {
      if (v[i]->getId() == id)
	{
	  if (v[i]->getX() != x)
	    v[i]->translate(glm::vec3(x - v[i]->getX(), 0, 0));
	  if (v[i]->getY() != y)
	    v[i]->translate(glm::vec3(0, 0, y - v[i]->getY()));
	  v[i]->setX(x);
	  v[i]->setY(y);
	  if (v[i]->getOrientation() != o)
	    {
	      if ((v[i]->getOrientation() == 4 && o == 1)
		  || (v[i]->getOrientation() == 1 && o == 2)
		  || (v[i]->getOrientation() > 1 && v[i]->getOrientation() < 4
		      && o > v[i]->getOrientation()))
		v[i]->rotate(glm::vec3(0,1,0), 270);
	      else
		v[i]->rotate(glm::vec3(0,1,0), 90);
	      v[i]->setOrientation(o);
	      break ;
	    }
	}
    }
}

void	GraphicEngine::pfk(std::string const & input)
{
  size_t		id;
  std::stringstream	ss;
  size_t		pos_start = 4;
  size_t		pos_end;

  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> id;
  ss.clear();

  std::vector<Character*>&	v = _map->getCharacters();
  for (size_t i = 0; i < v.size(); i++)
    {
      if (v[i]->getId() == id)
	{
	  _map->addEgg(v[i]->getX(), v[i]->getY());
	  break ;
	}
    }
}

#include <unistd.h>
void	GraphicEngine::pdi(std::string const & input)
{
  size_t	id;
  std::stringstream	ss;
  size_t		pos_start = 3;
  size_t		pos_end;

  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> id;
  ss.clear();  
  
  std::vector<Character*>&	character = _map->getCharacters();
  for (std::vector<Character*>::iterator it = character.begin();
       it != character.end(); it++)
    {
      if ((*it)->getId() == id)
	{
	  (*it)->rotate(glm::vec3(0,0,1), 90);
	  (*it)->rotate(glm::vec3(1,0,0), 90);
	  (*it)->die();
	  break ;
	}
    }
}

void	GraphicEngine::seg(std::string const & input)
{
  size_t	n;
  size_t		pos_start = 3;
  size_t		pos_end;
  std::stringstream	ss;

  pos_end = input.find_first_of(" \n", pos_start);
  ss << input.substr(pos_start, pos_end - pos_start);
  ss >> n;
  ss.clear();  
  
  std::cout << "--- --- --- GAME OVER --- --- ---" << std::endl;
  std::cout << "Winner Team is : " << n << std::endl;
  std::cout << "--- --- --- ---- ---- --- --- ---" << std::endl;

  _over = true;
}
