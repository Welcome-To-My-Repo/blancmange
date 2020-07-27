Blancmange 64
===

Blancmange 64 is an esoteric interpreted programming language inspired by Befunge-93. 
Blancmange's main difference from Befunge is that it is intended to be an entirely serious language for use in the real world.

---


## The Program Counter

The Program Counter marks the current instruction.
Unlike conventional program counters, the B64 PC is able to move forward, backward, upward, and downward.
The PC moves through a torus of 2^16-1 x 2^16-1 bytes.

### Concurrency

Blancmange supports up to 255 separate Program Counters simultaneously.
Each program counter is assigned a byte identifier upon creation.
The initial Program Counter always has an ID of 0.

### Torus Coordinates

The torus coordinates begin at the upper left corner at 0x0.
Coordinates are compressed into the two least significant 16 bit values in an integer type.
For example, an integer holding the value 65,356 represents the coordinates 1,0 in the torus.

### Program Counter Instructions

* ` ` Whitespace represents no operation. The current direction is continued.
* `^` Change direction upwards.
* `v` Change direction downwards.
* `<` Change direction right.
* `>` Change direction left.
* `j` jump to coordinates using register 0.
* `@` end program

* `!` spawn a new PC.
* `~` Pop x and pause the PC with the matching character.
* `,` Pop x and resume the PC with the matching character.
* `\`` Pop x and end the PC with the matching character.
* `t` Pop x and push x with PC identifier
* `T` Pop x and push x with a byte representing the total number of Program Counters running.

---

## Registers

There are sixteen registers numbered 0 through F.
Datums can be loaded and saved from registers.
Register instructions operate on a single register.
The current register can be selected using its number.
Any loading and saving operations are done with that register until another is selected.
Operations are performed using two registers as X and Y operands.

Registers A-F are used for unsigned integer operations

### Register Operations

* `0123456789ABCDEF` Sets the current register.
* `i` Load the integer following this instruction into the current register.
* `c` Load the character following this instruction into the current register.
* `X` Load a zero torus X coordinate into the current register.
* `Y` Load a zero torus Y coordinate into the current register.
* `Q` Loads the current X,Y position if the PC onto the register.
* `P` Pushes the current register onto the stack.

---

## The Stack

The Stack is a LIFO structure used to control access to registers for operations.
In order for a register to be used in an operation, its number mustbe pushed onto the stack.
Instructions that operate on register data will know which registers to use by popping register numbers off the stack and accessing the corresponding registers.

### Stack Instructions

* `p` Pop a register from the stack and do nothing.
* `:` Duplicate the top of the stack.
* `\` Switch the top two Datums on the stack.

---

## Data Types

Blancmange supports three data types, signed and unsigned 64 bit words and the unsigned byte.
These types can be used interchangeably.
Signed and Unsigned Words are converted by copying between registers.
Copying a word to a character will only preserve the least significant byte.
únsigned Words are used for coordinates and memory addresses outside of the torus and anywhere else where two's compliment won't make sense.
The torus only supports information in unsigned bytes, so word types are stored across a series of eight bytes in little endian format.

### Data Instructions

All instructions below will pop register y, then pop register x, then push register x with the result.

* `+` x \+ y
* `-` x \- y
* `*` x \* y
* `/` x \/ y
* `%` x \% y

* `&` Binary AND of x and y
* `O` Binary OR of x and y
* `N` Binary NOT of the top
* `!` Logical NOT of the top. If top is zero, a max integer value is pushed. If top is non-zero, a zeroed integer is pushed.

* `C` copy y to x.

---

## Branching

Branch instructions use a special Branch Flag that is always set to one or zero.
Comparison instructions are used to set the Branch Flag.
Comparison instructions will set the flag to one for true and zero for false.
Comparison instructions pop register y, then pop register x, then set the Branch Flag.

* `l` x < y
* `g` x > y
* `=` x == y
* `?` If true execute the next instruction. If false, skip the next instruction.
* `|` If true, emulate ^. If false, emulate v.
* `_` If true, emulate <. If false, emulate >.
* `#` Unconditionally skips the next instruction.

---

## Input and Output

Blancmange programs are guaranteed to always have a default input and output stream.
These streams are formatted so that characters and integers can both be read and written to them without requiring conversion.

### Input and Output Instructions

Both Read and Write pop a register from the top of the stack.

* `[` Read a character into the top register.
* `]` Write a character from the top register.
* `{` Read an integer into the top register.
* `}` Write an integer into the top register.

There is a set of special read and write instructions that allow Blancmange to read and write to and from the torus.
* `r` Pops a register from the stack holding coordinates. Places the character found at those coordinates in the popped register and pushes it.
* `w` Pops a registers y and x from the stack and writes the character in x at the coordinates y.
* `R` Pops a register from the stack holding coordinates. Places the integer found at those coordinates in the popped register and pushes it.
* `W` Pops registers y and x from the stack and writes the integer in x at the coordinates y.

Integers are read and written in little endian format in the current direction of the PC.

---

## Devices

Devices are objects created by the runtime mapped onto the torus that allow Blancmange programs to interface with the underlying system.
Specific bytes can be read and written to that represent device states or messages.
The simplest device would be a two byte mapping,
[ ][ ]
where the left byte is a single-byte buffer to be read from, and the right byte a stream to write messages to.
A more complex device might include more mappings to represent a wider buffer, error flags, multiple streams, or states.
Blancmange offers multiple pre-defined devices to allow access to various resources.

---

### The Page Device

If a Blancmange program requires memory beyond what is available in the torus, the Page object can be used.
The Page object represents a memory segment of 1KB.
It has a 1x9 byte mapping with a byte the left and an integer on the left.

[read][write]

The first byte can be read from.
It represents a byte from the array.
The integer represents the address of the byte in the Page.
The address can be updated by writing a new integer to it.

#### Page Device Instructions

* `Z` Pops x and y. Creates page with x bytes at y coordinates.
* `z` Pops a register with the coordinates of a Page to destroy.

---

### The File Device

The File device lets Blancmange read and write to the filesystem.
The File device has a 2x? byte mapping.

[W: rwa flags][W: message][R: Error][W: buffer size][W: buffer location]
[R: file size][W: file position]
[W: file pathname

#### Flags

Flags Are written to "rwa flags"

Bit Representation
1. read only 
2. write only 
4. read and write only
8. open in append mode
16. open in overwrite mode

#### Messages

Messages are written to "message"

* "r" Read buffer size bytes from file and place in buffer
* "w" Write buffer size bytes to file from buffer
* "o" Open file
* "c" Close file

#### Error Flags

Errors are read from "Error"

* "x" File couldn't be opened
* "w" File couldn't be written
* "r" File couldn't be read
* "m" not enough storage
