#ifndef	__GAME_HPP__
#define	__GAME_HPP__

#include <iostream>
#include <fstream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "mySDL.hpp"
#include "trainer.hpp"

class			Game
{
private:
  mySDL			_sdl;
  SDL_Event		_event;
  SDL_Rect		_pos;
  Map			*_map;
  Trainer		*_hero;
  int			_end;
  int			_tempsPrecedent;
  int			_tempsActuel;

  Game();

  void			remplisMap();

public:
  Game(std::string name);
  ~Game();

  void			gameLoop();

};

#endif
