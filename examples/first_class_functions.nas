myFunc = func {
    print("I don't take any arguments", "\n")
}

# If we use reference a function without its parentheses, and our statement contains no other expression, nothing happens.
# To be honest, this statement all by itself should probably be a runtime error.

myFunc; # Nothing happens, this isn't the same as function call, as the parentheses are missing.

# However, if we want to assign a variable to our function, we can reference the function name without parentheses.
x = myFunc;

# This calls myFunc():
x(); 
 
# We are even able to pass arguments to myFunc() for some reason, even though it doesn't accept them, and they are ignored.
x(2);


myFuncWithArguments = func(a) {
    return a + 1;
}

# What if we try to assign a variable to a function but don't include the parentheses, even though the function takes arguments?
y = myFuncWithArguments;

# We just simply pass the function arguments in the function call y().
y(3);

# Ok, well what if we did pass arguments to myFuncWithArguments() when we assigned a variable to it?
z = myFuncWithArguments(4);

# Well, we've come full circle and that's just a regular assignment. 'z' is an integer, with a value of 4. 
print(z, "\n");

# And if we try to assign z to another function, one that has no return type:
z = myFunc;
z();

# If we try to call z again with a new parameter, we will get a runtime error. Uncomment to try it out. 
#z(3);