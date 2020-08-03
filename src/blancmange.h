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

void (*txt[256])();


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
BM_POINTER ip;

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

BM_CPU cpu;

void INC_Z ();
void DEC_Z ();
void INC_Y ();
void DEC_Y ();
void INC_X ();
void DEC_X ();
void JUMP ();
void BRIDGE ();
void END ();

void R0 ();
void R1 ();
void R2 ();
void R3 ();
void R4 ();
void R5 ();
void R6 ();
void R7 ();
void R8 ();
void R9 ();
void RA ();
void RB ();
void RC ();
void RD ();
void RE ();
void RF ();

void INC_R ();
void DEC_R ();
void SET_R_B ();
void SET_R_W ();
void SET_COORD ();
void PUSH_R ();

void POP_R ();
void DUP_STACK ();
void SWITCH_STACK ();
void AND ();
void OR ();
void NOT ();
void XOR ();
void ADD ();
void SUB ();
void MUL ();
void DIV ();
void MOD ();

void GT ();
void LT ();
void EQL ();
void COND ();
void BR_X ();
void BR_Y ();
void BR_Z ();

void RD_B_COORD ();
void WR_B_COORD ();
void RD_W_COORD ();
void WR_W_COORD ();
void ISTREAM ();
void OSTREAM ();
void RD_B_MEM ();
void WR_B_MEM ();
void RD_W_MEM ();
void WR_W_MEM ();

void SYS ();

int load (unsigned char* txt, long int l)
{
	unsigned char x = 0, y = 0, z = 0;
	long int i;
	txt['.'] = INC_Z;
	txt[','] = DEC_Z;
	txt['^'] = INC_Y;
	txt['v'] = DEC_Y;
	txt['>'] = INC_X;
	txt['<'] = DEC_X;
	txt['@'] = JUMP;
	txt['#'] = BRIDGE;
	txt['Q'] = END;
	txt['0'] = R0;
	txt['1'] = R1;
	txt['2'] = R2;
	txt['3'] = R3;
	txt['4'] = R4;
	txt['5'] = R5;
	txt['6'] = R6;
	txt['7'] = R7;
	txt['8'] = R8;
	txt['9'] = R9;
	txt['A'] = RA;
	txt['B'] = RB;
	txt['C'] = RC;
	txt['D'] = RD;
	txt['E'] = RE;
	txt['F'] = RF;
	txt['i'] = INC_R;
	txt['d'] = DEC_R;
	txt['r'] = SET_R_B;
	txt['R'] = SET_R_W;
	txt['"'] = SET_COORD;
	txt['P'] = PUSH_R;
	txt['p'] = POP_R;
	txt['c'] = DUP_STACK;
	txt['u'] = SWITCH_STACK;
	txt['&'] = AND;
	txt['|'] = OR;
	txt['!'] = NOT;
	txt['+'] = ADD;
	txt['-'] = SUB;
	txt['*'] = MUL;
	txt['/'] = DIV;
	txt['%'] = MOD;
	txt['g'] = GT;
	txt['l'] = LT;
	txt['='] = EQL;
	txt['?'] = COND;
	txt['b'] = BR_X;
	txt['B'] = BR_Y;
	txt['Z'] = BR_Z;

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
