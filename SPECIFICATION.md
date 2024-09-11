
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

| Nasal Built-in function | Description   |
| ----------------------- | ------------- |
| `size()`                |               |
| `keys()`                |               |
| `append()`              |               |
| `pop()`                 |               |
| `setsize()`             |               |
| `subvec()`              |               |
| `vecindex()`            |               |
| `remove()`              |               |
| `removeat()`            |               |
| `delete()`              |               |
| `int()`                 |               |
| `num()`                 |               |
| `str()`                 |               |
| `streq()`               |               |
| `cmp()`                 |               |
| `substr()`              |               |
| `left()`                |               |
| `right()`               |               |
| `chr()`                 |               |
| `contains()`            |               |
| `typeof()`              |               |
| `ghosttype()`           |               |
| `compile()`             |               |
| `call()`                |               |
| `die()`                 |               |
| `sprintf()`             |               |
| `caller()`              |               |
| `closure()`             |               |
| `find()`                |               |
| `split()`               |               |
| `rand()`                |               |
| `bind()`                |               |
| `sort()`                |               |
| `id()`                  |               |
| `isscalar()`            |               |
| `isint()`               |               |
| `isnum()`               |               |
| `isghost()`             |               |
| `isstr()`               |               |
| `isvec()`               |               |
| `ishash()`              |               |
| `isfunc()`              |               |
| `range()`               |               |

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
