COMP = cc
NAME = blancmange
DEBUG = -g3
OPT = -O3

default:
	$(COMP) reference.c -o $(NAME) $(DEBUG)

release:
	$(COMP) reference.c -o $(NAME) $(OPT)
	strip $(NAME)

clean:
	rm $(NAME)
