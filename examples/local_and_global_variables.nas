# Variable 'a' is a global variable because it is not declared inside a function or code block.
a = 1; 

# Variable 'b' is a global variable because although it is declared inside a function, it is missing the 'var' keyword.
OtherFunc = func() {
  b = 3; 
}

# Variable 'c' is a local variable because it is defined in a function/code block *and* uses the 'var' keyword.

Func = func() {
  var c = 4;
}

# Because 'c' is a local variable, we can not access it from outside the function/code block it was defined in.
# If you uncomment the line below, Nasal will produce a runtime error:

# print(c)

# Variable 'd' is a global variable. While it does have the 'var' keyword, it does not have any effect on the variables scope
# because the variable is still declared outside of a function or code block.

var d = 2; 