/*
** loop.c for Naruto2 in /home/valentin/Projets_persos/Naruto2
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Thu Apr 19 10:20:31 2012 valentin combes
** Last update Sun Apr 22 21:07:35 2012 valentin combes
*/

#include "naruto.h"

void	show(char *str, t_tournoi *tournoi)
{
  if (!my_strcmp(str + 5, "characters"))
    show_character(tournoi);
}

void	init_cmd_compl()
{
  add_in_search("show");
  add_in_search("quit");
  add_in_search("matchs");
  add_in_search("players");
  add_in_search("characters");
}

void	end_cmd_compl()
{
  remove_from_search("characters");
  remove_from_search("players");
  remove_from_search("matchs");
  remove_from_search("quit");
  remove_from_search("show");
}

void	loop(t_tournoi *tournoi)
{
  int	quit;
  char	*s;

  init_cmd_compl();
  quit = 0;
  while (!quit)
    {
      s = line_edit(0, "~> ");
      my_printf("\n");
      if (!my_strcmp(s, "quit"))
	quit = 1;
      if (!my_strncmp(s, "show ", 5))
	show(s, tournoi);
      if (!my_strcmp(s, "ls"))
	my_ls(".", PRINT, NULL);
      s = xfree(s);
    }
  end_cmd_compl();
}
