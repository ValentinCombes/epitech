/*
** server.c for my_irc in /home/combes_v//Proj/my_irc
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Wed Apr 18 10:29:16 2012 valentin combes
** Last update Sat Apr 27 12:51:00 2013 
*/

# include	"libmy.h"
# include	"server.h"
# include	"rbuffer.h"
# include	"../client/aff.h"

void	list_channels(char *buffer, t_client **clients, int fd_good)
{
  (void)buffer;
  (void)clients;
  (void)fd_good;

}

void	to_execute(char *buffer, t_client **clients, int fd_good)
{
  if (strncmp(buffer, "/list ", 6) == 0)
    list_channels(buffer, clients, fd_good);
  else if (strncmp(buffer, "/nick ", 6) == 0)
    nick(buffer, clients, fd_good);
  else if (strncmp(buffer, "/part ", 6) == 0)
    part_channel(buffer, clients, fd_good);
  else if (strcmp(buffer, "/users") == 0)
    users(clients, fd_good);
  else if (strcmp(buffer, "/quit") == 0)
    client_quit(clients, fd_good);
  else if (strncmp(buffer, "/msg ", 5) == 0)
    private_message(buffer, clients, fd_good);
  else
    print_message(buffer, clients, fd_good);
}

void	init_client(t_client **new, int *rc, int *wc)
{
  (*new)->addr = inet_ntoa((*new)->sinc.sin_addr);
  (*new)->next = NULL;
  (*new)->prev = NULL;
  (*new)->channel = NULL;
  (*new)->name = NULL;
  (*rc) = 0;
  (*wc) = 0;
}

int		manage_client(int sock, t_client **clients)
{
  t_client	*new;
  int		rc;
  int		wc;
  char		buf[BUF_SIZE];

  new = xmalloc(sizeof(*new));
  if (!new)
    return (-1);
  new->clen = sizeof(new->sinc);
  new->cs = accept(sock, (struct sockaddr *) &new->sinc,
		   (socklen_t *) &new->clen);
  if (new->cs == -1)
    {
      free(new);
      return (-1);
    }
  init_client(&new, &rc, &wc);
  while (!new->name)
    new->name = rotative_buffer(buf, &wc, &rc, new->cs);
  add_client(clients, new);
  g_clients = clients;
  while (42)
    check_clients(clients, sock);
  return (1);
}

int		main(int ac, char **av)
{
  int		sock;
  t_client	*clients;
  int		port;

  clients = NULL;
  if (ac == 2)
    port = atoi(av[1]);
  else
    port = 4242;
  if (create_sock(&sock, port) == -1)
    return (EXIT_FAILURE);
  while (manage_client(sock, &clients));
  free_clients(clients);
  close (sock);
  return (0);
}
