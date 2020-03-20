/*
** my_get_nbr.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Wed Mar 30 21:38:57 2011 valentin combes
*/

#include	"libmy.h"

int	my_strlen(char *str)
{
  int	n;

  n = 0;
  while (str[n])
    n++;
  return (n);
}

double		my_get_nbr(char *str)
{
  double	res = 0;
  int		n;
  int		puiss = 1;
  int		virg = 0;

  n = my_strlen(str) - 1;
  while (n > -1) {
    if (str[n] >= '0' && str[n] <= '9') {
      res += (str[n] - '0') * puiss;
      puiss = puiss * 10;
    }
    else if (str[n] == '.' || str[n] == ',') {
      if (virg == 0) {
	res = res / puiss;
	puiss = 1;
	virg = 1;
      }
      else
	return (0);
    }
    else if (n == 0 && str[n] == '-')
      return (-res);
    n--;
  }
  return (res);
}

int	my_get_nbr_hex(char *str)
{
  int	res;
  int	n;
  int	puiss;

  res = 0;
  puiss = 1;
  n = my_strlen(str) - 1;
  while (n > -1)
    {
      if (str[n] >= '0' && str[n] <= '9') {
	res += (str[n] - '0') * puiss;
	puiss = puiss * 16;
      }
      else if (str[n] >= 'A' && str[n] <= 'F') {
	res += (str[n] - 'A' + 10) * puiss;
	puiss = puiss * 16;
      }
      else if (n == 0 && str[n] == '-')
	res = -res;
      else if (str[n] != 'X' && str[n] != 'x')
	return (0);
      n--;
    }
  return (res);
}

int	my_basecmp(char c, char *base)
{
  int	n = 0;

  while (base[n] != '\0')
    {
      if (base[n] == c)
	return (n);
      n++;
    }
  return (-1);
}

double		my_get_nbr_base(char *str, char *base)
{
  double	res = 0;
  int		n;
  int		puiss = 1;
  int		virg = 0;

  n = my_strlen(str) - 1;
  while (n > -1) {
    res += my_basecmp(str[n], base) * puiss;
    puiss = puiss * my_strlen(base);
    if (str[n] == '.' || str[n] == ',') {
      if (virg == 0) {
	res = res / puiss;
	puiss = 1;
	virg = 1;
      }
      else
	return (0);
    }
    if (n == 0 && str[n] == '-')
      return (-res);
    n--;
  }
  return (res);
}

