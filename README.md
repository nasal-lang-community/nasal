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

Nasal doesn't really have a standard specification, like ECMAScript, or the C and C++ standards, nor does it have any documentation. It also lacks tooling like package management, documentation generation, linting, formatting, etc. Or really, any modern convenience adopted by
programming languages over the last ~15 years. Usually that would be a reason to stop dead in your tracks and turn the other way, however, it's also a perfect opportunity to experiment with developing that kind of tooling.

Lastly, I've also always wanted a good excuse to read [Crafting Interepreters by Robert Nystrom](https://craftinginterpreters.com/), so I may very well shoehorn knowledge from that book into the codebases see what happens.

Basically this is a big science experiment.

## Special areas of interest
Also suitably catalogued under "extremely lofty goals", there are some big-ticket items Nasal falls short in that would be incredible to solve: 

- Migrating to generational garbage collection would be a step-up. Supporting multi-threading and migrating to _concurrent_ garbage collection would be a major leap.
- Migrate from a stack-based virtual machine to a register-based virtual machine.

I don't forsee any progress being made on those fronts however, as they are lofty.

## Specification
You can view a work-in-progress [Nasal specification](SPECIFICATION.md) here. It's not adding or proposing anything new, just codifying the language as-is into a proper specification or standard as most languages tend to have.
