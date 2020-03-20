/*
** my_puttime.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Wed Mar 30 21:38:57 2011 valentin combes
*/

#include	"libmy.h"

void		my_puttime(int fd, int sec, int min, int hour)
{
  if ((hour / 10) == 0) {
    my_putchar(fd, '0');
    my_put_nbr(fd, hour);
  }
  else
    my_put_nbr(fd, hour);
  my_putchar(fd, ':');
  if ((min / 10) == 0) {
    my_putchar(fd, '0');
    my_put_nbr(fd, min);
  }
  else
    my_put_nbr(fd, min);
  my_putchar(fd, ':');
  if ((sec / 10) == 0) {
    my_putchar(fd, '0');
    my_put_nbr(fd, sec);
  }
  else
    my_put_nbr(fd, sec);
}

void		my_putnstr(int fd, int precision, char *str)
{
  int	n;

  n = my_strlen(str);
  if (n > precision)
    write(fd, str, precision);
  else
    write(fd, str, n);
  if (n < precision)
    my_put_space(fd, precision - n + 1);
}

void		my_putnnbr(int fd, int precision, int nbr)
{
  int	n;
  char	*str;

  str = my_nbr_to_nstr(nbr, precision);
  n = my_strlen(str);
  if (n > precision)
    write(fd, str, precision);
  else
    write(fd, str, n);
  if (n < precision)
    my_put_space(fd, precision - n + 1);
  str = xfree(str);
}

void	my_manalyse(char *str, int n, va_list ap, int fd)
{
  int	a;
  int	b;
  char	*s;

  if (str[n] == 's')
    {
      a = va_arg(ap, int);
      s = va_arg(ap, char *);
      my_putnstr(fd, a, s);
    }
  else if (str[n] == 'd')
    {
      a = va_arg(ap, int);
      b = va_arg(ap, int);
      my_putnnbr(fd, a, b);
    }
}
