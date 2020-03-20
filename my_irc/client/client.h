/*
** client.h for client in /home/guay_q//boulot/tp/my_ftp/client
** 
** Made by quentin guay
** Login   <guay_q@epitech.net>
** 
** Started on  Sat Apr  7 18:04:23 2012 quentin guay
** Last update Sun Apr 22 21:13:44 2012 valentin combes
*/

#ifndef	__CLIENT_H__
# define	__CLIENT_H__

# define _GNU_SOURCE

# include	<sys/types.h>
# include	<sys/socket.h>
# include	<sys/select.h>
# include	<unistd.h>
# include	<string.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<netinet/in.h>
# include	<netinet/ip.h>
# include	<arpa/inet.h>
# include	<netdb.h>
# include	<unistd.h>
# include	"aff.h"

typedef	struct	s_cli
{
  int		s;
  int		out;
  int		port;
  int		error;
  char		*str;
  char		*nick;
}		t_cli;

typedef	struct	s_loop
{
  int		quit;
  int		rc;
  int		wc;
  int		src;
  int		swc;
  char		buf[BUF_SIZE];
  char		sbuf[BUF_SIZE];
}		t_loop;

/*	in client_loop.c	*/
void	init_loop(t_loop *loop);
int	look_for_command(char *msg, t_cli *cli, t_aff *list);
int	client_loop(char *buf, int *rc, int *wc, t_cli *cli);
int	client_recieve_loop(char *buf, int *rc, int *wc, t_cli *cli);

/*	in client.c	*/
char	*get_nick(char *msg, t_aff *list, char *name);
void	do_client(int s, t_cli *cli);
void	setting_client(int ac, char **av, t_cli *cli);
void	starting_client(struct sockaddr_in *sin, t_cli *cli, char **av);
int	main(int ac, char **av);

#endif
