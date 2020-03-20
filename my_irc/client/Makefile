##
## Makefile for makefile in /home/guay_q//boulot/tp/my_ftp/serveur
## 
## Made by quentin guay
## Login   <guay_q@epitech.net>
## 
## Started on  Sat Apr  7 17:59:42 2012 quentin guay
## Last update Sun Apr 22 21:14:17 2012 valentin combes
##

NAME=	client

SRC=	client.c		\
	client_loop.c		\
	aff.c			\
	aff_buf.c		\
	aff_utils.c		\
	rotative_buffer.c	

OBJ=	$(SRC:.c=.o)

CC=	gcc

LIBS=	-L. -lmy -lcurses

CFLAGS=	-W -Wall -Wextra -pedantic -Werror

$(NAME):	$(OBJ)
	$(CC) $(SRC) -o $(NAME) $(CFLAGS) $(LIBS)

.cc.o:
	$(CC) -c -o $@ $< $(CFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) *~

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

.SUFIXE:	.c.o
