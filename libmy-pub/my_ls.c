/*
** my_ls.c for libmy in /home/combes_v//Projets_persos/svn/valentin/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat Apr  7 19:02:21 2012 valentin combes
** Last update Fri Apr 13 17:28:23 2012 valentin combes
*/

#include	"libmy.h"

char		*add_to_line(char * line, char * to_add)
{
  char		*res;
  char		*tmp;

  if (my_strcmp(line, "") && line[my_strlen(line) - 1] != '\n')
    tmp = my_strcat(line, " ");
  else
    tmp = my_strcreat(line);
  res = my_strcat(tmp, to_add);
  line = xfree(line);
  tmp = xfree(tmp);
  return (res);
}

int		get_max_len_size(t_ls *list)
{
  t_ls	*tmp;
  int		size;
  char		*s;

  size = 0;
  tmp = list;
  while (tmp)
    {
      s = my_nbr_to_str(tmp->size);
      if (my_strlen(s) > size)
	size = my_strlen(s);
      tmp = tmp->next;
      s = xfree(s);
    }
  return (size);
}

int		get_max_len_nlink(t_ls *list)
{
  t_ls	*tmp;
  int		size;
  char		*s;

  size = 0;
  tmp = list;
  while (tmp)
    {
      s = my_nbr_to_str(tmp->nlink);
      if (my_strlen(s) > size)
	size = my_strlen(s);
      tmp = tmp->next;
      s = xfree(s);
    }
  return (size);
}

t_ls		*open_path(char *path)
{
  struct dirent	*file;
  struct stat	s_stat;
  DIR		*dir;
  t_ls		*list;
  t_ls		*elem;
  char		*prefix;

  prefix = my_strcat(path, "/");
  list = NULL;
  if (!(dir = opendir(path)))
    return (NULL);
  file = readdir(dir);
  while (file)
    {
      if (file->d_name[0] != '.')
	{
	  elem = fill_ls(prefix, file, s_stat, list);
	  list = elem;
	}
      file = readdir(dir);
    }
  closedir(dir);
  return (list);
}

void		free_t_ls(t_ls *tmp)
{
  tmp->gname = xfree(tmp->gname);
  tmp->uname = xfree(tmp->uname);
  tmp->time = xfree(tmp->time);
  tmp->name = xfree(tmp->name);
  tmp = xfree(tmp);
}

