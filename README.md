Blancmange
===

An esoteric language.

---

# Instruction Pointer Instructions

* ` `	no operation
* `.`	move forward
* `,`	move backward
* `^`	Rotate up
* `v`	Rotate down
* `<`	rotate left
* `>`	rotate right
* `@`	unconditional jump using r1-r3 for coordinates
* `#`	unconditional bridge

---

# Register Instructions

* `0123456789ABCDEF` Select Register
* `l`	shift left
* `r`	shift right
* `L`	rotate left
* `R`	rotate right
* `f`	flip first bit
* `j`	flip last bit
* `"`	set r1-r3 to current coordinates
* `P`	Push register to stack

---

# Register Operation Stack Instructions

* `p`	pop from stack
* `d`	duplicate top
* `s`	sWitch two top
* `&`	binary AND
* `o`	binary OR
* `!`	binary NOT
* `+`	addition
* `-`	subtraction
* `*`	multiplication
* `/`	division
* `%`	modulus

---

# Flag Register Instructions

* `g`	greater than, set r0 to 1
* `l`	less than, set r0 to 1
* `=`	if equal, set r0 to 1
* `?`	if r0 is 0, skip next instruction

---

# I/O Instructions

* `[`	reads byte from coordinates in r1-r3 and sets r0 with byte
* `]`	writes byte from r0 to coordinates in r1-r3
* `(`	reads word from coordinates in r1-r3 and sets r4 with it
* `)`	writes word from r4 to coordinates in r1-r3

---

# Buffer Instructions

* `M`	Creates new buffer with size taken from r4. Sets r4 with the buffer address.
* `m`	Frees buffer at address in r4
* `w`	reads word from buffer located in r4 at offset in r5 to r6
* `W`	writes word in r6 at offset in r5 at buffer located in r4
* `b`	reads byte from buffer located in r4 at offset in r5 to r0
* `B`	writes byte in r1 at offset in r5 at buffer located in r4
* `x`	sets buffer located at r4 to be executable
* `z`	sets buffer located at r4 to be read/write-able
* `E`	Executes buffer located at r4

---

# System Interface

* `S`	Calls Kernel using r4-r9 for parameters. Return value is placed in r4.

---

# Blancmange Source Format

Blancmange executes code in a three dimensional tesseract.
The dimensions of the cube are 256^3 bytes.

source code is formatted as 256 individual 256x256 planes of x and y coordinates
each plane added to the source represents a new plane further along the z coordinate.
All three coordinates begin at zero.
Each character across increases x.
Each line increases y.
Each additional plane increases z.

* `{`	begin a new 256x256 plane on the next line
* `;`	end a line before 256 chatacters
* `}`	end a plane before 256 lines

---

# The Program Counter

The Program Counter can move forward or backward along an axis.
The direction can be rotated upward, downward, left, or right.
When a program starts, the PC begins at 0,0,0 and moves forward along the x axis.

---

# Blancmange Registers

There are sixteen registers in Blamcmange.
Registers 0-3 are 8bit.
Registers 4-9 are unsigned 64bit.
Registers A-F are signed 64bit.
r0 doubles as a flag register for comparisons.
A register can be selected as the current register.
Register instructions operate on the current register.

---

# The Register Stack

Operations that use two registers use the register stack.
Registers are pushed to the stack via their ID.
Stack instructions consume register ID's from the stack to determine which registers they operate on.
Each instruction will pop y, then x and will perform an operation of x by y (as in x / y or x + y).
