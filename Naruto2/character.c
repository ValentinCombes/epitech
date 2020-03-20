/*
** character.c for Naruto2 in /home/valentin/Projets_persos/Naruto2
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Thu Apr 19 10:20:31 2012 valentin combes
** Last update Sun Apr 22 21:07:35 2012 valentin combes
*/

#include "naruto.h"

t_perso		*add_character(char *name, int allowed)
{
  t_perso	*tmp;

  tmp = xmalloc(sizeof(*tmp));
  tmp->name = my_strcreat(name);
  tmp->allowed = allowed;
  tmp->prev = NULL;
  tmp->next = NULL;
  return (tmp);
}

void		fill_character(t_tournoi *tournoi, int fd_perso)
{
  t_perso	*tmp;
  char		*s;
  int		allow;

  if (!tournoi->pers)
    {
      s = get_next_line(fd_perso);
      allow = my_get_nbr(s + strlen(s) - 1);
      s[strlen(s) - 2] = '\0';
      tournoi->pers = add_character(s, allow);
      s = xfree(s);
    }
  tmp = tournoi->pers;
  s = get_next_line(fd_perso);
  while (s)
    {
      allow = my_get_nbr(s + strlen(s) - 1);
      s[strlen(s) - 2] = '\0';
      tmp->next = add_character(s, allow);
      tmp->next->prev = tmp;
      tmp = tmp->next;
      s = xfree(s);
      s = get_next_line(fd_perso);
    }
}

void		free_character(t_tournoi *tournoi)
{
  t_perso	*tmp;
  t_perso	*plop;

  tmp = tournoi->pers;
  while (tmp)
    {
      plop = tmp->next;
      tmp = xfree(tmp);
      tmp = plop;
    }
}

void		show_character(t_tournoi * tournoi)
{
  t_perso	*tmp;

  tmp = tournoi->pers;
  while (tmp)
    {
      if (tmp->allowed)
	my_printf("%s\n", tmp->name);
      else
	my_printf("%C%s\n", BOLDGREY, tmp->name);
      tmp = tmp->next;
    }
}
