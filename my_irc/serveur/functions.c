/*
** functions.c for functions in /home/guay_q//boulot/projets/my_irc/myirc-2015-2014s-guay_q/serveur
** 
** Made by quentin guay
** Login   <guay_q@epitech.net>
** 
** Started on  Sat Apr 21 17:37:31 2012 quentin guay
** Last update Sun Apr 22 23:27:48 2012 valentin combes
*/

# include	"libmy.h"
# include	"server.h"
# include	"rbuffer.h"
# include	"../client/aff.h"

void	part_channel(char *buffer, t_client **clients, int fd_good)
{
  char **tabeulo;
  t_client	*tmp;

  tmp = *clients;
  tabeulo = my_str_to_wordtab(buffer);
  (void)tabeulo;
  while (tmp != NULL && tmp->cs != fd_good)
    tmp = tmp->next;
  tmp->channel = NULL;
}

void	users(t_client **clients, int fd_good)
{
  t_client	*tmp;

  tmp = *clients;
    while (tmp != NULL)
      {
	my_printf("%F%s", fd_good, tmp->name);
	tmp = tmp->next;
      }
}

void	print_message(char *buffer, t_client **clients, int fd_good)
{
  t_client	*tmp;
  char		buf[BUF_SIZE];
  char		*name;
  char		*msg;
  int		wc;
  int		rc;

  rc = ini_print_msg(&wc, &msg, &tmp, clients);
  sec_print_msg(fd_good, &name, &tmp);
  tmp = *clients;
  while (tmp)
    {
      if (tmp->cs != fd_good)
	{
	  my_printf("%F%s\n", tmp->cs, name);
	  while (!msg)
	    msg = rotative_buffer(buf, &wc, &rc, tmp->cs);
	  my_printf("%F%s\n", tmp->cs, buffer);
	  msg = xfree(msg);
	}
      tmp = tmp->next;
    }
  name = xfree(name);
}

void    private_message(char *buffer, t_client **clients, int fd_good)
{
  char **tabeulo;
  int i;
  t_client	*tmp;

  (void) fd_good;
  tmp = *clients;
  i = 0;
  tabeulo = my_str_to_wordtab(buffer);
  while (tabeulo[i] != NULL)
    i++;
  if (i >= 3)
    {
      while (tmp != NULL &&
             my_strcmp(tmp->name, tabeulo[1]) != 0)
        tmp = tmp->next;
      if (my_strcmp(tmp->name, tabeulo[1]) == 0)
        my_printf("%F%s", tmp->cs, tabeulo[2]);
    }
}
