# not another scripting language

## Credits

Nasal is a programming language over 20 years in the making developed by Andy Ross and countless members of the FlightGear team. The original version can be found on GitHub [here](https://github.com/andyross/nasal). 


## About

This project is not official, nor is it endorsed by the authors of Nasal. It's goals are academic and experimental in nature, with the hope potentially furthering the betterment and proliferation of the Nasal language, but strictly _not_ to compete with it. Please don't eat me.


## Rationale

This is the Nasal scripting language from the FlightGear project, broken out into its own repo. 

The C++ bindings and Emesary have been removed as they are tightly coupled to SimGear, and this repo is intended as a stand-alone, project-agnostic, core language implementation. 
The reason this has been done is because I'd like to do some experiments with language interpreters, garbage collection, performance, etc. without the distraction of interplay with Boost and SimGear. 

The intention is not to break pre-existing Nasal code. Things under the hood might be changed significantly, but things at a surface-level should still work the same way. Hopefully just faster. 
The idea is that if any experiments done here turn out to provide some significant benefit to Nasal performance, FlightGear could choose to become a downstream consumer of this Nasal intrepreter by adding
this repository as a dependency via the CMake `FetchContent` feature, and linking against this Nasal. This would be done instead of merging back upstream into FlightGear, as the working belief here is to have Nasal
broken out into a separate repository/project.

Nasal doesn't really have a standard specification, like ECMAScript, or the C and C++ standards, nor does it have any documentation. It also lacks tooling like package management, documentation generation, linting, formatting, etc. Or really, any modern convenience adopted by
programming languages over the last ~15 years. Usually that would be a reason to stop dead in your tracks and turn the other way, however, it's also a perfect opportunity to experiment with developing that kind of tooling.

Lastly, I've also always wanted a good excuse to read [Crafting Interepreters by Robert Nystrom](https://craftinginterpreters.com/), so I may very well shoehorn knowledge from that book into the codebases see what happens.

**Basically, this is just a big science experiment.**


## Specification
You can view a work-in-progress (unofficial) Nasal specification [here](https://github.com/nasal-lang-community/specification). It's not adding or proposing anything new, just codifying the language as-is into a proper specification or standard as most languages tend to have.

## License

The Nasal language was released under the GNU GPLv2. Naturally, this repository, being a fork and a derivative of the original, follows suit.

