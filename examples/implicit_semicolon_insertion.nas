# This example demonstrates the "implicit semicolon insertion" behavior in Nasal

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