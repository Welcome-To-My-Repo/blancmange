Blancmange
===

An esoteric language.

---

# Instruction Pointer Instructions

* ` `	no operation
* `.`	Reverse direction
* `^`	Rotate Upward
* `v`	Rotate Downward
* `<`	Rotate to the left
* `>`	Rotate to the right
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
* `"`	set r1-r3 to current coordinates
* `P`	Push register to stack

---

# Operand Stack Instructions

* `p`	pop from stack
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

---

# I/O Instructions

* `[`	reads byte from coordinates in r1-r3 and sets r0 with byte
* `]`	writes byte from r0 to coordinates in r1-r3
* `(`	reads word from coordinates in r1-r3 and sets r4 with it
* `)`	writes word from r4 to coordinates in r1-r3
* `I`	Read in a byte from default stream into r0
* `O`	Write a byte to the default stream from r0

---

# System Interface

* `Y`	Calls Kernel using r4-r9 for parameters. Return value is placed in r4.

---

# Blancmange Source Format

Blancmange executes code in a three dimensional tesseract.
The dimensions of the tesseract cube are 256^3 bytes.
The tesseract allows the Program Counter to iterate past the bounds of the cube and continue by entering on the opposite face from its exit point.

The source code is formatted as 256 individual 256x256 planes of x and y coordinates.
Each plane added to the source represents a new plane further along the z coordinate.

All three coordinates begin at zero in the bottom left back corner of the cube.
Each character to the right increases in the x-axis.
Each line downward increases in the y-axis.
Each additional plane increases in the z-axis.

The Program Counter will move along a path that matches the visual representation of the source code.
The source code is oriented so that it represents a view of the cube from its bottom, facing towards higher Z coordinates with X and Y coordinates increasing to the bottom right of the text.

* `{`	begin a new 256x256 plane on the next line
* `;`	end a line before 256 chatacters
* `}`	end a plane before 256 lines
* `~`	surrounds comments
* `\\`	escapes byte values
* Tab characters and other invisible or control characters are ignored.

## Encoding Raw Bytes in Source Code

Raw byte values can be enoded in a text file through use of the backslash, `\\`.
Each byte is represented by a two-digit hexadecimal value prepended by a backslash.
`\6F` or `\a0`

Be aware that each three-character byte represents a single byte internally.
Code appearing after encoded bytes may not be properly aligned.

---

# The Program Counter

The Program Counter can move forward or backward along an axis.
The direction can be rotated upward, downward, left, or right.
When a program starts, the PC begins at 0,0,0 and moves forward along the x axis.

## Orientation

Normally, n-dimensional programming languages change the direction of the pointer by orienting it to an axis where it increases or decreases.
Blancmange uses rotations instead of orientations; the movement of the pointer is disjoint from the axis of the cube.
The Instruction Pointer has the option to rotate 90 degrees left, right, upwards, or downwards, with respect to its current forward direction.
Consider if the pointer started execution increasing on the X-axis.
A *rotate downwards* instruction would turn the pointer to increase on the Z-axis.
Consider again if the pointer was increasing on the X-axis and encountered this series of instructions, `v>>^^`.
By the second *rotate upwards* instruction, the pointer would be decreasing on the Z-axis.
This is because the local axis of the pointer were rotated 180 degrees as a side effect.
This rotation could be corrected by this series of instructions, `^^.`.
The two upward rotations would right the pointer, but it would be facing the opposite way, so the *reverse direction* instruction is used.

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

# The Operand Stack

Operations that use two registers use the register stack.
Registers are pushed to the stack via their ID.
Stack instructions consume register ID's from the stack to determine which registers they operate on.
Each instruction will pop y, then x and will perform an operation of x by y (as in x / y or x + y).
