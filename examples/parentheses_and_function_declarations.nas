# This example demonstrates how parentheses work with function declarations in Nasal.
# For more information, read the section on "Parentheses and Function Declaraionts" in the unofficial Nasal specification: https://github.com/nasal-lang-community/specification

# This function takes no arguments, so the parentheses "()" can be omitted from the function declaration:
functionWithoutArguments = func {
    print("This function has takes no arguments!", "\n");
    return;
}

# This function takes an argument, so it must have parentheses in the function declaration:
functionWithArguments = func(x) {
    print("This function takes an argument of x: ", x, "\n");
    return x;
}

functionWithoutArguments();
functionWithArguments(1);
