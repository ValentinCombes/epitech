/*
** my_ls_rights.c for libmy in /home/combes_v//Projets_persos/svn/valentin/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat Apr  7 19:04:04 2012 valentin combes
** Last update Sat Apr  7 19:15:40 2012 valentin combes
*/

#include	"libmy.h"

char	det_type(struct stat s_stat)
{
  if (S_ISDIR(s_stat.st_mode))
    return ('d');
  else if (S_ISLNK(s_stat.st_mode))
    return ('l');
  else if (S_ISREG(s_stat.st_mode))
    return ('-');
  else if (S_ISCHR(s_stat.st_mode))
    return ('c');
  else if (S_ISBLK(s_stat.st_mode))
    return ('b');
  else if (S_ISLNK(s_stat.st_mode))
    return ('l');
  else if (S_ISSOCK(s_stat.st_mode))
    return ('s');
  return (' ');
}

int	det_user_rights(struct stat s_stat, t_ls *list)
{
  if (S_IRUSR & s_stat.st_mode)
    list->rights[1] = 'r';
  else
    list->rights[1] = '-';
  if (S_IWUSR & s_stat.st_mode)
    list->rights[2] = 'w';
  else
    list->rights[2] = '-';
  if (S_IXUSR & s_stat.st_mode)
    list->rights[3] = 'x';
  else
    list->rights[3] = '-';
  return (0);
}

int	det_group_rights(struct stat s_stat, t_ls *list)
{
  if (S_IRGRP & s_stat.st_mode)
    list->rights[4] = 'r';
  else
    list->rights[4] = '-';
  if (S_IWGRP & s_stat.st_mode)
    list->rights[5] = 'w';
  else
    list->rights[5] = '-';
  if (S_IXGRP & s_stat.st_mode)
    list->rights[6] = 'x';
  else
    list->rights[6] = '-';
  return (0);
}

int	det_other_rights(struct stat s_stat, t_ls *list)
{
  if (S_IROTH & s_stat.st_mode)
    list->rights[7] = 'r';
  else
    list->rights[7] = '-';
  if (S_IWOTH & s_stat.st_mode)
    list->rights[8] = 'w';
  else
    list->rights[8] = '-';
  if (S_IXOTH & s_stat.st_mode)
    list->rights[9] = 'x';
  else
    list->rights[9] = '-';
  return (0);
}

void	get_type_and_rights(struct stat s_stat, t_ls *list)
{
  list->rights[0] = det_type(s_stat);
  det_user_rights(s_stat, list);
  det_group_rights(s_stat, list);
  det_other_rights(s_stat, list);
  list->rights[10] = '\0';
}
