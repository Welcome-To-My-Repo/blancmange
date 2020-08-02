/*
 * The Blancmange Kernel Reference Implementation
 * Author: o_o <yosngne@gmail.com>
 *
 * This file is public domain.
*/

#ifndef BLANCMANGE
#define BLANCMANGE

/*
* Blancmange is an esoteric language that stores programs in a cube matrix of
* bytes and allows instruction pointer movement in three dimensions.
*
* Blancmange gets its name from a rough homile of the name of its predecessor,
* Befunge.
*
* This header defines a small interpreter for the Blancmange instruction set
* designed to be used internally by an arbitrary user interface application.
*/

static unsigned char T [256][256][256];
/*
 * The Tesseract holds the instructions that the instruction pointer iterates
 * through.
 */


struct BM_POINTER;
/*
 * IP holds the position and direction of the instruction pointer
 */

struct BM_CPU;
/*
 * The CPU maintains the registers and operand stack as well as the current
 * register
 */

int load (unsigned char *txt, long int l);
/*
 * Loads a program from source code into the tesseract.
 */


int run (int I, int O);
/*
 * executes the loaded instructions.
 * I is the file descriptor for the default input.
 * O is the file descriptor for the default output.
 * It's usually a good choice for Unix/Linux to enter zero for I and one for O.
 *
 */

/*
 * Errors
 */

#define BAD_HEX 1
#define EMPTY_STACK 2
#define NOT_ENOUGH_STACK 3
#define FULL_STACK 4

struct BM_POINTER
{
	unsigned char o;
	/*
	 * 120: x increasing
	 * 121: y increasing
	 * 122: z increasing
	 * 248: x decreasing
	 * 249: y decreasing
	 * 250: z decreasing
	 */
	unsigned char
		x,
		y,
		z;
	/*
	 * Holds current coordinates
	 */
};

struct BM_CPU
{
	unsigned long long int *c;
	/*
	 * current register
	 * 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
	 */
	unsigned long long int r[16];

	unsigned char p;
	unsigned long long int *s[256];
};

int load (unsigned char* txt, long int l)
{
	unsigned char x = 0, y = 0, z = 0;
	long int i;
	for (int i = 0; i < l; i ++)
	{
		if (txt[i] < 32 || txt[i] > 126)
			continue;
		switch (txt[i])
		{
			case '{':	//Starting a new plane
				{
					z++;
					break;
				}
			case ';':	//starting a new line
				{
					y++;
					break;
				}
			case '\\':	//encoded raw byte
				{
					unsigned char h[2];
					unsigned char x = 0;
					i++;
					h[0] = txt[i];
					i++;
					h[1] = txt[i];
					//convert two digit hex to a byte
					if (h[0] < 58 && h[0] > 47)
					{
						h[0] -= 48;
						x = 16 * h[0];
					}
					else if (h[0] > 64 && h[0] < 71)
					{
						h[0] -= 55;
						x = 16 * h[0];
					}
					else if (h[0] > 96 && h[0] < 103)
					{
						h[0] -= 87;
						x = 16 * h[0];
					}
					else
					{
						return BAD_HEX;
					}

					if (h[1] < 58 && h[1] > 47)
					{
						h[1] -= 48;
						x += h[1];
					}
					else if (h[1] > 64 && h[1] < 71)
					{
						h[1] -= 55;
						x += h[1];
					}
					else if (h[1] > 96 && h[1] < 103)
					{
						h[1] -= 87;
						x += h[1];
					}
					else
					{
						return BAD_HEX;
					}
					T[x][y][z] = x;
				}
			default:
				{
					T[x][y][z] = txt[i];
					x++;
					break;
				}
			}
		if(x == 0)
			y++;
		if(y == 0)
			z++;
	}
	return 0;
}

