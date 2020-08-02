/*
* This source code is authored by o_o <yosngne@gmail.com> and is public domain.
* Use at your own risk and enjoy.
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
* designed to be used internally by a larger environment for the language.
*/

static unsigned char T [256][256][256];
/*
 * The Tesseract holds the instructions that the instruction pointer iterates
 * through.
 */


struct BM_POINTER;
struct BM_POINTER ip;
/*
 * IP holds the position and direction of the instruction pointer
 */


struct BM_CPU;
struct BM_CPU cpu;
/*
 * The CPU maintains the registers and operand stack as well as the current 
 * register
 */


int load (unsigned char *txt, long int l);
/*
 * Loads a program from source code into the tesseract.
 */


int run ();
/*
 * executes the instructions
 */

/*
 * Errors
 */

#define BAD_HEX 1


struct BM_POINTER
{
	char o;
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
	char c;
	/*
	 * current register
	 * 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
	 */

	unsigned char cr[4];	//byte registers
	unsigned int ir[6];	//word registers
	long long int ur[6];	//signed word registers
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
			case '{':
				{
					z++;
					break;
				}
			case ';':
				{
					y++;
					break;
				}
			case '\\':
				{
					unsigned char h[2];
					unsigned char x = 0;
					i++;
					h[0] = txt[i];
					i++;
					h[1] = txt[i];

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


#endif //BLANCMANGE
