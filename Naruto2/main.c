/*
** main.c for Naruto2 in /home/valentin/Projets_persos/Naruto2
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Thu Apr 19 10:20:31 2012 valentin combes
** Last update Sun Apr 22 21:07:35 2012 valentin combes
*/

#include "naruto.h"

void	look_for_args(int ac, char **av, t_tournoi *tournoi)
{
  int	n;

  n = 1;
  while (n < ac)
    {
      if (!my_strncmp("--", av[n], 2))
	{
	  my_printf("%C%Coption %s\n", BOLD, GREEN, av[n]);
	  if (!my_strcmp("--nosave", av[n]))
	    tournoi->save = 0;
	  if (!my_strcmp("--noteam", av[n]))
	    tournoi->teamsize = 0;
	}
      n++;
    }
}

int		open_game(char *str, t_tournoi *tournoi)
{
  char		*path_perso;
  char		*path;
  char		*s;
  int		fd;

  path = set_game(str, tournoi);
  s = my_strcat(path, "_perso");
  path_perso = my_strcat("perso/", s);
  s = xfree(s);
  fd = open(path_perso, O_RDONLY);
  if (fd == -1)
    my_puterror("no character file.");
  path_perso = xfree(path_perso);
  fill_character(tournoi, fd);
  close(fd);

  fd = open(path, O_APPEND | O_RDWR, 0666);
  if (fd == -1)
    fd = open(path, O_CREAT | O_APPEND | O_RDWR, 0666);
  if (fd == -1)
    my_puterror("can't open data, contact the dev.");
  tournoi->fd = fd;
  return (fd);
}

void	add_games()
{
  int	fd;
  char	*s;
  char	**tablo;

  fd = open("game.lst", O_RDONLY);
  if (fd < 0)
    return;
  s = get_next_line(fd);
  while (s)
    {
      tablo = my_str_to_wordtab(s);
      my_printf("adding game %s\n", tablo[0]);
      add_in_search(tablo[0]);
      tablo = my_freetab((void **)tablo);
      s = xfree(s);
      s = get_next_line(fd);
    }
  close(fd);
}

int		main(int ac, char **av)
{
  t_tournoi	tournoi;
  struct tm	*temps;
  time_t	t;

  add_games();
  tournoi.teamsize = 1;
  look_for_args(ac, av, &tournoi);
  init(ac, av, &tournoi);
  t = time(&t);
  tournoi.debut = temps = localtime(&t);
  my_printf("Tournoi de %s du %d/%d/%d ouvert :\n", tournoi.name,
	    temps->tm_mday, temps->tm_mon + 1, temps->tm_year % 100);

  loop(&tournoi);

  free_character(&tournoi);
  free_history();
  return (0);
}
