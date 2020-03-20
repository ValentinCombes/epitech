#include "mySDL.hpp"

mySDL::mySDL()
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
      fprintf(stderr, "fail on SDL_Init : %s.\n", SDL_GetError());
      exit (EXIT_FAILURE);
    }
  this->screen = SDL_SetVideoMode(16 * WINX, 16 * WINY, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (screen == NULL)
    {
      fprintf(stderr, "fail on SDL_SetVideoMode : %s.\n", SDL_GetError());
      exit (EXIT_FAILURE);
    }
}

mySDL::~mySDL()
{
  SDL_Quit();
}
