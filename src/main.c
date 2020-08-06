/*
 * A Command Line front end for the Blancmange Virtual Machine
 * Author: o_o
 * Date: 2020
 */

#include "blancmange.h"

#include <stdio.h>
#include <stdlib.h>

char in () {return getchar ();}
void out (char c) {putchar(c);}

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
	int debug = 0;

	for (int i = 1; i < argv; i ++)
	{
		if (argc[i][0] != '-')
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
		else
		{
			debug = 1;
		}
	}
	if (debug == 0)
	{
		if (bs > 0)
		{
			if (1 == load ((unsigned char*)buffer, bs))
				return 1;
			run (in, out);
		}
		else
		{
			printf ("No files loaded!\n");
		}
	}
	else
	{
		if (bs > 0)
		{
			if (1 == load ((unsigned char*)buffer, bs))
				return 1;
			running = 1;
			input = in;
			output = out;
			printf ("Press ENTER to step through instructions.\n");
			while (running)
			{
				printf ("\x1b[2J\x1b[H");
				printf ("Current Instruction: %c\n", T[ip.x][ip.y][ip.z]);
				printf ("Instruction Pointer: x %i, y %i, z %i\n",
						ip.x,
						ip.y,
						ip.z);
				printf ("Current Register: %lli\n", (*cpu.c));
				printf ("Registers:\n");
				for (int j = 0; j < 16; j ++)
					printf ("%lli ", cpu.r[j]);
				printf ("\nStack: %i\n", cpu.p);
				if (cpu.p > 0)
					for (int j = cpu.p; j > 0; j --)
						printf ("%lli ", (*cpu.s[j - 1]));
				printf("\n");
				getchar ();
				step();
			}
		}
	}
	return 0;
}
