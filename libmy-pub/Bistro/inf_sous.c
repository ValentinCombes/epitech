/*
** soustraction.c for bistro in /home/combes_v//Bistro
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Oct 26 18:54:44 2010 valentin combes
** Last update Tue Nov  2 15:21:41 2010 marie baudy
*/

#include "my.h"
#include <stdlib.h>

char	def_pos2(char *base, char *str2, int pos)
{
  if (pos < my_strlen(str2))
    return (find_pos(base, str2[pos]));
  return (0);
}

int	modif(char *str1, char *str2, char **resultat)
{
  int	m;

  if (my_strlen(str1) < my_strlen(str2) 
      || *str1 < *str2 && my_strlen(str1) == my_strlen(str2))
    {  
      swap_char(&resultat, &str1, &str2);
      *resultat = (char *) my_malloc((my_strlen(str1) + 2) * sizeof(*resultat));
      m = 1;
    }
  else 
    {
      *resultat = (char *) my_malloc((my_strlen(str1) + 1) * sizeof(*resultat));
      m = 0;
    }
  return (m);
}

char	*inf_sous(char *str1, char *str2, char *base)
{
  char	*resultat;
  char	pos_sous;
  char	retenue;
  int	n;
  int	m;

  n = 0;
  retenue = 0;
  m = modif(str1, str2, &resultat);
  str1 = my_revstr(str1);
  str2 = my_revstr(str2);
  while (str1[n])
    {
      pos_sous = find_pos(base, str1[n]) - def_pos2(base, str2, n)
	- retenue;
      retenue = 0;
      while (pos_sous < 0)
	{
	  pos_sous += my_strlen(base);
	  retenue++;
	}
      resultat[n] = base[pos_sous];
      n++;
    }
  return (my_revstr(resultat));
}
