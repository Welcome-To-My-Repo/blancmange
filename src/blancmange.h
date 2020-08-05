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


char (*input)();
void (*output)(char c);
int run (char (*I)(), void (*O)(char c));
/*
 * executes the loaded instructions.
 * I is the file descriptor for the default input.
 * O is the file descriptor for the default output.
 * It's usually a good choice for Unix/Linux to enter zero for I and one for O.
 *
 */

//errors
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
struct BM_POINTER ip;

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

struct BM_CPU cpu;

void (*t[256]) ();

void STEP ();

void NOP (); void INC_Z (); void DEC_Z (); void INC_Y (); void DEC_Y ();
void INC_X (); void DEC_X (); void JUMP (); void BRIDGE (); void END ();
void R0 (); void R1 (); void R2 (); void R3 (); void R4 (); void R5 ();
void R6 (); void R7 (); void R8 (); void R9 (); void RA (); void RB ();
void RC (); void RD (); void RE (); void RF (); void INC_R (); void DEC_R (); 
void SET_R_B (); void SET_R_W (); void SET_COORD (); void PUSH_R (); 
void POP_R (); void DUP_STACK (); void SWITCH (); void AND (); void OR ();
void NOT (); void XOR (); void ADD (); void SUB (); void MUL (); void DIV ();
void MOD (); void GT (); void LT (); void EQL (); void COND (); void BR_X (); 
void BR_Y (); void BR_Z (); void RD_B_COORD (); void WR_B_COORD (); 
void RD_W_COORD (); void WR_W_COORD (); void ISTREAM (); void OSTREAM (); 
void RMEM (); void WMEM (); void SHL_R (); void SHR_R (); void FL_B ();

void SYS ();

unsigned char running = 1;

int load (unsigned char* txt, long int l)
{
	unsigned char x = 0, y = 0, z = 0;
	long int i;
	t[0] = NOP; t[' '] = NOP; t['\''] = INC_Z; t[','] = DEC_Z;
	t['^'] = DEC_Y; t['v'] = INC_Y; t['>'] = INC_X; t['<'] = DEC_X;
	t['@'] = JUMP; t['#'] = BRIDGE; t['Q'] = END; t['0'] = R0; t['1'] = R1;
	t['2'] = R2; t['3'] = R3; t['4'] = R4; t['5'] = R5; t['6'] = R6;
	t['7'] = R7; t['8'] = R8; t['9'] = R9; t['A'] = RA; t['B'] = RB;
	t['C'] = RC; t['D'] = RD; t['E'] = RE; t['F'] = RF; t['i'] = INC_R;
	t['d'] = DEC_R; t['r'] = SET_R_B; t['R'] = SET_R_W; t['"'] = SET_COORD;
	t['P'] = PUSH_R; t['p'] = POP_R; t['c'] = DUP_STACK; t['u'] = SWITCH;
	t['&'] = AND; t['|'] = OR; t['_'] = XOR; t['!'] = NOT; t['+'] = ADD;
	t['-'] = SUB; t['*'] = MUL; t['/'] = DIV; t['%'] = MOD; t['g'] = GT;
	t['l'] = LT; t['='] = EQL; t['?'] = COND; t['b'] = BR_X; t['B'] = BR_Y;
	t['Z'] = BR_Z; t['['] = RD_B_COORD; t[']'] = WR_B_COORD;
	t['('] = RD_W_COORD; t[')'] = WR_W_COORD; t['I'] = ISTREAM;
	t['O'] = OSTREAM; t['m'] = RMEM; t['M'] = WMEM; t['s'] = SHL_R;
	t['S'] = SHR_R; t['f'] = FL_B; t['.'] = NOP;

	for (int i = 0; i < l; i ++)
	{
		if (txt[i] < 32 || txt[i] > 126)
		{
			continue;
		}
		else
		{
			switch (txt[i])
			{
				case '{':	//Starting a new plane
					{
						z++;
						x = 0;
						y = 0;
						break;
					}
				case ';':	//starting a new line
					{
						y++;
						x = 0;
						break;
					}
				case '\\':	//encoded raw byte
					{
						unsigned char h[2];
						unsigned char HEX = 0;
						i++;
						h[0] = txt[i];
						i++;
						h[1] = txt[i];
						//convert two digit hex to a byte
						if (h[0] < 58 && h[0] > 47)
						{
							h[0] -= 48;
							HEX = 16 * h[0];
						}
						else if (h[0] > 64 && h[0] < 71)
						{
							h[0] -= 55;
							HEX = 16 * h[0];
						}
						else if (h[0] > 96 && h[0] < 103)
						{
							h[0] -= 87;
							HEX = 16 * h[0];
						}
						else
						{
							return BAD_HEX;
						}

						if (h[1] < 58 && h[1] > 47)
						{
							h[1] -= 48;
							HEX += h[1];
						}
						else if (h[1] > 64 && h[1] < 71)
						{
							h[1] -= 55;
							HEX += h[1];
						}
						else if (h[1] > 96 && h[1] < 103)
						{
							h[1] -= 87;
							HEX += h[1];
						}
						else
						{
							return BAD_HEX;
						}
						T[x][y][z] = HEX;
						if (x == 255)
						{
							x++;
							y++;
						}
						else if (y == 255)
						{
							x++;
							y++;
							z++;
						}
						else
							x++;
						break;
					}
				case '~':
					{
						i ++;
						while (txt[i] != '~')
							i++;
						break;
					}
				default:
					{
						T[x][y][z] = txt[i];
						if (x == 255)
						{
							x++;
							y++;
						}
						else if (y == 255)
						{
							x++;
							y++;
							z++;
						}
						else
							x++;
						break;
					}
			}
		}
	}
	return 0;
}

