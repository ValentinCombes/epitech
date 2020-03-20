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

static t_hist *history = NULL;

void		add_in_history(char *s, int temp)
{
  t_hist	*tmp;

  if (my_strlen(s) == 1 && s[0] == 12)
    return;
  if (history == NULL)
    {
      history = xmalloc(sizeof(*history));
      history->tmp = temp;
      history->prev = NULL;
      history->next = NULL;
      history->line = my_strcreat(s);
    }
  else
    {
      tmp = history;
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = xmalloc(sizeof(*tmp->next));
      tmp->next->tmp = temp;
      tmp->next->prev = tmp;
      tmp->next->next = NULL;
      tmp->next->line = my_strcreat(s);
    }
}

void		clean_tmp_history()
{
  t_hist	*tmp;
  t_hist	*tmp2;

  while (history && history->tmp == 1) {
    tmp = history;
    history = history->next;
    history->prev = NULL;
    tmp->line = xfree(tmp->line);
    tmp = xfree(tmp);
  }
  tmp = history;
  while (tmp) {
    if (tmp->tmp == 1)
      {
	if (tmp->prev)
	  tmp->prev->next = tmp->next;
	if (tmp->next)
	  tmp->next->prev = tmp->prev;
	tmp2 = tmp->prev;
	tmp->line = xfree(tmp->line);
	tmp = xfree(tmp);
	tmp = tmp2;
      }
    tmp = tmp->next;
  }
}

t_hist	*get_history_pointer()
{
  return (history);
}

void		free_history()
{
  t_hist	*tmp;

  tmp = history;
  while (tmp)
    {
      tmp->line = xfree(tmp->line);
      if (tmp->next)
	{
	  tmp = tmp->next;
	  tmp->prev = xfree(tmp->prev);
	}
      else
	tmp = xfree(tmp);
    }
}
