/*
** line_edit.c for libmy in /home/combes_v//Projets_persos/svn/valentin/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat May 12 16:22:13 2012 valentin combes
** Last update Sat May 12 16:22:13 2012 valentin combes
*/

#include "libmy.h"

t_hist	*go_up_in_history(t_hist *tmp, char *s, int *pos, int *len)
{
  int	n;

  n = -1;
  if (!get_history_pointer())
    return (NULL);
  if (!tmp)
    {
      add_in_history(s, 1);
      tmp = get_history_pointer();
      while (tmp->next)
  	tmp = tmp->next;
      tmp = tmp->prev;
    }
  else if (tmp->prev)
    tmp = tmp->prev;
  else
    return (tmp);
  while (tmp->line[++n])
    s[n] = tmp->line[n];
  *pos = n;
  while (n < *len)
    s[n++] = '\0';
  *len = *pos;
  return (tmp);
}

t_hist	*go_down_in_history(t_hist *tmp, char *s, int *pos, int *len)
{
  int	n;

  n = -1;
  if (!tmp)
    return (NULL);
  if (tmp->next)
    tmp = tmp->next;
  while (tmp && tmp->line[++n])
    s[n] = tmp->line[n];
  *pos = n;
  while (n < *len)
    s[n++] = '\0';
  *len = *pos;
  if (tmp->tmp == 1)
    {
      tmp->line = xfree(tmp->line);
      tmp->prev->next = xfree(tmp->prev->next);
      tmp = NULL;
    }
  return (tmp);
}

void		dump_history()
{
  t_hist	*tmp;

  tmp = get_history_pointer();
  while (tmp)
    {
      my_printf("%s\n", tmp->line);
      tmp = tmp->next;
    }
}

