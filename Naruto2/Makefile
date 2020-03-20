##
## Makefile for Naruto2 in /home/valentin/Projets_persos/Naruto2
## 
## Made by valentin combes
## Login   <combes_v@epitech.net>
## 
## Started on  Tue Mar 29 09:36:59 2011 valentin combes
## Last update Sat May 12 14:17:23 2012 valentin combes
##

NAME=	Naruto

SRC=	main.c		\
	character.c	\
	loop.c		\
	init.c		\
	fill_game.c	

OBJ=	$(SRC:.c=.o)

CFLAGS=	-W -Wall -Wextra -Werror -g3 -O3 -ansi -pedantic

LIBS=	-L. -lmy -lcurses

CC=	gcc

RM=	rm -rvf

all:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBS) $(CFLAGS)

clean:	
	$(RM) $(OBJ)
	$(RM) *~

fclean:	clean
	$(RM) $(NAME)

re:	fclean all