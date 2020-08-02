Blancmange
===

An esoteric language.

---

# Instruction Pointer Instructions

* ` `	no operation
* `.`	Increase on Z-axis
* `,`	Decrease on Z-axis
* `^`	Increase on Y-axis
* `v`	Decrease on Y-axis
* `>`	Increase on X-axis
* `<`	Decrease on X-axis
* `@`	unconditional jump using r1-r3 for coordinates
* `#`	unconditional bridge
* `Q`	end program

---

# Register Instructions

* `0123456789ABCDEF` Select Register
* `s`	shift left
* `S`	shift right
* `r`	rotate left
* `R`	rotate right
* `f`	flip first bit
* `j`	flip last bit
* `i`	increment
* `d`	decrement
* `k`	set register to the byte after this instruction
* `K`	set register to the word after this instruction
* `"`	set r1-r3 to current coordinates
* `P`	Push register to stack

---

# Operand Stack Instructions

* `p`	pop from stack and set the current register to the value in the popped register.
* `c`	duplicate top
* `u`	sWitch top with below
* `&`	binary AND
* `|`	binary OR
* `_`	binary XOR
* `!`	binary NOT
* `+`	addition
* `-`	subtraction
* `*`	multiplication
* `/`	division
* `%`	modulus

---

# Flag Register Instructions

* `g`	greater than, set r0 to 255
* `l`	less than, set r0 to 255
* `=`	if equal, set r0 to 255
* `?`	if r0 is 0, skip next instruction
* `b`	if r0 is 0, emulate `<` otherwise emulate `>`
* `B`	if r0 is 0, emulate `v` otherwise emulate `^`
* `Z`	if r0 is 0, emulate `.` otherwise emulate `,`

---

# I/O Instructions

* `[`	reads byte from coordinates in r1-r3 and sets r0 with byte
* `]`	writes byte from r0 to coordinates in r1-r3
* `(`	reads word from coordinates in r1-r3 and sets r4 with it
* `)`	writes word from r4 to coordinates in r1-r3
* `I`	Read in a byte from default stream into r0
* `O`	Write a byte to the default stream from r0
* `w`	Write byte from r0 to memory address r5 plus offset r6
* `W`	write word from r4 to memory address r5 plus offset r6
* `j`	read byte from memory address r5 plus offset r6 to r0
* `J`	read word from memory address r5 plus offser r6 to r4

---

# System Interface

* `Y`	Calls Kernel using r4-r9 for parameters. Return value is placed in r4.

---

# Blancmange Source Format

Blancmange executes instructions by moving the instruction pointer through a three dimensional tesseract.
The tesseract allows the instruction pointer to freely iterate beyond the dimensions of the cube by entering at the opposite face of its exit point preventing bounds errors.
The tesseract contains a three dimensional cube with 256^3 byte indexes.

A Blancmange source file divides the three dimensions of instructions into individual planes along the Z-axis.
Each two dimensional plane has an X and Y axis with 256x256x1 dimensions.
Multiple planes of instructions are listed in descending order in a source file corresponding to increasing Z-axis coordinates.

Both the source file and cube are oriented so that the zero origin of all three axis occurs in the upper left corner. 
Source code represents a view of the cube looking up from the bottom towards higher Z-axis coordinates.
Each character to the right increases in the x-axis.
Each line downward increases in the y-axis.
Each additional plane increases in the z-axis.

---

## Source Code Formatting

Blancmange source code uses only visible ASCII characters and the space.
Invisible and control characters are ignored.
Blancmange parses source code by reading in groups of 256 characters and 256 lines.

* `{`	Begin a new 256x256 plane.
* `;`	Begin a new line before 256 characters has occurred.
* `~`	surrounds comments
* `\\`	escapes byte values
* Tab characters and other invisible or control characters are ignored.

## Encoding Raw Bytes in Source Code

Raw byte values can be enoded in a text file through use of the backslash, `\\`.
Each byte is represented by a two-digit hexadecimal value prepended by a backslash.
`\6F` or `\a0`.

Be aware that each three-character byte represents a single byte internally.
Code appearing after encoded bytes may not be properly aligned.

---

# The Program Counter

The Program Counter can move forward or backward along an axis.
The axis and direction can be dynamically changed throughout a program.
When a program starts, the PC begins at 0,0,0 and moves forward along the x axis.

The cube is oriented so that the origin point of the three axis is located in the upper left corner of the source file.
Each character to the right increases on the X-axis.
Each line increases on the Y-axis.
Each new plane increases on the Z-axis.

---

# Blancmange Registers

There are sixteen registers in Blamcmange.
Registers 0-3 are unsigned 8bit.
Registers 4-9 are unsigned 64bit.
Registers A-F are signed 64bit.
r0 doubles as a flag register for comparisons.
A register can be selected as the current register.
Register instructions operate on the current register.

---

# The Operand Stack

Operations that use two registers use the register stack.
Registers are pushed to the stack via their ID.
Stack instructions consume register ID's from the stack to determine which registers they operate on.
Each instruction will pop y, then x and will perform an operation of x by y (as in x / y or x + y).

# 
