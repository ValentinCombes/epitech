NAME=	Naruto

SRC=	naruto.c

OBJ=	$(SRC:.c=.o)

CFLAGS=	-g3 -O3 -ansi -pedantic -W -Wall -Wextra

LIBS=	-L. -lmy -lcurses

all:	$(OBJ)
	cc -o $(NAME) $(OBJ) $(LIBS) $(CFLAGS)

save:
	touch tmp
	cat tmp >> savetmp

clean:	save
	rm -rvf $(OBJ)
	rm -rvf *~
	rm -rvf \#*#

fclean:	clean
	rm -rvf $(NAME)

re:	fclean all
