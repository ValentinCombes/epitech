/*
** serveur.c for serveur in /home/guay_q//boulot/tp/my_ftp
** 
** Made by quentin guay
** Login   <guay_q@epitech.net>
** 
** Started on  Wed Apr  4 14:31:55 2012 quentin guay
** Last update Sun Apr 22 23:16:21 2012 valentin combes
*/

#include	"libmy.h"
#include	"client.h"
#include	"rbuffer.h"
#include	"aff.h"

char	*get_nick(char *msg, t_aff *list, char *name)
{
  char	**tablo;
  char	*res;
  char	*message;

  tablo = my_str_to_wordtab(msg);
  if (tablo[1])
    res = my_strcreat(tablo[1]);
  else
    {
      my_putwarn("Usage: /nick <name>");
      res = my_strcreat("anonymous");
    }
  my_freetab((void **)tablo);
  message = my_strcat("change his nickname for ", res);
  aff(name, message, list);
  name = xfree(name);
  return (res);
}

void		do_client(int s, t_cli *cli)
{
  t_loop	loop;
  t_aff		*list;
  fd_set	fds;
  int		fd;

  list = NULL;
  init_loop(&loop);
  my_printf("%F%s\n", s, cli->nick);
  non_canon_mode();
  list = aff(cli->nick, "enter the chat", list);
  while (loop.quit)
    {
      my_printf("~> %C \r", HIGHLIGHT);
      fd = s;
      FD_ZERO(&fds);
      FD_SET(0, &fds);
      FD_SET(s, &fds);
      signal(SIGWINCH, &resize);
      fd = select(fd + 1, &fds, NULL, NULL, NULL);
      if (fd > 0 && FD_ISSET(0, &fds))
	loop.quit = client_loop(loop.buf, &loop.rc, &loop.wc, cli);
      if (fd > 0 && FD_ISSET(s, &fds))
	loop.quit = client_recieve_loop(loop.sbuf, &loop.src, &loop.swc, cli);
    }
  canon_mode();
}

void			setting_client(int ac, char **av, t_cli *cli)
{
  struct protoent	*pe;

  (void)ac;
  cli->out = 0;
  cli->nick = my_strcreat(av[2]);
  cli->port = 4242;
  pe = getprotobyname("TCP");
  cli->s = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (cli->s == -1)
    my_puterror("Socket error, end of program");
}

void	starting_client(struct sockaddr_in *sin, t_cli *cli, char **av)
{
  sin->sin_family = AF_INET;
  sin->sin_port = htons(cli->port);
  sin->sin_addr.s_addr =  inet_addr(av[1]);
  cli->error = connect(cli->s, (const struct sockaddr*)sin, sizeof(*sin));
  if (cli->error == -1)
    {
      close (cli->s);
      my_puterror("Connect error, end of program");
    }
  my_printf("You're connected to %s\n", inet_ntoa(sin->sin_addr));
}

int			main(int ac, char **av)
{
  struct s_cli		cli;
  struct sockaddr_in	sin;

  if (ac == 3)
    {
      setting_client(ac, av, &cli);
      starting_client(&sin, &cli, av);
      do_client(cli.s, &cli);
      my_clear();
      put_cursor();
      close(cli.s);
      my_free_list(g_list);
    }
  else
    my_printf("Usage: ./client [IP adress] [nickname]\n");
  return (1);
}
