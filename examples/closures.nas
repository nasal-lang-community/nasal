# This example demonstrates how Closures work in Nasal. 
# For more information, read the section on Closures in the Nasal documentation.

outer = func {
    var x = 5;

    return func {
        return x;  # 'x' is captured from the outer scope
    };
};

closureFunc = outer();  # 'outer' function returns an inner function
print(closureFunc(), "\n");  # Prints 5, even though 'outer' has finished