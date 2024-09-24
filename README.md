# not another scripting language

## Credits

Nasal is a programming language over 20 years in the making developed by Andy Ross and countless members of the FlightGear team. The original version can be found on GitHub [here](https://github.com/andyross/nasal). 


## About

This project is not official, nor is it endorsed by the authors of Nasal. It's goals are academic and experimental in nature, with the hope potentially furthering the betterment and proliferation of the Nasal language, but strictly _not_ to compete with it. Please don't eat me.


## Rationale

This is the Nasal scripting language from the FlightGear project, broken out into its own repo. 

The C++ bindings and Emesary have been removed as they are tightly coupled to SimGear, and this repo is intended as a stand-alone, project-agnostic, core language implementation. 
The reason this has been done is because I'd like to do some experiments with language interpreters, garbage collection, performance, etc. without the distraction of interplay with Boost and SimGear. 

## Goals

The intention is not to break pre-existing Nasal code. Things under the hood might be changed significantly, but things at a surface-level should still work the same way. Hopefully just faster. 
The idea is that if any experiments done here turn out to provide some significant benefit to Nasal performance, FlightGear could choose to become a downstream consumer of this Nasal intrepreter by adding
this repository as a dependency via the CMake `FetchContent` feature, and linking against this Nasal. This would be done instead of merging back upstream into FlightGear, as the working belief here is to have Nasal
broken out into a separate repository/project.


Lastly, I've also always wanted a good excuse to read [Crafting Interepreters by Robert Nystrom](https://craftinginterpreters.com/), so I may very well shoehorn knowledge from that book into the codebases see what happens.

**Basically, this is just a big science experiment.**

## Special areas of interest

### Formalized specification, test cases, standardization, etc.

Nasal doesn't really have a standard specification, like ECMAScript, or the C and C++ standards. It has some example code, but it lacks any kind of unit testing.

Pretty much any improvement we would want to make to Nasal would require an accurate baseline to work off of, so one of the first priorities should be rigorously testing
and benchmarking the current implementation.

### Documentation and exploration of Nasal internals

I think the internals of Nasal are only particularly well understood by a very small group of people, probably in the single digits - those who have gone to the trouble of gaining a knowledge of its inner workings
through experience. Documentation on how the internals of the language work would be very beneficial for knowledge sharing, educational purposes, and getting new developers up to speed.

### Fuzzing
A cursory attempt at fuzzing the Nasal interpreter has revealed a significant number of segfaults, stack overflows, etc. Right now you can't throw a stone without causing a segfault the moment you walk off the beaten path
of overtly valid Nasal code. This poses significant problems both in terms of security as well as general correctness. It is no challenge (right now) to trigger one of these critical bugs, it can however be extremely challenging to 
identify the root cause and fix them.

### Performance improvements

There is another (albeit incompatible) [implementation of Nasal](https://github.com/ValKmjolnir/Nasal-Interpreter) that, upon some cursory benchmarking, was as much as 80% faster than the original Nasal implementation. This is a major indication that there are massive performance gains to be realized.

Hypothesized areas of improvement pertaining to performance include:
- Nasal has a stack-based virtual machine. This has the benefit of keeping the compiler implementation simple, but is reportedly slower than a register-based virtual machine. Lua made such a migration in 5.0. This would be a very lofty goal.
- Nasal uses a single-threaded mark/sweep garbage collection system. This is problematic in real-time applications, as it essentially brings things to a halt when its time to take out the trash. 
  Migrating to generational garbage collection would be a step-up. Supporting multi-threading and migrating to _concurrent_ garbage collection would be a major leap.
- Nasal appears to push variables as strings onto the stack, which seemingly comes at a significant cost to performance. Implementing symbol encoding or hash-based lookups may improve performance.



### Modern ecosystem ammenities:

Nasal lacks the modern convenience adopted by programming languages over the last ~15 years: 
  - Package management
  - Documentation of the language and API
  - Documentation generation
  - Linting and formatting tools

### Misc.

- A `const` type would be nice.
  
Usually a lack of these ammenities would be a reason to stop dead in your tracks and turn the other way, however, it's also a perfect opportunity to experiment with developing that kind of tooling.

## Specification
You can view a work-in-progress (unofficial) Nasal specification [here](https://github.com/nasal-lang-community/specification). It's not adding or proposing anything new, just codifying the language as-is into a proper specification or standard as most languages tend to have.

## License

The Nasal language was released under the GNU GPLv2. Naturally, this repository, being a fork and a derivative of the original, follows suit.
