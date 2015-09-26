//
// GraphicEngine.hpp for GraphicEngine in /home/rosain_f/projects/zappy/graphic
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Jun 29 09:04:43 2015 Francois Rosain
// Last update Sun Jul  5 11:07:23 2015 Francois Rosain
//

#ifndef _GRAPHIC_ENGINE_
# define _GRAPHIC_ENGINE_

# include <iostream>
# include <sstream>

/* LibGDL */

# include "Game.hh"
# include "SdlContext.hh"
# include "BasicShader.hh"
# include "Input.hh"
# include "Texture.hh"
# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"

/* Window */
# define WIDTH	1600
# define HEIGHT	1000
# define MOVE_PADDING	0.2

# define LFOV	5

/* Zappy */
# include "Map.hpp"
# include "Character.hpp"

# include <pthread.h>

class	GraphicEngine : public gdl::Game
{
public:
  typedef void	(GraphicEngine::*fct_ptr)(std::string const &);

private:
  gdl::SdlContext	_context;
  gdl::BasicShader	_shader;
  gdl::Clock		_clock;
  gdl::Input		_input;
  Map*			_map;
  glm::vec3		_camera;
  bool			_initialized;
  std::map<std::string, fct_ptr> fct_tab;
  bool			_goDraw;
  bool			_over;
  size_t		_bcts;

  void	_drawGround();
  void	_drawRessources();
  void	_drawCharacters();
  void	_drawEggs();

  void	bct(std::string const &);
  void	msz(std::string const &);
  void	pnw(std::string const &);
  void	ppo(std::string const &);
  void	pfk(std::string const &);
  void	pdi(std::string const &);
  void  seg(std::string const &);

public:
  GraphicEngine();
  virtual ~GraphicEngine() {};

  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();

  std::map<std::string, fct_ptr>&	getFctTab();
  bool					getGoDraw() const;
  bool					getOver() const;
  Map*					getMap();

  bool	goDraw();
  bool	isInit() const;
  void	exec(std::string const &);
};

#endif /* !_GRAPHIC_ENGINE_ */
