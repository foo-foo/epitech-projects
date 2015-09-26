//
// ARessource.cpp for ARessource in /home/rosain_f/rendu/PSU_2014_zappy/GraphicEngine/Srcs
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Wed Jul  1 14:03:18 2015 Francois Rosain
// Last update Wed Jul  1 16:10:58 2015 Francois Rosain
//

#include "ARessource.hpp"

ARessource::ARessource(gdl::Model& model, e_object type)
  : AObject(type), _model(model)
{
  switch (type)
    {
    case LINEMATE:
      _padding_x = PADD_X_LINEMATE;
      _padding_y = PADD_Y_LINEMATE;
      break ;
    case DERAUMERE:
      _padding_x = PADD_X_DERAUMERE;
      _padding_y = PADD_Y_DERAUMERE;
      break ;
    case SIBUR:
      _padding_x = PADD_X_SIBUR;
      _padding_y = PADD_Y_SIBUR;
      break ;
    case MENDIANE:
      _padding_x = PADD_X_MENDIANE;
      _padding_y = PADD_Y_MENDIANE;
      break ;
    case PHIRAS:
      _padding_x = PADD_X_PHIRAS;
      _padding_y = PADD_Y_PHIRAS;
      break ;
    case THYSTANE:
      _padding_x = PADD_X_THYSTANE;
      _padding_y = PADD_Y_THYSTANE;
      break ;
    case FOODR:
      _padding_x = PADD_X_FOOD;
      _padding_y = PADD_Y_FOOD;
      break ;
    default:
      break ;
    };
}

float	ARessource::getPaddingX() const
{
  return (_padding_x);
}

float	ARessource::getPaddingY() const
{
  return (_padding_y);
}

void	ARessource::draw(gdl::AShader &shader, gdl::Clock const & clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
