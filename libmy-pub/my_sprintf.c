/*
** my_fprintf.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat May 12 14:03:38 2012 valentin combes
** Last update Sat May 12 14:03:38 2012 valentin combes
*/

#include "libmy.h"

char		*my_fanalyse(char *str, int n, va_list ap, char *buffer, int *a)
{
  char		*s;
  char		*s2;
  int		b;

  s2 = buffer;
  if (str[n] == 'c')
    buffer[*a++] = (char) va_arg(ap, int);
  else if (str[n] == 'm' && str[n + 1] == 's')
    {
      int c = va_arg(ap, int);
      char *s = va_arg(ap, char *);
      s2 = buffer;
      buffer = my_strncat(buffer, s, my_strlen(buffer) + c);
      s2 = xfree(s2);
      *a += c;
    }
  else if (str[n] == 'd' || str[n] == 'X' || str[n] == 'o'
  	   || str[n] == 'b')
    {
      s = my_nbr_to_str(va_arg(ap, int));
      buffer = my_strcat(buffer, s);
      s2 = xfree(s2);
      s2 = buffer;
      *a += my_strlen(s);
      s = xfree(s);
    }
  else if (str[n] == 's')
    {
      s = va_arg(ap, char *);
      buffer = my_strcat(buffer, s);
      s2 = xfree(s2);
      s2 = buffer;
      a += my_strlen(s);
    }
  else if (str[n] == ' ')
    {
      b = va_arg(ap, int);
      s = xmalloc((b + 1) * sizeof(*s));
      s[b--] = '\0';
      *a += b;
      while (b >= 0)
	s[b--] = ' ';
      buffer = my_strcat(buffer, s);
      s = xfree(s);
      s2 = xfree(s2);
      s2 = buffer;
    }
  else if (str[n] == 'f')
    {
      double	d;
      d = va_arg(ap, double);
      b = d;
      s = my_nbr_to_str(b);
      buffer = my_strcat(buffer, s);
      s2 = xfree(s2);
      s2 = buffer;
      *a += my_strlen(s);
      s = xfree(s);
      buffer = my_strcat(buffer, ".");
      s2 = xfree(s2);
      s2 = buffer;
      *a = *a + 1;
      d -= b;
      d = d * 1000000;
      b = d;
      s = my_nbr_to_fullstr(b);
      buffer = my_strcat(buffer, s);
      s2 = xfree(s2);
      s2 = buffer;
      *a += my_strlen(s);
      s = xfree(s);
    }
  return (buffer);
}

char	*scolor_in_str(char *buffer, int color)
{
  char	*s;
  char	*s2;
  int	a;

  s = xmalloc((my_strlen(buffer) + 10));
  my_strcpy(s, buffer);
  a = my_strlen(buffer);
  my_strcpy(s + a, "[");
  a += my_strlen("[");
  s2 = my_nbr_to_str(color);
  my_strcpy(s + a, s2);
  a += my_strlen(s2);
  s2 = xfree(s2);
  my_strcpy(s + a, "m");
 return (s);
}

char		*my_sprintf(char *str, ...)
{
  va_list	ap;
  int		n = 0;
  int		a = 0;
  int		colorchange = WHITE;
  char		*s;
  char		*buffer;
  char		c;

  va_start(ap, str);
  buffer = xmalloc(2 * sizeof(*buffer));
  while (str[n]) {
    while (str[n] != '%' && str[n] != '\0')
      {
	c = str[n++];
	s = buffer;
	buffer = my_strcat(buffer, &c);
	s = xfree(s);
      }
    if (str[n] == '%') {
      n++;
      if (str[n] == 'C') {
	colorchange = va_arg(ap, int);
	s = buffer;
	buffer = scolor_in_str(buffer, colorchange);
	s = xfree(s);
      }
      else
	buffer = my_fanalyse(str, n, ap, buffer, &a);
      if (str[n++] == 'm' && str[n] == 's')
	n++;
    }
  }
  if (colorchange != WHITE) {
    s = buffer;
    buffer = scolor_in_str(buffer, WHITE);
    s = xfree(s);
  }
  va_end(ap);
  return (buffer);
}
