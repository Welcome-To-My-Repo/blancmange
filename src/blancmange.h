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

static unsigned char TESSERACT [256][256][256];

struct BM_POINTER typedef POINTER;	//the Instruction Pointer
struct BM_CPU typedef CPU;		//The register and operand stack


#endif //BLANCMANGE
