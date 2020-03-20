/*
** commands.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Sat Oct 27 14:22:28 2012 
*/

#include	"libmy.h"

void	look_for_variable(int n, char *str, va_list ap, int *fd)
{
  if (str[n] == 'F')
    {
      my_printf("%F%C", *fd, WHITE);
      *fd = va_arg(ap, int);
      my_printf("%F%C", *fd, RED);
    }
  else if (str[n] == 'C')
    my_put_color(*fd, va_arg(ap, int));
  else
    my_analyse(str, n, ap, *fd);
}

t_ls	*fill_ls(char *prefix, struct dirent *file,
		      struct stat s_stat, t_ls *list)
{
  char	*pathfile;
  t_ls	*elem;

  elem = xmalloc(sizeof(*elem));
  elem->prev = NULL;
  pathfile = my_strcat(prefix, file->d_name);
  lstat(pathfile, &s_stat);
  pathfile = xfree(pathfile);
  get_type_and_rights(s_stat, elem);
  elem->nlink = s_stat.st_nlink;
  elem->uname = get_uname(s_stat);
  elem->gname = get_grname(s_stat);
  elem->size = s_stat.st_size;
  elem->time = get_time(s_stat.st_ctime);
  elem->name = get_name(file->d_name);
  elem->next = list;
  if (list)
    list->prev = elem;
  return (elem);
}

void	print_ls(t_ls *list, int mls, int mlnl)
{
  char	*s;
  char	*s2;

  s = my_nbr_to_nstr(list->nlink, mlnl);
  s2 = my_nbr_to_nstr(list->size, mls);
  my_printf("%s %s %s %s %s %s ", list->rights, s,
	    list->uname, list->gname, s2, list->time);
  if (list->rights[0] == 'd')
    my_printf("%C%C%s\n", BLUE, BOLD, list->name);
  else if (list->rights[3] == 'x' || list->rights[6] == 'x'
	   || list->rights[9] == 'x')
    my_printf("%C%C%s\n", GREEN, BOLD, list->name);
  else if (list->name[my_strlen(list->name) - 1] == '~' ||
	   (list->name[0] == '#' &&
	    list->name[my_strlen(list->name) - 1] == '#'))
    my_printf("%C%C%s\n", RED, BOLD, list->name);
  else
    my_printf("%s\n", list->name);
  s = xfree(s);
  s2 = xfree(s2);
}

void	my_ls_print(t_ls *list, char *ls_flags, char *path)
{
  int	mls;
  int	mlnl;
  t_ls	*tmp;
  char	*npath;
  char	*tmpath;

  (void)ls_flags;
  if (!list)
    {
      my_printf("total 0\n");
      return;
    }
  mls = get_max_len_size(list);
  mlnl = get_max_len_nlink(list);
  while (list)
    {
      print_ls(list, mls, mlnl);
      if (ls_flags && ls_flags[0] == 'r' && list->rights[0] == 'd')
      	{
      	  npath = my_strcat(path, "/");
      	  tmpath = my_strcat(npath, list->name);
	  npath = xfree(npath);
	  npath = tmpath;
      	  my_printf("%C%Cin %s :\n", BLUE, BOLD, npath);
      	  my_ls(npath, PRINT, ls_flags);
	  my_printf("%Cquitting %C%C%s\n", RED, BLUE, BOLD, npath);
	  npath = xfree(npath);
      	}
      tmp = list;
      list = list->next;
      free_t_ls(tmp);
    }
}

void	*my_ls(char * path, int flag, char *ls_flags)
{
  char	*res;
  t_ls	*list;
  t_ls	*tmp;
  t_ls	*end;
  char	*npath;
  char	*tmpath;

  list = NULL;
  list = open_path(path);
  list = file_class(list);
  end = list;
  while (end && end->next)
    end = end->next;
  if (flag == LIST)
    {
      if (ls_flags && !my_strcmp(ls_flags, "r"))
      	{
      	  if (end && list)
      	    {
      	      tmp = list;
      	      while (tmp)
      		{
      		  if (end && tmp->rights[0] == 'd')
      		    {
      		      tmpath = my_strcat(path, "/");
      		      npath = my_strcat(tmpath, tmp->name);
      		      tmpath = xfree(tmpath);
      		      tmpath = my_strcat(npath, "/");
      		      npath = xfree(npath);
      		      end->next = my_ls(tmpath, LIST, ls_flags);
      		      if (end && end->next)
      			{
      			  end->next->prev = end;
      			  end = end->next;
      			  while (end && end->next)
      			    {
      			      npath = my_strcat(tmpath, end->name);
      			      end->name = xfree(end->name);
      			      end->name = npath;
      			      npath = NULL;
      			      end = end->next;
      			    }
      			}
      		      tmpath = xfree(tmpath);
      		    }
      		  tmp = tmp->next;
      		}
      	    }
      	}
      return (list);
    }
  else if (flag == STRING)
    res = concatls(list, ls_flags);
  else if (flag == PRINT)
    my_ls_print(list, ls_flags, path);
  return (res);
}
