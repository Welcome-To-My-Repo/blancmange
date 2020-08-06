# Blancmange Virtual Machine

"blancmange.h" is designed to be included in a third party program that manages loading instructions and starting the virtual machine.
Directions for devekoping a front end are found in "blancmange.h".

# Compiling

The Blancmange Virtual Machine uses pure C without any libraries required.
Any C99+ compiler can compile Blancmange with the provided sample front end.
A sample makefile is provided that works with CLANG and GCC.

# Installing

Install Blancmange wherever your executable path search will find it.
The sample Blancmange will work as a command-line utility.

# Uninstalling

Delete the executable from wherever you put it.

# Using the Reference Frontend

The reference program compiles to an executable called "blancmange".
It takes a number of files to parse as source code. 
The instructions are concatenated in the order they were given in the command to "blancmange".

The debugging functionality can be accessed by including a dash as one of the arguments.
