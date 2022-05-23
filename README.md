# beep
 Beep programing language

- Explicit over implicit

### Operators


### Variable declarations
A declaration  declares a new variable for the current scope. 
The type have to be explicitly set.

---------------------------------------------------------------
x  : i32; // declares "x" as type i32 (32-bit integer)
y,z: i16; // declares "y" and "z" as type i16 (16-bit integer(short))
s  : string;
a  : [i32];
---------------------------------------------------------------

// Note:
// Casting a i32 to f32 -> x:i32=123; x:=321; (casting can be done by replacing the type) x:f32= 3.21; 

### Assignment statement
The assignment statement assigns a new value to a variable

---------------------------------------------------------------
x    : i32 = 123;   	  // declares variable "x" as type i32 and assigns it a value 
x    := 312;	      	  // assigns "x" a new value 
x, y : i32, f32 = 1, 1.2; // declares variable "x" and "y" as type i32 and f32 and assigns them a value
s    : string = "Hello";
a    : [i32]  = {3,2,1};
---------------------------------------------------------------

## Constant declaration/assignment
// TODO: Not sure how this will look. maybe const is implicit and var is explicit


### Namespace 
Sets the "name" of the code in a file directory way.
---------------------------------------------------------------
------------------------------------
namespence core.math

proc round f32: value, i8: decimals return f32: result {
    ...
}
------------------------------------

// The using namespace name is the same as the last element in the using path
------------------------------------
using core.math; 

namespace myprogram.commerce;

proc do_something f32: value, i8 decimals {
    value:= math.round(value, decimals);
}
------------------------------------

---------------------------------------------------------------

### Access modifiers
// TODO: not sure how this will look like. private and public proc and func's

### Control flow

#### Loops

#### if statement
--------------------------------
// if 
if x > 0 {
    io.print("x is over zero");
}

// if-else 
if x > 0 {
    io.print("x is over zero");
}
elseif x < 0 {
    io.print("x is under zero");
}
else {
    io.print("x is zero");
}

// switch with expression in case
if x {
    case > 0:
        io.print("x is over zero");
    case < 0:
        io.print("x is under zero");
    case:
        io.print("x is zero");
}
// switch with expression in if
if x = {
    case 0:
        io.print("x is zero");
    case 1:
        io.print("x is one");
    case:
        io.print("x is neither 0 nor 1");
}
--------------------------------

#### for statement
