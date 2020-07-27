#ifndef BLANCMANGE
#define BLANCMANGE

//errors

//instruction text is larger than torus
#define TXT_BOUNDS 1
//the stack doesn't specify a register
#define ERR_BAD_STACK 2

#define TX 256
#define TY 1024

//torus                   x   y
unsigned char TORUS [TX][TY];

//Program Counter direction constants
#define L '<'
#define R '>'
#define U '^'
#define D 'v'

//the program counter object
struct PC {
	//ID number for concurrent CPUs
	unsigned char ID;

	//coordinates on the torus
	unsigned short int X;
	unsigned short int Y;

	//either running (255), standby (128), or off (0)
	unsigned char state;

	//The current PC direction
	unsigned char exec;
} typedef PC;

//the Register object
struct REGISTER {
	unsigned long long int u; //the actual register itself
	long long int i; //the actual signed register itself
} typedef REGISTER;

//the Stack object
struct STACK {
	char S[256]; //256 available registers
	unsigned char T; //the position of the top
} typedef STACK;

//clock "speed" is either zero for auto or not zero for stepped execution.
unsigned char CLOCK = 0;

struct CPU {
	PC pc; //program counter
	REGISTER r [16]; //registers 0-F (A-F use unsigned integers)
	char cr; //current register
	STACK s; //The register stack
} typedef CPU;

unsigned char MAX_CPU = 0; //the number of running CPU's

CPU C[256]; //all possible CPUs

void init_cpu ( //initialize a CPU from the array
		unsigned char c, //which CPU
		unsigned char pid, //which ID
		unsigned short int x, //coordinate in torus
		unsigned short int y  //^
		);

int init_env ( //initialize the execution environment with a new program
		const char *txt, //text to place onto torus
		unsigned int length, //size of text
		unsigned char clock //clock
		);
int exec (unsigned char cpu); //run the environment


void init_cpu (	unsigned char c,
		unsigned char pid,
		unsigned short int x,
		unsigned short int y)
{
	if (c <= 255)
	{
	 	C[c].pc.ID = pid;
		C[c].pc.X = x;
		C[c].pc.Y = y;
		C[c].pc.exec = R;
	}
}

int init_env (const char *txt, unsigned int length, unsigned char clock)
{
	unsigned char x = 0;
	int y = 0;
	if (length > 262144)
		return TXT_BOUNDS;

	for (int i = 0; i < length; i ++)
	{
		TORUS[x][y] = txt[i];
		if (x == 255)
		{
			x ++;
			y ++;
		}
		else
		{
			x ++;
		}
	}
	CLOCK = clock;
	init_cpu (0, 0, 0, 0);
}

int exec (unsigned char cpu)
{
	CPU* c = C[cpu];
	c.pc.state = 0 - 1;
	while (c.pc.state > 0)
	{
		switch (TORUS[c.pc.X][c.pc.Y])
		{
			case ' ':
				break;
			case '^':
			{
				c.pc.exec = U;
				break;
			}
			case 'v':
			{
				c.pc.exec = D;
				break;
			}
			case '<':
			{
				c.pc.exec = L;
				break;
			}
			case '>':
			{
				c.pc.exec = R;
				break;
			}
			case 'j':
			{
				if (c.s.S[T] < 48 or c.s.S[T] > 70)
					return ERR_BAD_STACK;
				
			}

#endif //BLANCMANGE
