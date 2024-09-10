# not another scripting language


## Rationale

This is the Nasal scripting language from the FlightGear project, broken out into its own repo. 

The C++ bindings and Emesary have been removed as they are tightly coupled to SimGear, and this repo is intended as a stand-alone, project-agnostic, core language implementation. 
The reason this has been done is because I'd like to do some experiments with language interpreters, garbage collection, performance, etc. without the distraction of interplay with Boost and SimGear. 

The intention is not to break pre-existing Nasal code. Things under the hood might be changed significantly, but things at a surface-level should still work the same way. Hopefully just faster. 
The idea is that if any experiments done here turn out to provide some significant benefit to Nasal performance, it could be re-integrated upstream into FlightGear without major modification on either end.

Nasal also doesn't really have a standard specification, like ECMAScript, or the C and C++ standards, nor does it have any documentation. It also lacks tooling like package management, documentation generation, linting, formatting, etc. Or really, any modern convenience adopted by
programming languages over the last ~15 years. Usually that would be a reason to stop dead in your tracks and turn the other way, however, it's also a perfect opportunity to experiment with developing that kind of tooling.

Lastly, I've also always wanted a good excuse to read [Crafting Interepreters by Robert Nystrom](https://craftinginterpreters.com/), so I may very well shoehorn knowledge from that book into the codebases see what happens.

Basically this is a big science experiment.


## The Nasal language

### Builtin functions
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

