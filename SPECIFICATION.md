
# The Nasal language specification
Despite existing for over 20 years, there is no official Nasal specification. Here's a crack at one.

- [Keywords](#keywords)
  - [Variable Declaration](#variable-declaration)
  - [Function Declaration](#function-declaration)
  - [Conditional Control Flow Keywords](#conditional-control-flow-keywords)
  - [Iterative Control Flow Keywords](#iterative-control-flow-keywords)
  - [Control Flow Keywords](#control-flow-keywords)
  - [Boolean Literals](#boolean-literals)
  - [Null Value](#null-value)
- [Built-in functions](#builtin-functions)
- [Standard Library](#standard-library)
  - [Math](#math)
- [Language Internals](#language-internals)
  - [Bytecode VM](#bytecode-vm)
    - [Opcodes](#opcodes)


## Keywords

### Variable Declaration
| Keyword |
|---------|
| `var`   |

### Function Declaration
| Keyword |
|---------|
| `func`  |

### Conditional Control Flow Keywords
| Keyword |
|---------|
| `if`    |
| `elsif` |
| `else`  |

### Iterative Control Flow Keywords
| Keyword   |
|-----------|
| `for`     |
| `foreach` |
| `while`   |

### Control Flow Keywords

| Keyword    |
|------------|
| `continue` |
| `break`    |
| `return`   |

### Boolean Literals
| Keyword |
|---------|
| `true`  |
| `false` |

### Null Value
| Keyword |
|---------|
| `nil`   |


## Builtin functions
In lieu of formal API documentation, in the meantime here is an overview of Nasals built-in functions. Note that built-in functions, or "builtins", are implemented directly in the Nasal intrepreter, they are integral. Some confusion can arise when looking at Nasal from a FlightGear-centric perspective, 
where there are plenty of functions available in Nasal that aren't listed here. 

That leads us to concept of **extension functions**, which are, simply put, a function that has been added to the language by FlightGear. Some of these are general purpose functions that should be back-ported to become builtins. Others however are of course extremely specific to FlightGear, for example, `findAirportsWithinRange()`.

The nasal builtin functions are implemented in `lib.c` and are denoted by an `f_` prefix, indicating they are implementations of builtin Nasal functions, as opposed to being some other function that belongs to the language internals.

| Nasal Built-in function | Arguments     | Description   |
|-------------------------|---------------|---------------|
| `size()`                |               |               |
| `keys()`                |               |               |
| `append()`              |               |               |
| `pop()`                 |               |               |
| `setsize()`             |               |               |
| `subvec()`              |               |               |
| `vecindex()`            |               |               |
| `remove()`              |               |               |
| `removeat()`            |               |               |
| `delete()`              |               |               |
| `int()`                 |               |               |
| `num()`                 |               |               |
| `str()`                 |               |               |
| `streq()`               |               |               |
| `cmp()`                 |               |               |
| `substr()`              |               |               |
| `left()`                |               |               |
| `right()`               |               |               |
| `chr()`                 |               |               |
| `contains()`            |               |               |
| `typeof()`              |               |               |
| `ghosttype()`           |               |               |
| `compile()`             |               |               |
| `call()`                |               |               |
| `die()`                 |               |               |
| `sprintf()`             |               |               |
| `caller()`              |               |               |
| `closure()`             |               |               |
| `find()`                |               |               |
| `split()`               |               |               |
| `rand()`                |               |               |
| `bind()`                |               |               |
| `sort()`                |               |               |
| `id()`                  |               |               |
| `isscalar()`            |               |               |
| `isint()`               |               |               |
| `isnum()`               |               |               |
| `isghost()`             |               |               |
| `isstr()`               |               |               |
| `isvec()`               |               |               |
| `ishash()`              |               |               |
| `isfunc()`              |               |               |
| `range()`               |               |               |

## Standard Library

### `math`

| Functions         |
|-------------------|
| `math.acos()`     |
| `math.asin()`     |
| `math.atan()`     |
| `math.atan2()`    |
| `math.ceil()`     |
| `math.clamp()`    |
| `math.cos()`      |
| `math.exp()`      |
| `math.floor()`    |
| `math.fmod()`     |
| `math.ln()`       |
| `math.periodic()` |
| `math.pow()`      |
| `math.round()`    |
| `math.sin()`      |
| `math.sqrt()`     |
| `math.trunc()`    |

**Note:** The standard math library is actually missing a math.abs() function. It has been added as an extension function in FlightGear, but the standard library should implement it.

| Constants |
|-----------|
| `math.pi` |
| `math.e`  |

## Language Internals

### Compiler

Nasal uses a **single-pass compiler** design. This keeps the implementation simple, and means compilation time is fast, with the trade-off of slower execution time.

### Garbage Collection

Nasal uses a **mark/sweep** garbage collector. This keeps things simple, but is problematic in real-time applications (like FlightGear) because garbage collection requires that all operations are stopped before recursively marking all reachable objects and free unreachable ones, in a single-threaded manner. [Source](https://wiki.flightgear.org/How_the_Nasal_GC_works#Problem)

A **generational garbage collector** has been identified as an important leap for Nasal.

### Bytecode VM

Nasal operates on a **stack-based** VM, as opposed to a **register-based** This design choice means that the language implementation has lower complexity, but is much less performant. Lua, for example, moved away from a stack-based virtual machine to a register-based virtual machine in Lua 5.0.

Nasal uses a bytecode VM that implements almost 60 opcodes.

#### Opcodes

| ID | Opcode       | Operands | Description          |
|----|--------------|----------|----------------------|
| 0  | OP_NOT       | 1        | Logical not operator (`!`)   |
| 1  | OP_MUL       | 2        | Multiplication operator (`*`)|
| 2  | OP_PLUS      | 2        | Addition operator (`+`)      |
| 3  | OP_MINUS     | 2        | Subtraction operator (`-`)   |
| 4  | OP_DIV       | 2        | Division operator (`/`)      |
| 5  | OP_NEG       | 1        | Negation operator (`-`)             |
| 6  | OP_CAT       | 2        | String concatenation operator (`~`) |
| 7  | OP_LT        | | |
| 8  | OP_LTE       | | |
| 9  | OP_GT        | | |
| 10 | OP_GTE       | | |
| 11 | OP_EQ        | | |
| 12 | OP_NEQ       | | |
| 13 | OP_EACH      | | |
| 14 | OP_JMP       | | |
| 15 | OP_JMPLOOP   | | |
| 16 | OP_JIFNOTPOP | | |
| 17 | OP_JIFEND    | | |
| 18 | OP_FCALL     | | |
| 19 | OP_MCALL     | | |
| 20 | OP_RETURN    | | |
| 21 | OP_PUSHCONST | | |
| 22 | OP_PUSHONE   | | |
| 23 | OP_PUSHZERO  | | |
| 23 | OP_PUSHNIL   | | |
| 25 | OP_POP       | | |
| 26 | OP_DUP       | | |
| 27 | OP_XCHG      | | |
| 28 | OP_INSERT    | | |
| 29 | OP_EXTRACT   | | |
| 30 | OP_MEMBER    | | |
| 31 | OP_SETMEMBER | | |
| 32 | OP_LOCAL     | | |
| 33 | OP_SETLOCAL  | | |
| 34 | OP_NEWVEC    | | |
| 35 | OP_VAPPEND   | | |
| 36 | OP_NEWHASH   | | |
| 37 | OP_HAPPEND   | | |
| 38 | OP_MARK      | | |
| 39 | OP_UNMARK    | | |
| 40 | OP_BREAK     | | |
| 41 | OP_SETSYM    | | |
| 42 | OP_DUP2      | | |
| 43 | OP_INDEX     | | |
| 44 | OP_BREAK2    | | |
| 45 | OP_PUSHEND   | | |
| 46 | OP_JIFTRUE   | | |
| 47 | OP_JIFNOT    | | |
| 48 | OP_FCALLH    | | |
| 49 | OP_MCALLH    | | |
| 50 | OP_XCHG2     | | |
| 51 | OP_UNPACK    | | |
| 52 | OP_SLICE     | | |
| 53 | OP_SLICE2    | | |
| 54 | OP_BIT_AND   | | |
| 55 | OP_BIT_OR    | | |
| 56 | OP_BIT_XOR   | | |
| 57 | OP_BIT_NE    | | | 