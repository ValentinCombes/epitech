/*
** aff_buf.c for my_irc in /home/combes_v//Proj/my_irc/aff
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Fri Apr 20 18:28:28 2012 valentin combes
** Last update Fri Apr 20 18:54:22 2012 valentin combes
*/

#include "libmy.h"
#include "aff.h"

void	put_cursor()
{
  char  *src;
  char	*tmp;

  src = malloc(16);
  tgetent(NULL, "xterm");
  tmp = tgetstr("ve", &src);
  my_printf("%s", tmp);
  tmp = xfree(tmp);
}

/* void	non_canon_mode() */
/* { */
/*   struct termios term; */
/*   char  *src; */
/*   char	*tmp; */

/*   src = malloc(16); */
/*   tgetent(NULL, "xterm"); */
/*   tmp = tgetstr("vi", &src); */
/*   my_printf("%s", tmp); */
/*   tmp = xfree(tmp); */
/*   tcgetattr(0, &term); */
/*   term.c_cc[VTIME] = 0; */
/*   term.c_cc[VMIN] = 1; */
/*   term.c_lflag &= ~(ECHO | ICANON); */
/*   tcsetattr(0, 0, &term); */
/* } */

void	aff_buf(char *buf, int rc, int wc)
{
  int	width;
  char	*msg;
  char	*tmp;

  width = tgetnum("co");
  my_printf("%C%C~> ", BLUE, BOLD);
  buf[wc] = '\0';
  msg = my_strcreat(buf + rc);
  if (wc < rc)
    {
      rc = 0;
      tmp = my_strcat (msg, buf);
      msg = xfree(msg);
      msg = tmp;
    }
  tmp = msg;
  if ((my_strlen(msg) + 4) > width)
    msg += (my_strlen(msg) + 4) - width;
  my_printf("%s%C %C", msg, HIGHLIGHT, WHITE);
  if ((my_strlen(tmp) + 5) < width)
    my_printf(" \r");
  else
    my_printf("\r");
  tmp = xfree(tmp);
}

