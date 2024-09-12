
# The Nasal language specification
Despite existing for over 20 years, there is no official Nasal specification. Here's a crack at one.

- [Syntax and Conventions](#syntax-and-conventions)
  - [Semicolons](#semicolons)
    - [Automatic Semicolon Insertion](#automatic-semicolon-insertion)
  - [Parentheses and Function Declarations](#parentheses-and-function-declarations)
- [Keywords](#keywords)
  - [Variable Declaration](#variable-declaration)
  - [Function Declaration](#function-declaration)
  - [Conditional Control Flow Keywords](#conditional-control-flow-keywords)
  - [Iterative Control Flow Keywords](#iterative-control-flow-keywords)
  - [Control Flow Keywords](#control-flow-keywords)
  - [Boolean Literals](#boolean-literals)
  - [Null Value](#null-value)
- [Variables and Scope](#variables-and-scope)
  - [Global and Local Scope](#global-and-local-scope)
  - [Lexical Scoping](#lexical-scoping)
  - [Closures](#closures)
  - [Variable Shadowing](#variable-shadowing)
  - [Function Parameters](#function-parameters)
  - [Best Practices](#best-practices-for-variables-and-scope)
- [Types](#types)
  - [Mutability](#mutability)
  - [Primitives](#primitives)
    - [Null](#null)
    - [Boolean](#boolean)
    - [Integer](#integer)
    - [String](#string)
  - [Containers](#containers)
    - [Vector](#vector)
    - [Hash](#hash)
- [Functions](#functions)
  - [Functions as first-class citizens](#functions-as-first-class-citizens)
- [Ghosts](#ghosts)
- [Built-in functions](#builtin-functions)
- [Standard Library](#standard-library)
  - [Math](#math)
- [Language Internals](#language-internals)
  - [Bytecode VM](#bytecode-vm)
    - [Opcodes](#opcodes)


## Syntax and Conventions

### Semicolons

Nasal, taking syntax cues from C, C++, and JavaScript, is a "semicolon language". That means that **statements must be terminated with a semicolon** in order to tell Nasal the statement has ended. There is an exception to this rule however. In JavaScript (which shares this similiarity), it is known as **automatic semicolon insertion** (ASI), so that's what we will call it here as well. 

#### Automatic Semicolon Insertion 

Nasal, like JavaScript, has a concept of ASI. This essentialy boils down to the fact that **semicolons can be omitted in the last line of a code block**. The rationale is that semicolons are used to terminate statements, but if the statement appears at the end of a block of code, it is implicitly known that it is already the last statement, and so no semicolon is necessary to tell Nasal where the statement terminates.

```
# Normally, statements must be terminated with a semicolon.
var x = 1;

foo = func(y) {
    # Another normal statement, so a semi-colon is required
    y = x + 1;

    # At the end a code block, the last line is seen as an implict end of a statement,
    # so there are no complaints if a semicolon is ommitted.
    return y 
}

var z = foo(x); # Another normal statement, no semi-colon required.

# The last line in the "main" block. Again this line is seen implicitly as the end of a statement,
# and no semicolon is required.
print("The value of z is " ~ z ~ "\n")
```

If we run this code, we will see that despite the lack of semicolons at the end of statement blocks, there are no parsing errors, and the code functions as expected with the output:

```
The value of z is 2
```

### Parenthesis and Function Declarations

If a function takes no parameters, the parentheses may be omitted in a function declaration. 

```
# This function takes no arguments, so the parentheses "()" can be omitted from the function declaration:
functionWithoutArguments = func {
    print("This function has takes no arguments!", "\n");
    return;
}

# This function takes an argument, so it must have parentheses in the function declaration:
functionWithArguments = func(x) {
    print("This function takes an argument of x: ", x, "\n");
    return x;
}

functionWithoutArguments();
functionWithArguments(1);
```

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

## Variables and Scope

Like many programming languages, Nasal has a concept of scope. And like many languages, in Nasal there are two kinds of scope - **global scope**, and **local scope**. Variables under these two scopes are known as **global variables** and **local variables** respectively.

> **Tip:** If you're familiar with how scoping works in Lua, it is roughly similar in Nasal except the differences boil down to the use (or lack of use) of keywords.

## Global and Local Scope

> **Tip:** Nasal does not use a `global` or`local` keyword to describe what scope a variable has. Variables are scoped based on the use of the `var` keyword _and_ (crucially) contexual factors, like where the variable is defined.

The default behavior in Nasal is vaguely similar to Lua, meaning that in most cases, variables will be **globally scoped**, _unless_ you actively do something to make them locally scoped instead.

A variable in Nasal _will_ be globally scoped if any of the following conditions are met:
- The variable is declared _outside_ of a code block or function.
- The variable is declared _inside_ a code block or function, but is missing the `var` keyword.

>**Note:** Any variable defined outside a function or code block is a global variable, even if it uses the `var` keyword!

Likely the easiest way to understand this is by demonstration. Here is the `local_and_global_scopes.nas` example from the `examples/` directory:

```
# Variable 'a' is a global variable because it is not declared inside a function or code block.
a = 1; 

# Variable 'b' is a global variable because although it is declared inside a function, it is missing the 'var' keyword.
OtherFunc = func() {
  b = 3; 
}

# Variable 'c' is a local variable because it is defined in a function/code block *and* uses the 'var' keyword.

Func = func() {
  var c = 4;
}

# Because 'c' is a local variable, we can not access it from outside the function/code block it was defined in.
# If you uncomment the line below, Nasal will produce a runtime error:

# print(c)

# Variable 'd' is a global variable. While it does have the 'var' keyword, it does not have any effect on the variables scope
# because the variable is still declared outside of a function or code block.

var d = 2; 
```

### Lexical Scoping

Nasal uses lexical scoping (also known as static scoping) to resolve variable names based on the structure of the program code, rather than when or where functions are executed. With lexical scoping, a variable’s scope is determined at the time the function or block is defined, not at runtime.

When Nasal encounters a variable reference, it starts searching for the variable in the current scope (inside the function or block where the reference is made). If the variable is not found there, Nasal continues searching in the surrounding (outer) scope where the function or block was defined, and this search continues outward until the global scope is reached.

```
globalVar = 10;

outer = func {
    var outerVar = 20;

    inner = func {
        var innerVar = 30;
        print(globalVar);  # Accesses globalVar from global scope
        print(outerVar);   # Accesses outerVar from outer function scope
        print(innerVar);   # Accesses innerVar from local scope
    };

    inner();  # Executes inner function within the same outer function call
};

outer();
```

#### Lexical Scoping and Nested Functions

As demonstrated above, functions in Nasal can be defined within other functions. Lexical scoping ensures that a nested function has access to variables from its surrounding (outer) function, even after the outer function has finished executing. This behavior allows for the creation of **closures**, where an inner function can "remember" and use the variables from its outer scope.

### Closures

A closure is created when an inner function captures variables from its enclosing scope, retaining access to those variables even after the outer function has finished executing. This allows the inner function to "remember" the environment in which it was created.

Here is the `closures.nas` example from the `examples/` directory:

```
outer = func {
    var x = 5;

    return func {
        return x;  # 'x' is captured from the outer scope
    };
};

closureFunc = outer();  # 'outer' function returns an inner function
print(closureFunc());  # Prints 5, even though 'outer' has finished
```
In this example:

- The outer function defines a variable `x` and returns an inner function that references `x`.
- Even though `outer()` has finished executing, the inner function returned by `outer()` retains access to `x` due to the closure.
- When `closureFunc()` is called, it still has access to `x` and returns its value, even though `x` was defined in a scope that has already exited.

#### The difference between Lexical Scoping and Closures
- Lexical Scoping ensures that variables are resolved based on where they are defined, not where the function is called. In the lexical scoping example, variables are only accessible while the outer function is still active.
- Closures extend this concept by allowing inner functions to retain access to variables from their enclosing scope, even after the outer function has finished executing.

### Variable Shadowing

### Function Parameters

### Best Practices for Variables and Scope

- Strongly avoid the use of global variables. That means declaring as many variables with `var` as possible. If it is at all possible to replace a global variable with a local one, 9 times out of 10, that is the better solution. [⁽¹⁾](https://web.archive.org/web/20240905153735/https://www.forrestthewoods.com/blog/global-variables-are-evil-and-unsafe/) [⁽²⁾](https://web.archive.org/web/20240303085335/https://www.codewithjason.com/global-variables/)


## Types

### Mutability

Everything in Nasal is mutable. There is no `const` keyword, and no immutable data types.

### Primitives

#### Null 

Nasal has a null type, represented with the keyword `nil`. This is analagous to `null`, or `None` in other programming languages.

#### Boolean

Nasal has boolean values 

#### Integer

#### String

As with all types, strings are **mutable** in Nasal, this includes strings, which can be concatenated using the string concatenation operator (`~`).


Here is an excerpt from `examples/string_mutability_and_concatenation.nas`:
```
var myString = "Hello";

# Reassignment
myString = myString ~ " world!\n";

# Will output "Hello world!"
print(myString);
```

### Containers

#### Vector

#### Hash

## Functions

### Functions as first-class citizens

In Nasal, functions are referred to as 'first-class citizens'. This term is widely used in programming to convey the fact that functions are treated the same way as any other variable in a programming language. 

That means you can:
- Assign functions to variables
- Pass functions as arguments to other functions
- Return functions from other functions
- Store functions in data structures like vectors or hashes

This is as opposed to a language like C, where it is possible to do some of these things, but not in the same way. 

The ability to treat functions like any other data (assigning them to variables, passing them around, etc.) is a fundamental feature of functional programming and is commonly seen in languages that support higher-order functions.

## Ghosts

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
