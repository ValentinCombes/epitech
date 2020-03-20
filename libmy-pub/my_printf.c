/*
** my_printf.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Wed Feb 29 13:35:47 2012 valentin combes
*/

#include "libmy.h"

void	my_put_nbr_hex(int fd, int nb)
{
  int	puiss;
  int	n;

  puiss = 1;
  if (nb < 0) {
    my_putchar(fd, '-');
    nb = -nb;
  }
  my_putstr(fd, "0x");
  n = 0;
  while ((nb / puiss) >= my_strlen("0123456789ABCDEF")) {
    puiss = puiss * my_strlen("0123456789ABCDEF");
    n++;
  }
  n = 5 - n;
  while (n > 0) {
    my_putchar(fd, '0');
    n--;
  }
  my_put_nbr_base(fd, nb, "0123456789ABCDEF");
}

void	my_put_nbr_oct(int fd, int nb)
{
  if (nb < 0) {
    my_putchar(fd, '-');
    nb = -nb;
  }
  my_putchar(fd, '0');
  my_put_nbr_base(fd, nb, "01234567");
}

void	my_put_nbr_bin(int fd, int nb)
{
  my_put_nbr_base(fd, nb, "01");
}

void	my_putnumber(int fd, int nb, char type)
{
  if (type == 'd')
    my_put_nbr(fd, nb);
  else if (type == 'X')
    my_put_nbr_hex(fd, nb);
  else if (type == 'o')
    my_put_nbr_oct(fd, nb);
  else if (type == 'b')
    my_put_nbr_bin(fd, nb);
}

void		my_printf(char *str, ...)
{
  va_list	ap;
  int		n = 0;
  int		fd = 1;
  int		colorchange = WHITE;

  va_start(ap, str);
  while (str[n]) {
    while (str[n] != '%' && str[n] != '\0')
      my_putchar(fd, str[n++]);
    if (str[n] == '%') {
      n++;
      if (str[n] == 'F')
	change_fd(&fd, colorchange, WHITE, va_arg(ap, int));
      else if (str[n] == 'C') {
	colorchange = va_arg(ap, int);
	my_put_color(fd, colorchange);
      }
      else
	my_analyse(str, n, ap, fd);
      if (str[n++] == 'm' && (str[n] == 's' || str[n] == 'd'))
	n++;
    }
  }
  my_end_color(fd, colorchange, WHITE);
  va_end(ap);
}
