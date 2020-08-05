/*
 * A UI for the Blancmange Interpreter
 * Author: o_o
 * Date: 2020
 */

#include "blancmange.h"

#include <stdio.h>
#include <stdlib.h>

char in () {char c; scanf(" %c", &c); return c;}
void out (char c) {printf ("%c", c);}

int main (int argv, char **argc)
{
	if (argv < 2)
	{
		printf ("No imput files specified!\n");
		return 1;
	}
	char *buffer = malloc (1);
	unsigned long long int bs = 0;
	FILE *f;
	long sz;

	for (int i = 1; i < argv; i ++)
	{
		f = fopen(argc[i], "r");
		if (f == 0)
		{
			printf ("%s not found!\n", argc[i]);
		}
		else
		{
			fseek (f, 0, SEEK_END);
			sz = ftell(f);
			fseek (f, 0, 0);
			buffer = realloc (buffer, bs + sz);
			for (int j = 0; j < sz; j ++)
			{
				buffer[bs + j] = fgetc(f);
			}
			bs += sz;
		}
	}
	if (bs > 0)
	{
		load ((unsigned char*)buffer, bs);
		run (in, out);
	}
	else
	{
		printf ("No files loaded!\n");
	}
	return 0;
}
