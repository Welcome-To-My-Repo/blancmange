COMP = cc
NAME = blancmange
DEBUG = -g3
OPT = -O3
INSTALLDIR = /usr/local/bin

default:
	$(COMP) reference.c -o $(NAME) $(DEBUG)

release:
	$(COMP) reference.c -o $(NAME) $(OPT)
	strip $(NAME)

clean:
	rm $(NAME)

install: release
	mv $(NAME) $(INSTALLDIR)
