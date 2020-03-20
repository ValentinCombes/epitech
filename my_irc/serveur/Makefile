##
## Makefile for makefile in /home/guay_q//boulot/tp/my_ftp/serveur
## 
## Made by quentin guay
## Login   <guay_q@epitech.net>
## 
## Started on  Sat Apr  7 17:59:42 2012 quentin guay
## Last update Sun Apr 22 21:58:51 2012 quentin guay
##

NAME=	serveur

SRC=	server.c \
	rotative_buffer.c \
	create.c \
	functions.c \
	functions_2.c \
	check_clients_fnc.c

OBJ=	$(SRC:.c=.o)

CC=	gcc

INC=	-L. -lmy

CFLAGS=	-W -Wall -Wextra -Werror -ansi -pedantic

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(INC)

.cc.o:
	$(CC) -c -o $@ $< $(CFLAGS) $(INC)

all:	$(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) *~

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

.SUFIXE:	.c.o
