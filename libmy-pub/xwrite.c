/*
** xwrite.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Wed Feb 29 13:42:30 2012 valentin combes
*/

#include	"libmy.h"

void	xwrite(int fd, void *str, int size)
{
  int	n;

  n = write(fd, str, size);
  if (n == -1)
    {
      n = write(fd, str, size);
      if (n == -1)
	my_putwarn("error on write.");
    }
}

void	xread(int fd, char *buffer, int size)
{
  int	n;

  n = read(fd, buffer, size);
  if (n == -1)
    {
      n = read(fd, buffer, size);
      if (n == -1)
	my_putwarn("error on read.");
    }
}

void	my_putstrspecial(int fd, char *str)
{
  int	n;

  n = 0;
  while (str[n]) {
    if (str[n] == ' ')
      my_putchar(fd, '\\');
    my_putchar(fd, str[n++]);
  }
}

void	my_put_space(int fd, int nb)
{
  nb--;
  while (nb > 50) {
    xwrite(fd, "                                                  ", 50);
    nb -= 50;
  }
  xwrite(fd, "                                                  ", nb);
}

void		my_analyse(char *str, int n, va_list ap, int fd)
{
  if (str[n] == 'm')
    my_manalyse(str, n + 1, ap, fd);
  else if (str[n] == 'c')
    my_putchar(fd, (char) va_arg(ap, int));
  else if (str[n] == 'd' || str[n] == 'X' || str[n] == 'o'
	   || str[n] == 'b')
    my_putnumber(fd, va_arg(ap, int), str[n]);
  else if (str[n] == 's')
    my_putstr(fd, va_arg(ap, char *));
  else if (str[n] == 'S')
    my_putstrspecial(fd, va_arg(ap, char *));
  else if (str[n] == 't')
    my_puttab(fd, va_arg(ap, char **));
  else if (str[n] == ' ')
    my_put_space(fd, va_arg(ap, int));
  else if (str[n] == 'f')
    my_put_nbr_double(fd, va_arg(ap, double));
  else if (str[n] == 'T')
    my_puttime(fd, va_arg(ap, int), va_arg(ap, int), va_arg(ap, int));
  else
    my_putchar(fd, str[n]);
}
