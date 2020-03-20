/*
** my_strcmp.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Thu Jul 10 21:58:05 2014 
*/

#include	"libmy.h"

int	my_strcmp(char *s1, char *s2)
{
  int	n;
  int	diff;

  n = 0;
  diff = s1[n] - s2[n];
  while (s1[n] != '\0' && diff == 0)
    {
      diff = s1[n] - s2[n];
      n++;
    }
  if (s1[n] == '\0' && s2[n] != '\0')
    {
      diff = s1[n] - s2[n];
      n++;
    }
  return (diff);
}

int	my_strncmp(char *s1, char *s2, int size)
{
  int	n;
  int	diff;

  n = 0;
  diff = s1[n] - s2[n];
  while (s1[n] != '\0' && diff == 0 && n <= size)
    {
      diff = s1[n] - s2[n];
      n++;
    }
  return (diff);
}

int	my_strsncmp(char *s1, char *s2, int size)
{
  int	n;
  int	a;
  int	diff;
  int	aspace;
  int	nspace;

  n = 0;
  a = 0;
  aspace = 0;
  nspace = 0;
  diff = s1[n] - s2[a];
  while (s1[n] != '\0' && diff == 0 && (n - nspace <= size)
	 && (a - aspace <= size))
    {
      if (s2[a] == '\\')
	{
	  a++;
	  aspace++;
	}
      if (s1[n] == '\\')
	{
	  n++;
	  nspace++;
	}
      diff = s1[n] - s2[a];
      n++;
      a++;
    }
  return (diff);
}

int	my_strstr(char *str, char *to_find)
{
  int	n;
  int	diff;
  int	size;
  /* int	a; */
  /* int	b; */

  if (my_strlen(to_find) > my_strlen(str)) {
    /* a = my_strlen(to_find); */
    /* b = my_strlen(str); */
    /* return (my_putwarn("(%d char) is to big (%d char).", a, b)); */
    return -1;
  }
  size = my_strlen(to_find);
  n = -1;
  while (str[++n] != '\0' && diff != 0)
    {
      diff = my_strncmp(str + n, to_find, size -1);
      /* n++; */
    }
  if (diff == 0)
    return (n - 1);
  return (-1);
}
