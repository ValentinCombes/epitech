/*
** check_clients_fnc.c for server in /home/guay_q//boulot/projets/my_irc/myirc-2015-2014s-guay_q/serveur
** 
** Made by quentin guay
** Login   <guay_q@epitech.net>
** 
** Started on  Sun Apr 22 21:58:15 2012 quentin guay
** Last update Sun Apr 22 23:39:45 2012 valentin combes
*/

# include       "libmy.h"
# include       "server.h"
# include       "rbuffer.h"
# include       "../client/aff.h"

fd_set	check_p1(int sock, t_client **tmp, int *max_fd)
{
  fd_set all_fd;

  FD_ZERO(&all_fd);
  FD_SET(sock, &all_fd);
  FD_SET(0, &all_fd);
  while ((*tmp))
    {
      if ((*max_fd) < (*tmp)->cs)
        (*max_fd) = (*tmp)->cs;
      FD_SET((*tmp)->cs, &all_fd);
      (*tmp) = (*tmp)->next;
    }
  return (all_fd);
}

int	check_p2(t_client **tmp, t_client **clients, int *fd_good, fd_set *all)
{
  (*tmp) = (*clients);
  (*fd_good) = 0;
  while ((*tmp) && !(*fd_good))
    {
      if (FD_ISSET((*tmp)->cs, &(*all)))
	(*fd_good) = (*tmp)->cs;
      if (!(*fd_good))
	(*tmp) = (*tmp)->next;
    }
  if (!(*tmp))
    {
      my_printf("fail\n");
      return (-1);
    }
  return (0);
}

void	check_p3(char* msg, t_client *tmp, int fd_good, t_client **clients)
{
  if (msg)
    {
      to_execute(msg, clients, fd_good);
      write(fd_good, "ok\n", 3);
    }
  else
    write(tmp->cs, '\0', 1);
}

void    nick(char *buffer, t_client **clients, int fd_good)
{
  char **tabeulo;
  t_client      *tmp;

  tmp = *clients;
  tabeulo = my_str_to_wordtab(buffer);
  while (tmp != NULL && tmp->cs != fd_good)
    tmp = tmp->next;
  if (tabeulo[1] != NULL)
    my_strcpy(tmp->name, tabeulo[1]);
  else
    tmp->name = my_strcreat("anonymous");
  my_freetab((void **)tabeulo);
}
