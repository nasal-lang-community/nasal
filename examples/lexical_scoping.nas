# This example demonstrates how Lexical Scoping works in Nasal. 
# For more information, read the section on Lexical Scoping in the unofficial Nasal specification: https://github.com/nasal-lang-community/nasal-grammar
 
globalVar = 10;

outer = func {
    var outerVar = 20;

    inner = func {
        var innerVar = 30;
        print(globalVar, "\n");  # Accesses globalVar from global scope
        print(outerVar, "\n");   # Accesses outerVar from outer function scope
        print(innerVar, "\n");   # Accesses innerVar from local scope
    };

    inner();  # Executes inner function within the same outer function call
};

outer();
