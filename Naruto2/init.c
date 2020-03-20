/*
** init.c for Naruto2 in /home/valentin/Projets_persos/Naruto2
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Thu Apr 19 10:20:31 2012 valentin combes
** Last update Sun Apr 22 21:07:35 2012 valentin combes
*/

#include "naruto.h"

char	  	*set_game(char *str, t_tournoi *t)
{
  int		good;
  char		*path;

  good = 1;
  while (good)
    {
      if (!(good = gamecmp(str, t)))
	path = my_strcreat(str);
      else if (!my_strcmp(str, "quit"))
	exit(0);
      else
	{
	  my_printf("%Cinvalid game.\n%C%C%s% \r", RED, BLUE, BOLD, "~> ",
		    my_strlen("~> ") + my_strlen(str) + 3);
	  str = xfree(str);
	  str = line_edit(0, "~> ");
	  path = set_game(str, t);
	}
    }
  return (path);
}

void	init_teamsize(t_tournoi *tournoi)
{
  char	*s;

  if (tournoi->teamsize)
    {
      my_printf("please choose a team size\n");
      s = line_edit(0, "~> ");
      while (!my_get_nbr(s))
  	{
  	  s = xfree(s);
  	  s = line_edit(0, "~> ");
  	}
      tournoi->teamsize = my_get_nbr(s);
      my_printf("teamsize set to %d\n", tournoi->teamsize);
      s = xfree(s);
    }
}

void	init_rounds(t_tournoi *tournoi)
{
  char	*s;

  my_printf("please choose how many rounds a player will have to win to win");
  my_printf(" a match\n");
  s = line_edit(0, "~> ");
  while (!my_get_nbr(s))
    {
      s = xfree(s);
      s = line_edit(0, "~> ");
    }
  tournoi->rounds = my_get_nbr(s);
  my_printf("match in %d rounds won\n", tournoi->rounds);
  s = xfree(s);
}

int	init_game(t_tournoi *tournoi)
{
  char	*s;
  char	*game;
  int	fd;

  my_printf("%Cplease enter a game\n", RED);
  s = line_edit(0, "~> ");
  game = my_epurstr(s);
  s = xfree(s);
  fd = open_game(game, tournoi);
  return (fd);
}

void	init(int ac, char **av, t_tournoi *tournoi)
{
  char	*game;
  int	n;
  int	fd;

  init_teamsize(tournoi);
  init_rounds(tournoi);
  tournoi->type = GRID;
  tournoi->poll = NULL;
  tournoi->player = NULL;
  tournoi->pers = NULL;
  fd = -42;
  n = 1;
  while (n < ac)
    {
      if (my_strncmp("--", av[n], 2) && fd == -42)
	{
	  game = my_epurstr(av[n]);
	  fd = open_game(game, tournoi);
	}
      n++;
    }
  if (fd == -42)
    fd = init_game(tournoi);
  if (fd == -1 || fd == -42)
    exit(0);
}
