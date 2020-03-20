/*
** fill_game.c for Naruto2 in /home/valentin/Projets_persos/Naruto2
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Thu Apr 19 10:20:31 2012 valentin combes
** Last update Sun Apr 22 21:07:35 2012 valentin combes
*/

#include "naruto.h"

void	fill_game(char *s, t_tournoi *tournoi)
{
  char	**tablo;

  tablo = my_str_to_wordtab(s);

  tournoi->name = my_strcreat(tablo[2]);

  my_freetab((void **)tablo);
}

int	gamecmp(char *str, t_tournoi *tournoi)
{
  char	*s;
  int	fd;
  int	ret;

  ret = 1;
  fd = open("game.lst", O_RDONLY);
  if (fd < 0)
    my_puterror("no game in the list.");
  s = get_next_line(fd);
  while (s)
    {
      if (!my_strncmp(s, str, strlen(str)))
	{
	  fill_game(s, tournoi);
	  ret = 0;
	}
      s = xfree(s);
      s = get_next_line(fd);
    }
  close(fd);
  return (ret);
}

