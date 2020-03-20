/*
** get_next_line.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Fri Oct  5 12:11:31 2012 
*/

#include	"libmy.h"

int	my_linelen(char *str)
{
  int	n;

  n = 0;
  while (str[n] != '\n' && n < 10)
    n++;
  return (n);
}

char	*my_lineconcat(char *s1, char *s2, int *i)
{
  char	*result;
  int	n;
  int	a;

  a = 0;
  n = 0;
  result = NULL;
  result = xmalloc((my_strlen(s1) + my_linelen(s2) + 1) * sizeof(*result));
  while (s1[n])
    result[a++] = s1[n++];
  n = 0;
  while (s2[n] != '\n' && s2[n] != '\0')
    result[a++] = s2[n++];
  if (s2[n] == '\n')
    *i = 1;
  result[a] = '\0';
  return (result);
}

void	cpy_line(int n, char *line, char *buffer, int *a)
{
  int	i;

  if (n < 10)
    {
      i = 0;
      line = xfree(line);
      line = xmalloc((10 - n) * sizeof(*line));
      while (buffer[n] != '\n' && n < 10)
	line[i++] = buffer[n++];
      line[i] = '\0';
      if (buffer[n] == '\n')
	*a = 1;
    }
}

char	*init_line(char *buffer, int *a)
{
  char	*line;
  int	n;

  line = xmalloc(1 * sizeof(*line));
  line[0] = '\0';
  if (buffer)
    {
      n = 0;
      while (buffer[n] != '\n' && n < 10)
	n++;
      buffer[n] = 'a';
      n++;
      if (buffer[n] == '\n')
	{
	  *a = 1;
	  if (n == 10)
	    buffer[0] = '\0';
	  return (line);
	}
      cpy_line(n, line, buffer, a);
    }
  return (line);
}

char		*get_next_line(int fd)
{
  char		*line;
  char		*tmpline;
  static char	buffer[10];
  int		i;
  int		n;

  n = 0;
  line = init_line(buffer, &n);
 while (n == 0) {
    i = read(fd, buffer, 10);
    buffer[i] = '\0';
    if (i > 0) {
      tmpline = my_lineconcat(line, buffer, &n);
      line = xfree(line);
      line = tmpline;
      tmpline = NULL;
    }
    else if (my_strlen(line) >= 1)
      return (line);
    else
      return (line = xfree(line));
  }
  return (line);
}
