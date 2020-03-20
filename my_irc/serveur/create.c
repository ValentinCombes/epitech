/*
** create.c for create server in /home/guay_q//boulot/projets/my_irc/myirc-2015-2014s-guay_q/serveur
** 
** Made by quentin guay
** Login   <guay_q@epitech.net>
** 
** Started on  Sat Apr 21 17:40:32 2012 quentin guay
** Last update Sun Apr 22 23:29:43 2012 valentin combes
*/

# include	"libmy.h"
# include	"server.h"
# include	"rbuffer.h"
# include	"../client/aff.h"

int                     create_sock(int *sock, int port)
{
  int                   err;
  struct protoent       *proto;
  struct sockaddr_in    addr;

  proto = getprotobyname("TCP");
  *sock = socket(AF_INET, SOCK_STREAM, proto->p_proto);
  if (*sock == -1)
    return (-1);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  err = bind(*sock, (const struct sockaddr *) &addr, sizeof(addr));
  if (err == -1)
    {
      close (*sock);
      return (-1);
    }
  err = listen(*sock, 512);
  if (err == -1)
    {
      close (*sock);
      return (-1);
    }
  return (0);
}

void            free_clients(t_client *clients)
{
  t_client      *tmp;

  while (clients)
    {
      tmp = clients;
      clients = clients->next;
      if (tmp->name)
	free(tmp->name);
      if (tmp->addr)
	free(tmp->addr);
      free(tmp);
    }
}

void            add_client(t_client **clients, t_client * new)
{
  t_client      *tmp;

  if (*clients != NULL)
    {
      tmp = *clients;
      while (tmp->next)
        tmp = tmp->next;
      tmp->next = new;
      new->prev = tmp;
    }
  else
    *clients = new;
  my_printf("%s enter the chat\n", new->name);
  print_message("enter the chat", clients, new->cs);
}

int             manage_mod(int sock, t_client **clients)
{
  t_client      *new;
  t_buf		buf;

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
  new->addr = inet_ntoa(new->sinc.sin_addr);
  new->next = NULL;
  new->prev = NULL;
  new->channel = NULL;
  buf.rc = 0;
  buf.wc = 0;
  new->name = NULL;
  while (!new->name)
    new->name = rotative_buffer(buf.buffer, &buf.wc, &buf.rc, new->cs);
  add_client(clients, new);
  return (1);
}

void  check_clients(t_client **clients, int sock)
{
  fd_set		all_fd;
  int			max_fd;
  int			fd_good;
  t_buf			buf;
  char			*msg;
  t_client		*tmp;
  struct sockaddr_in	acc;

  ini_check_clients(&acc, &buf.wc, &buf.rc, &max_fd);
  tmp = *clients;
  all_fd = check_p1(sock, &tmp, &max_fd);
  fd_good = select(max_fd + 1, &all_fd, NULL, NULL, NULL);
  if (FD_ISSET(sock, &all_fd))
    manage_mod(sock, clients);
  else
    {
      if (check_p2(&tmp, clients, &fd_good, &all_fd) == -1)
	return;
      msg = NULL;
      while (!msg)
	msg = rotative_buffer(buf.buffer, &buf.wc, &buf.rc, fd_good);
      check_p3(msg, tmp, fd_good, clients);
    }
}
