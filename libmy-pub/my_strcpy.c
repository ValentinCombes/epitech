/*
** my_strcpy.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Wed Mar 30 21:38:57 2011 valentin combes
*/

#include	"libmy.h"

void	my_strcpy(char *dest, char *str)
{
  int	n;

  n = 0;
  while (str[n])
    {
      dest[n] = str[n];
      n++;
    }
  dest[n] = '\0';
}

void	my_strncpy(char *dest, char *str, int size)
{
  int	n;

  n = 0;
  while (str[n] && n < size)
    {
      dest[n] = str[n];
      n++;
    }
  dest[n] = '\0';
}

void	my_epurcpy(char *s, char *str)
{
  int	n;
  int	a;

  n = 0;
  a = 0;
  while (str[n] == ' ' || str[n] == '\t')
    n++;
  while (str[n]) {
    if (str[n] == ' ' || str[n] == '\t') {
      s[a] = str[n];
      a++;
      n++;
      while (str[n] == ' ' || str[n] == '\t')
	n++;
    }
      s[a] = str[n];
      a++;
      n++;
  }
  s[a] = '\0';
}

char	*my_epurstr(char *str)
{
  char	*s;
  int	n;
  int	a;

  n = 0;
  a = 0;
  while (str[n] == ' ' || str[n] == '\t') {
    n++;
    a++;
  }
  while (str[n]) {
    if (str[n] == ' ' || str[n] == '\t') {
      n++;
      while (str[n] == ' ' || str[n] == '\t') {
	n++;
	a++;
      }
    }
    n++;
  }
  s = xmalloc((n - a + 1) * sizeof(*s));
  my_epurcpy(s, str);
  return (s);
}
