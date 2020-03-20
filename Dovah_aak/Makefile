##
## Makefile for my_norme in /home/combes_v//Projets_persos/my_norme
##
## Made by valentin combes
## Login   <combes_v@epitech.net>
##
## Started on  Fri Apr 13 17:28:23 2012 valentin combes
## Last update Mon Oct  8 02:44:40 2012 
##

NAME=	Dovah_aak

SRC=	new_dovah.c

OBJ=	$(SRC:.c=.o)

LIBS=	-lSDL -lSDL_image -lSDL_ttf -L. -lmy -lcurses

CFLAGS=	-W -Wall -Werror -D'aff_charizard()'=' '

$(NAME):	$(OBJ)
	cc -o $(NAME) $(OBJ) $(LIBS)

all:	$(NAME)

charizard:	
	cc -o $(NAME) $(SRC) charizard.c $(LIBS)

clean:	
	rm -rvf *~
	rm -rvf $(OBJ)

fclean:	clean
	rm -rvf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

