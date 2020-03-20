/*
** my_str_to_wordtab.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Fri Oct  5 11:01:10 2012 
*/

#include	"libmy.h"

int	count_word(char *str)
{
  int	nbword;
  int	n;

  nbword = 0;
  n = 0;
  while ((str[n] == ' ' || str[n] == '\t' || str[n] == '\n') && str[n - 1] != '\\')
    n++;
  if (str[n] != '\0')
    nbword++;
  while (str[n])
    {
      if ((str[n] == ' ' || str[n] == '\t' || str[n] == '\n') && str[n - 1] != '\\')
	{
	  while ((str[n] == ' ' || str[n] == '\t' || str[n] == '\n') && str[n - 1] != '\\')
	    n++;
	  if (str[n] != '\0')
	    nbword++;
	}
      else
	n++;
    }
  return (nbword);
}

int	my_wordlen(char *str, int n)
{
  int	i;

  i = 0;
  while ((str[n] != ' ') && (str[n] != '\t') && (str[n] != '\n') && str[n] != '\0')
    {
      if (str[n] == '\\') {
	n++;
	i--;
      }
      n++;
      i++;
    }
  return (i);
}

void	my_wordcpy(char *str, char **wordtab, int nbword)
{
  int	n;
  int	i;
  int	a;

  n = 0;
  i = 0;
  while (n < nbword)
    {
      a = 0;
      while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') && str[i - 1] != '\\')
	i++;
      wordtab[n] = xmalloc((my_wordlen(str, i) + 1) * sizeof(**wordtab));
      while ((str[i] != ' ') && (str[i] != '\t') && (str[i] != '\n') && str[i] != '\0') {
	if (str[i] == '\\')
	  i++;
	wordtab[n][a++] = str[i++];
      }
      wordtab[n][a] = '\0';
      n++;
    }
}

char	**my_str_to_wordtab(char *str)
{
  char	**wordtab;
  int	nbword;

  nbword = count_word(str);
  wordtab = xmalloc((nbword + 1) * sizeof(*wordtab));
  my_wordcpy(str, wordtab, nbword);
  wordtab[nbword] = NULL;

  return (wordtab);
}

void	my_puttab(int fd, char **tableau)
{
  int	n;

  n = 0;
  while (tableau[n])
    {
      my_putstr(fd, tableau[n]);
      my_putchar(fd, '\n');
      n++;
    }
}
