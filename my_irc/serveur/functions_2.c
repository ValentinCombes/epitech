/*
** functions_2.c for server in /home/guay_q//boulot/projets/my_irc/myirc-2015-2014s-guay_q/serveur
** 
** Made by quentin guay
** Login   <guay_q@epitech.net>
** 
** Started on  Sun Apr 22 18:06:11 2012 quentin guay
** Last update Sun Apr 22 23:39:17 2012 valentin combes
*/

# include       "libmy.h"
# include       "server.h"
# include       "rbuffer.h"
# include       "../client/aff.h"

void	    client_quit(t_client **clients, int fd_good)
{
  t_client	*tmp;

  tmp = *clients;
  while (tmp && tmp->cs != fd_good)
    tmp = tmp->next;
  if (tmp == *clients)
    {
      my_printf("%s quit the chat\n", tmp->name);
      print_message("quit the chat", clients, tmp->cs);
      tmp = tmp->next;
      *clients = xfree(*clients);
      *clients = tmp;
      if (tmp)
	tmp->prev = NULL;
      g_clients = clients;
    }
  else
    {
      my_printf("%s quit the chat\n", tmp->name);
      print_message("quit the chat", clients, tmp->cs);
      if (tmp->prev)
	tmp->prev->next = tmp->next;
      if (tmp->next)
	tmp->next->prev = tmp->prev;
      tmp = xfree(tmp);
    }
}

void		handler(int s)
{
  t_client	*tmp;
  t_client	*tmp2;

  (void)s;
  my_printf("\r%Cquit\n", RED);
  tmp = *g_clients;
  if (tmp)
    {
      print_message("/quit", g_clients, 0);
      while (tmp)
	{
	  tmp2 = tmp->next;
	  client_quit(g_clients, tmp->cs);
	  tmp = tmp2;
	}
    }
  exit(EXIT_SUCCESS);
}

int	ini_print_msg(int *wc, char **msg, t_client **tmp, t_client **clients)
{
  (*wc) = 0;
  (*msg) = NULL;
  (*tmp) = (*clients);
  return (0);
}

int	sec_print_msg(int fd_good, char **name, t_client **tmp)
{
  if (fd_good == 0)
    (*name) = my_strcreat("serveur");
  else
    while ((*tmp) && (*tmp)->cs != fd_good)
      (*tmp) = (*tmp)->next;
  (*name) = my_strcreat((*tmp)->name);
  return (0);
}

int	ini_check_clients(struct sockaddr_in *acc, int *wc, int *rc, int *max)
{
  signal(SIGTERM, handler);
  signal(SIGINT, handler);
  (*acc).sin_family = 0;
  (*acc).sin_port = 0;
  (*wc) = 0;
  (*rc) = 0;
  (*max) = 0;
  return (0);
}
