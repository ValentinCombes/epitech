/*
** my_put.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Wed Mar 30 21:38:57 2011 valentin combes
*/

#include	"libmy.h"

void	my_putchar(int fd, char c)
{
  xwrite(fd, &c, 1);
}

void	my_put_nbr(int fd, int nb)
{
  int	puiss;

  puiss = 1;
  if (nb < 0)
    {
      my_putchar(fd, '-');
      nb = -nb;
    }
  while ((nb / puiss) >= 10)
    puiss = puiss * 10;
  while (puiss >= 1)
    {
      my_putchar(fd, (nb / puiss) + '0');
      nb = nb % puiss;
      puiss = puiss / 10;
    }
}

void	my_put_nbr_double(int fd, double nb)
{
  int	puiss;
  int	nbr;

  puiss = 1;
  if (nb < 0) {
    my_putchar(fd, '-');
    nb = -nb;
  }
  nbr = (int) nb;
  nb = nb - nbr;
  while ((nbr / puiss) >= 10)
    puiss = puiss * 10;
  while (puiss >= 1) {
    my_putchar(fd, (nbr / puiss) + '0');
    nbr = nbr % puiss;
    puiss = puiss / 10;
  }
  my_putchar(fd, ',');
  nbr = nb * 1000000;
  puiss = 100000;
  while (puiss >= 1) {
    my_putchar(fd, (nbr / puiss) + '0');
    nbr = nbr % puiss;
    puiss = puiss / 10;
  }
}

void	my_put_nbr_base(int fd, int nb, char *base)
{
  int	puiss;

  puiss = 1;
  if (nb < 0)
    {
      my_putchar(fd, '-');
      nb = -nb;
    }
  while ((nb / puiss) >= my_strlen(base))
    puiss = puiss * my_strlen(base);
  while (puiss >= 1)
    {
      my_putchar(fd, base[nb / puiss]);
      nb = nb % puiss;
      puiss = puiss / my_strlen(base);
    }
}

void	my_putstr(int fd, char *str)
{
  xwrite(fd, str, my_strlen(str));
}

