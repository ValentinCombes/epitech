/*
** my_strcat.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Sun Apr  8 16:06:44 2012 valentin combes
*/

#include	"libmy.h"

char	*my_strcat(char *s1, char *s2)
{
  char	*result;
  int	n;
  int	a;

  a = 0;
  n = 0;
  result = NULL;
  result = xmalloc((my_strlen(s1) + my_strlen(s2) + 1) * sizeof(*result));
  while (s1[n])
    result[a++] = s1[n++];
  n = 0;
  while (s2[n])
    result[a++] = s2[n++];
  result[a] = '\0';
  return (result);
}

char	*my_strncat(char *s1, char *s2, int size)
{
  char	*result;
  int	n;
  int	a;

  a = 0;
  n = 0;
  result = NULL;
  result = xmalloc((my_strlen(s1) + my_strlen(s2) + 1) * sizeof(*result));
  while (s1[n] && a < size)
    result[a++] = s1[n++];
  n = 0;
  while (s2[n] && a < size)
    result[a++] = s2[n++];
  result[a] = '\0';
  return (result);
}

char	*my_strcreat(char *str)
{
  char	*s;

  s = xmalloc((my_strlen(str) + 1) * sizeof(*s));
  my_strcpy(s, str);
  return (s);
}

int	my_isalphanum(char c)
{
  if (c >= 'A' && c <= 'Z')
    return (1);
  if (c >= '0' && c <= '9')
    return (1);
  if (c >= 'a' && c <= 'z')
    return (1);
  return (0);
}

int	my_strscmp(char *s1, char *s2)
{
  int	n;
  int	i;
  int	diff;

  n = 0;
  i = 0;
  diff = s1[n] - s2[i];
  while (s1[n] != '\0' && diff == 0)
    {
      if (s1[n] == '\\')
	n++;
      if (s2[i] == '\\')
	i++;
      diff = s1[n] - s2[i];
      n++;
      i++;
    }
  if (s1[n] == '\0' && s2[i] != '\0')
    {
      if (s1[n] == '\\')
	n++;
      if (s2[i] == '\\')
	i++;
      diff = s1[n] - s2[i];
      n++;
      i++;
    }
  return (diff);
}

char	*my_strscreat(char *str)
{
  char	*s;
  int	a;
  int	n;
  int	space;

  n = 0;
  space = 0;
  while (str[n])
    {
      if (str[n] == ' ')
	space++;
      n++;
    }
  s = xmalloc((my_strlen(str) + space + 1) * sizeof(*s));
  a = 0;
  n = 0;
  while (str[a])
    {
      if (str[a] == ' ')
	s[n++] = '\\';
      s[n] = str[a];
      n++;
      a++;
    }
  s[n] = '\0';
  return (s);
}
