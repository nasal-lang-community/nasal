# This example demonstrates two things:
# 1. Strings are mutable. There value can be changed after the initial assignment.
# 2. Strings can be concatenated together using the string concatenation (~) operator.

# For more information, read the unofficial Nasal specification: https://github.com/nasal-lang-community/specification

var myString = "Hello";

# Reassignment
myString = myString ~ " world!\n";

# Will output "Hello world!"
print(myString);
