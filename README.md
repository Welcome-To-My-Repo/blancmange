Blancmange
===

A three dimensional esoteric RISC.

---

# Overview

Blancmange is an interpreted RISC that supports three dimensional traversal of instructions.
The Instruction Pointer can move with six degrees of freedom within a three dimensional space.

## Reference Implementation

Blancmange is implemented as a portable virtual machine backend for the C language.
The entire backend is contained in a single header file designed to be used by a front end application that will handle loading and executing source code.

A simple command-line front end has been provided with the Blancmange header that facilitates loading, executing, and basic program debugging.

---

# The Instruction Pointer

In normal architectures, the instruction pointer moves only forward.
In Blancmange, the instruction pointer can move in six directions.
Instructions are stored in a three dimensional tesseract of 256x256x256 bytes.
A tesseract allows the pointer to iterate beyond the bounds of the cube and enter at the opposite face from the exit point.

## Instruction Pointer Instructions

* ` `	no operation
* `.`	no operation
* `'`	increase on Z-axis
* `,`	decrease on Z-axis
* `^`	increase on Y-axis
* `v`	decrease on Y-axis
* `>`	increase on X-axis
* `<`	decrease on X-axis
* `@`	unconditional jump to coordinates in r1-r3
* `#`	unconditional bridge.
* `Q`	end program

---

# The CPU Registers

The Blancmange virtual machine has a total of sixteen 64 bit word registers.
Data can be loaded and stored in registers as a byte or a word.
Only a single register can be operated on at one time.
The "current" register can be selected using 0-9 and A-F.

Register 0 (r0) is used as a flag for comparison instructions.
Registers 1-3 (r1-r3) are used to hold x, y, and z coordinates respectively.

## Register Instructions

* `0123456789ABCDEF` Select Current Register
* `i`	Increment the current register.
* `d`	Decrement the current register.
* `s`	Shift left by 1 bit in the current register.
* `S`	Shift right by 1 bit in the current register.
* `f`	Flip the first bit in the current register.
* `r`	Set the current register to the byte after this instruction.
* `R`	Set the current register to the word (next eight bytes) after this instruction.
* `"`	Set r1-r3 to the current instruction pointer coordinates.
* `!`	Perform a binary NOT on the current register.
* `P`	Push the current register to the stack.

---

# The Register Stack

Mathematical and logical operators determine which registers to use by the register stack.
The stack is a LIFO structure that can hold up to 256 register identifiers that are popped by operators.
Operators will pop y, then x, then push x holding the result.

## Stack Manipulator Instructions

* `p`	Pop the top of the stack and set the current register.
* `c`	Duplicate the top of the stack.
* `u`	Switch the top two stack elements.

## Stack Operator Instructions

* `&`	binary AND
* `|`	binary OR
* `_`	binary XOR
* `+`	addition
* `-`	subtraction
* `*`	multiplication
* `/`	division
* `%`	modulus

---

# Branching

Blancmange offers both a conditional execution instruction as well as three different branch instructions.
Branching is conditional on the value in r0.
The value of r0 can be set automatically by comparison instructions which set r0 to maximum if the comparison is true, or zero if the comparison is false.

## Flag Register Instructions

* `g`	If x > y, set r0 to max, else set r0 to 0.
* `l`	If x < y, set r0 to max, else set r0 to 0.
* `=`	If x == y, set r0 to max, else set r0 to 0.
* `?`	If r0 is max, execute the next instruction, else emulate the unconditional branch.
* `x`	If r0 is max, emulate `>`, else emulate `<`.
* `y`	If r0 is max, emulate `^`, else emulate `v`.
* `z`	If r0 is max, emulate `'`, otherwise emulate `,`.

---

# I/O

Blancmange has several methods of input and output from the CPU.
Individual bytes and words can be read and written to the program space.
When a word is read or written, the direction is the same as the direction of the instruction pointer. So if a word is stored in ascending Y indices, then the instruction pointer would have to be iterating towards increasing Y values in order for the word to be read properly.

## I/O Instructions

* `[`	Set the current register to the byte at r1-r3.
* `]`	Set the byte at r1-r3 from the current register.
* `(`	Set the current register to the word beginning at r1-r3.
* `)`	Set the word beginning at r1-r3 from the current register.
* `I`	Read a byte from the default stream and set the current register with it.
* `O`	Write a byte to the stream from the current register.
* `m`	Read byte from the memory address in r4 at the offset in r5 to the current register.
* `M`	Write a byte from the current register to the memory address in r4 at the offset in r5.

---

# System Interface

**Low level stuff is not implemented right now.**
As a side effect, the `m` and `M` instructions are useless as the runtime is contained inside the executable space.

* *`Y`	Calls Kernel using r4-r9 for parameters. Return value is placed in r4.*

---

# Blancmange Source Format

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

* `{`	Begins a new 256x256 plane before 256 lines have occurred.
* `;`	Begin a new line before 256 characters has occurred.
* `~`	surrounds comments
* `\`	escapes byte values

Source code file extensions can be either ".bm" or ".mange".
These extensions are recognized by the Vim syntax highlighting theme.

## Encoding Raw Bytes in Source Code

Raw byte values can be encoded in a text file through use of the backslash, `\`.
Each byte is represented by a two-digit hexadecimal value prepended by a backslash as in `\6F` or `\a0`. This byte representation is textual and is only valid written horizontally from left to right.

Be aware that each three-character encoded byte only represents a single byte internally and will visually distort the alignment of source code lines along the X-axis.

---
