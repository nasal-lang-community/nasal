# not another scripting language


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

Basically this is a big science experiment.

## Special areas of interest

### Misc.

- A `const` type would be nice.

### Specification

Nasal doesn't really have a standard specification, like ECMAScript, or the C and C++ standards, nor does it have any documentation. 

### Modern ecosystem ammenities:

Nasal lacks the modern convenience adopted by programming languages over the last ~15 years: 
  - Package management
  - Documentation of the language and API
  - Documentation generation
  - Linting and formatting tools
  
Usually a lack of these ammenities would be a reason to stop dead in your tracks and turn the other way, however, it's also a perfect opportunity to experiment with developing that kind of tooling.

### Garbage Collection

Nasal uses a single-threaded mark/sweep garbage collection system. This is problematic in real-time applications, as it essentially brings things to a halt when its time to take out the trash. 

Migrating to generational garbage collection would be a step-up. Supporting multi-threading and migrating to _concurrent_ garbage collection would be a major leap.

**This is a big, lofty goal.**

### Register vs. Stack-based Virtual Machine

Nasal has a stack-based virtual machine. This has the benefit of keeping the compiler implementation simple, but is reportedly slower than a register-based virtual machine. Lua made such a migration in 5.0.

**This is also a big, lofty goal.**

## Specification
You can view a work-in-progress [Nasal specification](docs/SPECIFICATION.md) here. It's not adding or proposing anything new, just codifying the language as-is into a proper specification or standard as most languages tend to have.
