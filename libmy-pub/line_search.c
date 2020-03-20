/*
** line_search.c for libmy in /home/combes_v//Projets_persos/svn/valentin/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat May 12 13:38:33 2012 valentin combes
** Last update Fri Oct 26 19:32:31 2012 
*/

#include "libmy.h"

static t_ls	*auto_completion_alt = NULL;

void	line_search_free(t_ls *list, t_hist *result)
{
  t_ls	*tmp;

  while (list)
    {
      tmp = list;
      list = list->next;
      free_t_ls(tmp);
    }
  while (result)
    {
      result->line = xfree(result->line);
      if (result->next)
  	{
  	  result = result->next;
  	  result->prev = xfree(result->prev);
  	}
      else
  	result = xfree(result);
    }
}

void		line_search(char *buffer, int *n, int *len)
{
  t_ls		*list;
  t_ls		*tmp;
  t_hist	*result;
  t_hist	*tmp2;
  int		a;
  int		res;
  char		c;
  int		maxlen;
  int		changelist;
  int		curlen;
  int		width;
  char		*longest = NULL;
  int		backslash;

  a = *n;
  c = 0;
  backslash = 0;
  while (a > 0 && ((buffer[a] != ' ') || (buffer[a] == ' ' && buffer[a - 1] == '\\')))
    {
      if (buffer[a] == '/')
	c++;
      if (buffer[a] == '\\')
	backslash++;
      a--;
    }
  if (buffer[a] == ' ')
    a++;
  if (c)
    {
      res = *n;
      while (res > 0 && buffer[res] != '/')
	res--;
      res++;
      c = buffer[res];
      buffer[res] = '\0';
      list = my_ls(buffer + a, LIST, NULL);
      buffer[res] = c;
      a = *n;
      while (a > 0 && buffer[a] != '/')
	a--;
      a++;
    }
  else
    list = my_ls(".", LIST, NULL);
  tmp = list;
  result = NULL;
  changelist = 0;
  while (tmp)
    {
      if (!my_strsncmp(buffer + a, tmp->name, *n - a - backslash) || a == *n)
  	{
	  if (!longest)
	    longest = my_strscreat(tmp->name);
	  else
	    longest_cut(tmp->name, longest);
  	  if (!result)
  	    {
  	      result = xmalloc(sizeof(*result));
  	      result->prev = NULL;
  	      result->next = NULL;
	      if (tmp->rights && tmp->rights[0] == 'd')
		result->line = my_strcat(tmp->name, "/");
	      else
		result->line = my_strscreat(tmp->name);
	    }
  	  else
  	    {
	      tmp2 = result;
  	      while (tmp2->next)
  	  	tmp2 = tmp2->next;
  	      tmp2->next = xmalloc(sizeof(*tmp2->next));
  	      tmp2->next->prev = tmp2;
  	      tmp2->next->next = NULL;
  	      tmp2->next->line = my_strcreat(tmp->name);
  	      tmp2 = tmp2->next;
  	    }
  	}
      tmp = tmp->next;
      if (!tmp && !changelist)
	{
	  tmp = auto_completion_alt;
	  changelist = 1;
	}
    }
  res = 0;
  tmp2 = result;
  maxlen = 0;
  while (tmp2)
    {
      if (my_strlen(tmp2->line) > maxlen)
	maxlen = my_strlen(tmp2->line);
      tmp2 = tmp2->next;
      res++;
    }
  width = tgetnum("co");
  if (res > 1)
    {
      my_printf("\n");
      tmp2 = result;
      curlen = 0;
      while (tmp2)
	{
	  curlen += maxlen + 3;
	  if (curlen > width)
	    {
	      curlen = maxlen + 3;
	      my_printf("\n");
	    }
	  my_printf("%ms", maxlen + 3, tmp2->line);
	  tmp2 = tmp2->next;
	}
      my_printf("\n");
      *len += my_strlen(longest) - (*n - a);
      res = 0;
      *n += my_strlen(longest) - (*n - a);
      while (longest[res])
	buffer[a++] = longest[res++];
    }
  else if (res == 1)
    {
      *len += my_strlen(result->line) - (*n - a);
      res = 0;
      *n += my_strlen(result->line) - (*n - a);
      while (result->line[res])
	buffer[a++] = result->line[res++];
    }
  line_search_free(list, result);
}

void	add_in_search(char *str)
{
  t_ls	*tmp;

  if (!auto_completion_alt)
    {
      auto_completion_alt = xmalloc(sizeof(*auto_completion_alt));
      auto_completion_alt->name = my_strcreat(str);
      auto_completion_alt->prev = NULL;
      auto_completion_alt->next = NULL;
    }
  else
    {
      tmp = auto_completion_alt;
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = xmalloc(sizeof(*tmp->next));
      tmp->next->prev = tmp;
      tmp = tmp->next;
      tmp->name = my_strcreat(str);
      tmp->next = NULL;
    }    
}

void	remove_from_search(char *str)
{
  t_ls	*tmp;

  tmp = auto_completion_alt;
  while (tmp && my_strcmp(tmp->name, str))
    tmp = tmp->next;
  if (tmp)
    {
      if (tmp == auto_completion_alt)
	{
	  auto_completion_alt = tmp->next;
	  if (tmp->next)
	    tmp->next = auto_completion_alt;
	  tmp->name = xfree(tmp->name);
	  tmp = xfree(tmp);
	}
      else
	{
	  if (tmp->prev)
	    tmp->prev->next = tmp->next;
	  if (tmp->next)
	    tmp->next->prev = tmp->prev;
	  tmp->name = xfree(tmp->name);
	  tmp = xfree(tmp);
	}
    }
}
