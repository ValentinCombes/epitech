/*
** my_ls_getnames.c for libmy in /home/combes_v//Projets_persos/svn/valentin/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat Apr  7 19:05:08 2012 valentin combes
** Last update Sat Apr  7 19:46:16 2012 valentin combes
*/

#include	"libmy.h"

char	*get_name(char *str)
{
  int	n;
  char	*name;

  n = 0;
  name = xmalloc((my_strlen(str) + 1) * sizeof(*name));
  while (str[n] != '\0')
    {
      name[n] = str[n];
      n++;
    }
  name[n] = '\0';
  return (name);
}

char	*get_grname(struct stat buf)
{
  char	*grname;
  int	taille;
  int	n;

  struct group *group;
  group = getgrgid(buf.st_gid);
  taille = my_strlen(group->gr_name);
  grname = xmalloc((taille + 1) * sizeof(*grname));
  n = 0;
  while (group->gr_name[n] != '\0')
    {
      grname[n] = group->gr_name[n];
      n++;
    }
  grname[n] = '\0';
  return (grname);
}

char	*get_uname(struct stat buf)
{
  struct passwd	*pwd;
  char		*uname;
  int		taille;
  int		n;

  pwd = getpwuid(buf.st_uid);
  taille = my_strlen(pwd->pw_name);
  uname = xmalloc((taille + 1) * sizeof(*uname));
  n = 0;
  while (pwd->pw_name[n] != '\0')
    {
      uname[n] = pwd->pw_name[n];
      n++;
    }
  uname[n] = '\0';
  return (uname);
}

char		*get_time(time_t t)
{
  int		n;
  int		a;
  char		outstr[200];
  char		*time;
  struct tm	*tmp;

  tmp = localtime(&t);
  strftime(outstr, sizeof(outstr), "    %b %_2d %H:%M ", tmp);
  n = 4;
  a = 0;
  time = xmalloc((my_strlen(outstr) - 3) * sizeof(*time));
  while (outstr[n] != '\0')
    time[a++] = outstr[n++];
  time[a - 1] = '\0';
  return (time);
}

int	get_ls_char_val(char c)
{
  char	*str;
  int	n;

  n = 0;
  if (c >= 'A' && c <= 'Z')
    c += 32;
  str = my_strcat("`^<=>| ,;:!?'\"()[]{}@*\\&#%012345",
		   "6789abcdefghijklmnopqrstuvwxyz_");
  while (str[n] != c)
    n++;
  str = xfree(str);
  return (n);
}
