#include "Game.hpp"

Game::Game()
{
}

Game::Game(std::string name)
{
  _hero = new Trainer(name, &_sdl);
  remplisMap();
  _hero->setMap(_map);

  SDL_WM_SetCaption("Pokemon", NULL);
  SDL_WM_SetIcon(IMG_Load("icone.png"), NULL);
  _pos.x = 0;
  _pos.y = 0;

  _end = 1;

  _map->affMap(&_sdl, _hero->getX(), _hero->getY(), 0, 0);
  SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL);
  SDL_BlitSurface(_hero->getCurFrame(), NULL, _sdl.screen, _hero->getPos());
  SDL_Flip(_sdl.screen);
}

Game::~Game()
{
  delete _map;
  delete _hero;
}

void	Game::remplisMap()
{
  std::string	buffer;
  std::string	map;
  std::fstream	filestr;

  map = "";
  filestr.open("map1", std::fstream::in);
  if (!filestr.is_open())
    std::cerr << "error opening map." << std::endl;
  else
    {
      while (!filestr.eof())
	{
	  getline(filestr, buffer);
	  map += buffer + "\n";
	}
      filestr.close();
    }
  _map = new Map(map);
}

void		Game::gameLoop()
{
  while (_end)
    {
      while (SDL_PollEvent(&_event));
      if (_event.type == SDL_KEYDOWN)
	{
	  switch (_event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      _end = 0;
	      break;
	    case SDLK_UP:
	      _hero->moveUp();
	      break;
	    case SDLK_DOWN:
	      _hero->moveDown();
	      break;
	    case SDLK_LEFT:
	      _hero->moveLeft();
	      break;
	    case SDLK_RIGHT:
	      _hero->moveRight();
	      break;
	    default:
	      break;
	    }
	}
      _tempsActuel = SDL_GetTicks();
      if (_tempsActuel - _tempsPrecedent > 30)
	_tempsPrecedent = _tempsActuel;
      else
	SDL_Delay(30 - (_tempsActuel - _tempsPrecedent));
    }

}
