##
## Makefile for makefile in /home/guay_q//boulot/projets/my_irc/myirc-2015-2014s-guay_q
## 
## Made by quentin guay
## Login   <guay_q@epitech.net>
## 
## Started on  Thu Apr 19 15:52:12 2012 quentin guay
## Last update Thu Apr 19 15:52:13 2012 quentin guay
##

$(NAME):
	make -C client/ all
	make -C serveur/ all

all:
	make -C client/ all
	make -C serveur/ all

clean:
	make -C client/ clean
	make -C serveur/ clean

fclean:
	make -C client/ fclean
	make -C serveur/ fclean

re:
	make -C client/ re
	make -C serveur/ re

client:
	make -C client/ re

serveur:
	make -C serveur/ re

.PHONY:	all clean fclean re