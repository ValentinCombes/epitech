/*
** rotative_buffer.c for my_irc in /home/combes_v//Proj/my_irc/aff
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat Apr 21 01:11:57 2012 valentin combes
** Last update Sat Apr 21 01:47:57 2012 valentin combes
*/

#include "libmy.h"
#include "aff.h"
#include "rbuffer.h"

char	*check_rbuffer(char *buf, int *wc, int *rc)
{
  char	*msg;
  char	*tmp;

  msg = NULL;
  if (buf[*wc - 1] == '\n')
    {
      buf[*wc - 1] = '\0';
      msg = my_strcreat(buf + *rc);
      if (*wc < *rc)
	{
	  *rc = 0;
	  tmp = my_strcat(msg, buf);
	  msg = xfree(msg);
	  msg = tmp;
	}
      *rc = *wc;
    }
  if (*wc >= BUF_SIZE)
    *wc -= BUF_SIZE;
  if (*rc >= BUF_SIZE)
    *rc -= BUF_SIZE;
  return (msg);
}

char	*rotative_buffer(char *buf, int *wc, int *rc, int fd)
{
  char	*msg;

  *wc += read(fd, buf + *wc, BUF_SIZE - *wc - 1);
  if (buf[*wc - 1] == 127)
    {
      if (*wc > *rc + 1)
	{
	  if (*wc > 1)
	    *wc -= 2;
	}
      else
	{
	  *wc -= 2;
	  if (*wc < 0)
	    *wc = BUF_SIZE - *wc;
	  if (*wc < *rc)
	    *wc = *rc;
	}
    }
  msg = check_rbuffer(buf, wc, rc);
  return (msg);
}