int run (char (*I)(), void (*O)(char c))
{
	input = I;
	output = O;
	unsigned char pos;
	cpu.c = &cpu.r[0];

	ip.x = 0;
	ip.y = 0;
	ip.z = 0;
	ip.o = 120;

	while (running)
	{
		pos = T[ip.x][ip.y][ip.z];
		(*t[pos])();
		STEP ();
	}
	return 0;
}

void STEP ()
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

void NOP () {}
void INC_Z () {ip.o = 122;}
void DEC_Z () {ip.o = 250;}
void INC_Y () {ip.o = 121;}
void DEC_Y () {ip.o = 249;}
void INC_X () {ip.o = 120;}
void DEC_X () {ip.o = 248;}
void JUMP () {
	ip.x = cpu.r[1];
	ip.y = cpu.r[2];
	ip.z = cpu.r[3];
}
void BRIDGE () {
	STEP ();
}
void END () { running = 0; }

void R0 () {cpu.c = &cpu.r[0];}
void R1 () {cpu.c = &cpu.r[1];}
void R2 () {cpu.c = &cpu.r[2];}
void R3 () {cpu.c = &cpu.r[3];}
void R4 () {cpu.c = &cpu.r[4];}
void R5 () {cpu.c = &cpu.r[5];}
void R6 () {cpu.c = &cpu.r[6];}
void R7 () {cpu.c = &cpu.r[7];}
void R8 () {cpu.c = &cpu.r[8];}
void R9 () {cpu.c = &cpu.r[9];}
void RA () {cpu.c = &cpu.r[10];}
void RB () {cpu.c = &cpu.r[11];}
void RC () {cpu.c = &cpu.r[12];}
void RD () {cpu.c = &cpu.r[13];}
void RE () {cpu.c = &cpu.r[14];}
void RF () {cpu.c = &cpu.r[15];}

