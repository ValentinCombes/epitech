/*
** my_putwarn.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Wed Mar 30 21:38:57 2011 valentin combes
*/

#include "libmy.h"

void	my_put_color(int fd, int color)
{
  my_putstr(fd, "[");
  if (color == BOLDGREY)
    my_putstr(fd, "1;30");
  else
    my_put_nbr(fd, color);
  my_putchar(fd, 'm');
}

void	my_end_color(int fd, int colorchange, int color)
{
  if (colorchange != color)
    my_put_color(fd, color);
}

void	change_fd(int *fd, int colorchange, int color, int newfd)
{
  my_end_color(*fd, colorchange, color);
  *fd = newfd;
  my_end_color(*fd, colorchange, color);
}

int	my_putwarn(char *str, ...)
{
  va_list	ap;
  int		n = 0;
  int		fd = 2;

  va_start(ap, str);
  my_put_color(fd, RED);
  while (str[n])
    {
      while (str[n] != '%' && str[n] != '\0')
	my_putchar(fd, str[n++]);
      if (str[n] == '%') {
	n++;
	look_for_variable(n, str, ap, &fd);
	if (str[n] == 'm' && str[n] == 's')
	  n++;
	n++;
      }
    }
  my_put_color(fd, WHITE);
  va_end(ap);
  my_putchar(fd, '\n');
  return (-1);
}

void	my_puterror(char *str, ...)
{
  va_list	ap;
  int		n = 0;
  int		fd = 2;

  va_start(ap, str);
  my_put_color(fd, RED);
  while (str[n])
    {
      while (str[n] != '%' && str[n] != '\0')
	my_putchar(fd, str[n++]);
      if (str[n] == '%') {
	n++;
	look_for_variable(n, str, ap, &fd);
	if (str[n] == 'm' && str[n] == 's')
	  n++;
	n++;
      }
    }
  my_put_color(fd, WHITE);
  va_end(ap);
  my_putchar(fd, '\n');
  exit(0);
}
