//
// main.cpp for  in /home/menich_a/rendu/cpp_bomberman/Game
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Tue Sep 15 06:42:53 2015 Anatole Menichetti
// Last update Tue Sep 15 07:08:40 2015 Anatole Menichetti
//

#include "GameEngine.hpp"
#include "BombEngine.hpp"
#include "Field.hpp"

int main()
{
  int           gameStatus;
  Field         field("./Maps/pokemon.bmap");
  GameEngine    engine(field, 2, 0, 1);

  if (!engine.initialize())
    {
      std::cout << "Error : can\'t initialize game engine." << std::endl;
      return (-1);
    }

  BombEngine    bomb_engine(field);

  while (engine.update())
    engine.draw();
  bomb_engine.exitThread();
  gameStatus = engine.getGameStatus();
  if (gameStatus > 0)
    std::cout << "Player " << gameStatus << " won." << std::endl;
  engine.getContext().stop();
  return (0);
}