void INC_R () { (*cpu.c) ++;}
void DEC_R () { (*cpu.c) --;}
void SHL_R () {(*cpu.c) = (*cpu.c) << 1;}
void SHR_R () {(*cpu.c) = (*cpu.c) >> 1;}
void FL_B () {(*cpu.c) = (*cpu.c) ^ 1;}
void SET_R_B () {
	STEP(); 
	(*cpu.c) = T[ip.x][ip.y][ip.z];
}
void SET_R_W () {
	STEP ();
	(*cpu.c) = 0;
	unsigned long long int tmp;
	for (int i = 0; i < 8; i ++)
	{
		STEP();
		tmp = T[ip.x][ip.y][ip.z];
		tmp = tmp << i * 8;
		(*cpu.c) = (*cpu.c) ^ tmp;
	}
}
void SET_COORD () {
	cpu.r[1] = ip.x;
	cpu.r[2] = ip.y;
	cpu.r[3] = ip.z;
}
void PUSH_R () {
	cpu.p ++;
	cpu.s[cpu.p] = cpu.c;
}
void POP_R () { 
	(*cpu.c) = (*cpu.s[cpu.p]);
	cpu.s[cpu.p] = 0; 
	cpu.p --; 
}
void DUP_STACK () { cpu.s[cpu.p + 1] = cpu.s[cpu.p]; cpu.p ++; }
void SWITCH () { 
	unsigned long long int *t = cpu.s[cpu.p];
	cpu.s[cpu.p] = cpu.s[cpu.p - 1];
	cpu.s[cpu.p - 1] = t;
}
void AND () {
	(*cpu.s[cpu.p - 1]) = (*cpu.s[cpu.p - 1]) & (*cpu.s[cpu.p]);
	cpu.s[cpu.p] = 0;
	cpu.p --;
}
void OR () {
	(*cpu.s[cpu.p - 1]) = (*cpu.s[cpu.p - 1]) | (*cpu.s[cpu.p]);
	cpu.s[cpu.p] = 0;
	cpu.p --;
}
void NOT () {
	(*cpu.s[cpu.p - 1]) = ~ (*cpu.s[cpu.p]);
	 cpu.s[cpu.p] = 0;
	 cpu.p --;
}
void XOR () {
	(*cpu.s[cpu.p - 1]) = (*cpu.s[cpu.p - 1]) ^ (*cpu.s[cpu.p]);
	cpu.s[cpu.p] = 0;
	cpu.p --;
}
void ADD () {
	(*cpu.s[cpu.p - 1]) = (*cpu.s[cpu.p - 1]) + (*cpu.s[cpu.p]);
	cpu.s[cpu.p] = 0;
	cpu.p --;
}
void SUB () {
	(*cpu.s[cpu.p - 1]) = (*cpu.s[cpu.p - 1]) - (*cpu.s[cpu.p]);
	cpu.s[cpu.p] = 0;
	cpu.p --;
}
void MUL () {
	(*cpu.s[cpu.p - 1]) = (*cpu.s[cpu.p - 1]) * (*cpu.s[cpu.p]);
	cpu.s[cpu.p] = 0;
	cpu.p --;
}
void DIV () {
	(*cpu.s[cpu.p - 1]) = (*cpu.s[cpu.p - 1]) / (*cpu.s[cpu.p]);
	cpu.s[cpu.p] = 0;
	cpu.p --;
}
void MOD () {
	(*cpu.s[cpu.p - 1]) = (*cpu.s[cpu.p - 1]) % (*cpu.s[cpu.p]);
	cpu.s[cpu.p] = 0;
	cpu.p --;
}

void GT () {
	if ((*cpu.s[cpu.p - 1]) > (*cpu.s[cpu.p]))
		cpu.r[0] = 0 - 1;
	else
		cpu.r[0] = 0;
}
void LT () {
	if ((*cpu.s[cpu.p - 1]) < (*cpu.s[cpu.p]))
		cpu.r[0] = 0 - 1;
	else
		cpu.r[0] = 0;

}
void EQL () {
	if ((*cpu.s[cpu.p - 1]) == (*cpu.s[cpu.p]))
		cpu.r[0] = 0 - 1;
	else
		cpu.r[0] = 0;

}
void COND () {
	if (cpu.r[0] == 0)
		STEP ();
}
void BR_X () {
	if (cpu.r[0] != 0)
		ip.o = 120;
	else
		ip.o = 248;
}
void BR_Y () {
	if (cpu.r[0] != 0)
		ip.o = 121;
	else
		ip.o = 249;
}
void BR_Z () {
	if (cpu.r[0] != 0)
		ip.o = 122;
	else
		ip.o = 250;
}

void RD_B_COORD () {}
void WR_B_COORD () {}
void RD_W_COORD () {}
void WR_W_COORD () {}
void ISTREAM () {cpu.r[0] = (*input)();}
void OSTREAM () {(*output)((char)cpu.r[0]);}
void RMEM () {}
void WMEM () {}

void SYS () {}

#endif //BLANCMANGE
