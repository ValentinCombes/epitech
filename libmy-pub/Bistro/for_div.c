/*
** for_div.c for for_div in /home/baudy_m//Desktop/Projet/C/Bistromatique
** 
** Made by marie baudy
** Login   <baudy_m@epitech.net>
** 
** Started on  Wed Nov  3 22:54:26 2010 marie baudy
** Last update Wed Nov  3 22:59:41 2010 marie baudy
*/

#include "my.h"

int	my_strdivcmp(char *str1, char *str2)
{
  int	n;
  int	diff;

  n = 0;
  diff = 0;
  while (diff == 0 && str2[n] != '\0')
    {
      diff = str1[n] - str2[n];
      n = n + 1;
    }
  if (diff > 0)
    diff = 1;
  return (diff);
}

char	*my_strdivcpy(char *str1, int n, int i, int s)
{
  char	*str2;
  int	a;

  a = 0;
  str2 = (char *) my_malloc((n + s + 1) * sizeof(*str2));
  n = n + s;
  while (n > 0)
    {
      str2[a] = (char) str1[i];
      a = a + 1;
      i = i + 1;
      n = n - 1;
    }
  return (str2);
}

char	*my_strdivcpy2(char *str1, char *str2)
{
  int	i;

  i = 0;
  while (str2[i] != '\0')
    {
      str1[i] = str2[i];
      i = i + 1;
    }
  return (str1);
}

char	*malloc_resultat(char *resultat, char *str1, char *str2)
{
  if ((my_strlen(str1) - my_strlen(str2)) > 1)
    resultat = (char *) my_malloc((my_strlen(str1) - my_strlen(str2) + 1)
				  * sizeof(*resultat));
  else
    resultat = (char *) my_malloc((2 * sizeof(*resultat)));
  return (resultat);
}