int run (int I, int O)
{
	struct BM_POINTER ip;
	struct BM_CPU cpu;
	unsigned char running = 1;
	cpu.c = &cpu.r[0];

	ip.x = 0;
	ip.y = 0;
	ip.z = 0;
	ip.o = 'x';
	while (running)
	{
		switch (T[ip.x][ip.y][ip.z])
		{
			case ' ':
			{
				break;
			}
			case '.':
			{
				ip.o = 122;
				break;
			}
			case ',':
			{
				ip.o = 250;
				break;
			}
			case '^':
			{
				ip.o = 121;
				break;
			}
			case 'v':
			{
				ip.o = 249;
				break;
			}
			case '>':
			{
				ip.o = 120;
				break;
			}
			case '<':
			{
				ip.o = 248;
				break;
			}
			case '@':
			{
				ip.x = cpu.r[1];
				ip.y = cpu.r[2];
				ip.z = cpu.r[3];
				break;
			}
			case '#':
			{
				switch (ip.o)
                		{
                        		case 120:
                        		{
		                                ip.x ++;
      		                          break;
					}
		                        case 121:
		                        {
		                                ip.y ++;
		                                break;
		                        }
		                        case 122:
		                        {
		                                ip.z ++;
		                                break;
		                        }
		                        case 248:
		                        {
		                                ip.x --;
		                                break;
		                        }
		                        case 249:
		                        {
		                                ip.y --;
		                                break;
		                        }
		                        case 250:
		                        {
		                                ip.z --;
		                                break;
		                        }
				}
				break;
			}
			case 'Q':
			{
				running = 0;
				continue;
				break;
			}
			case '0':
			{
				cpu.c = &cpu.r[0];
				break;
			}
			case '1':
			{
				cpu.c = &cpu.r[1];
				break;
			}
			case '2':
			{
				cpu.c = &cpu.r[2];
				break;
			}
			case '3':
			{
				cpu.c = &cpu.r[3];
				break;
			}
			case '4':
			{
				cpu.c = &cpu.r[4];
				break;
			}
			case '5':
			{
				cpu.c = &cpu.r[5];
				break;
			}
			case '6':
			{
				cpu.c = &cpu.r[6];
				break;
			}
			case '7':
			{
				cpu.c = &cpu.r[7];
				break;
			}
			case '8':
			{
				cpu.c = &cpu.r[8];
				break;
			}
			case '9':
			{
				cpu.c = &cpu.r[9];
				break;
			}
			case 'A':
			{
				cpu.c = &cpu.r[10];
				break;
			}
			case 'B':
			{
				cpu.c = &cpu.r[11];
				break;
			}
			case 'C':
			{
				cpu.c = &cpu.r[12];
				break;
			}
			case 'D':
			{
				cpu.c = &cpu.r[13];
				break;
			}
			case 'E':
			{
				cpu.c = &cpu.r[14];
				break;
			}
			case 'F':
			{
				cpu.c = &cpu.r[15];
				break;
			}
			case 'i':
			{
				*cpu.c ++;
				break;
			}
			case 'd':
			{
				*cpu.c --;
				break;
			}
			case 'r':
			{
				switch (ip.o)
				{
					case 120:
					{
						ip.x ++;
						break;
					}
					case 121:
					{
						ip.y ++;
						break;
					}
					case 122:
					{
						ip.z ++;
						break;
					}
					case 248:
					{
						ip.x --;
						break;
					}
					case 249:
					{
						ip.y --;
						break;
					}
					case 250:
					{
						ip.z --;
						break;
					}
				}
				*cpu.c = T[ip.x][ip.y][ip.z];
				break;
			}
			case 'R':
			{
				for (int i = 0; i < 8; i ++)
				{
					switch (ip.o)
					{
						case 120:
						{
							ip.x ++;
							break;
						}
						case 121:
						{
							ip.y ++;
							break;
						}
						case 122:
						{
							ip.z ++;
							break;
						}
						case 248:
						{
							ip.x --;
							break;
						}
						case 249:
						{
							ip.y --;
							break;
						}
						case 250:
						{
							ip.z --;
							break;
						}
					}
					*cpu.c = T[ip.x][ip.y][ip.z] << (i * 8);
				}
				break;
			}
			case '"':
			{
				r[1] = ip.x;
				r[2] = ip.y;
				r[3] = ip.z;
				break;
			}
			case 'P':
			{
				p ++;
				s[p] = c;
				break;
			}
			case 'p':
			{
				*c = *s[p];
				s[p] = 0;
				if (p < 0)
					p --;
				break;
			}
			case 'c':
			{
				if (p == 255)
					return FULL_STACK;
				s[p + 1] = s[p];
				p++;
				break;
			}
			case 'u':
			{
				unsigned long long int t = s[p];
				if (p == 0)
					return NOT_ENOUGH_STACK
				s[p] = s[p - 1];
				s[p - 1] = t;
				break;
			}
			case '&':
			{
				if (p == 0)
					return NOT_ENOUGH_STACK;
				if (p == 1)
				{
					s[p - 1] = s[p - 1] && s[p];
					p --;
					s[p] = 0;
				}
				else
				{
					s[p - 1] = s[p - 1] && s[p];
					p -= 2;
				}
				break;
			}
			case '|':
			{
				if(p == 0)
					return NOT_ENOUGH_STACK;
				if (p == 1)
				{
					s[p - 1] = s[p - 1] || s[p];
					p --;
					s[p] = 0;
				}
				else
				{
					s[p - 1] = s[p - 1] || s[p];
					p -= 2;
				}
				break;
			}
			case '!':
			{
				if (s[p] != 0)
				{
					s[p] = !s[p];
					if (p == 0)
						s[p] = 0;
					else
						p --;
				}
				break;
			}
		}
		switch (ip.o)
		{
			case 120:
			{
				ip.x ++;
				break;
			}
			case 121:
			{
				ip.y ++;
				break;
			}
			case 122:
			{
				ip.z ++;
				break;
			}
			case 248:
			{
				ip.x --;
				break;
			}
			case 249:
			{
				ip.y --;
				break;
			}
			case 250:
			{
				ip.z --;
				break;
			}
		}
	}
	return 0;
}



#endif //BLANCMANGE
