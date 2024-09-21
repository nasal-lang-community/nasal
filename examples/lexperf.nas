# A large number of variable assignments to test identifiers
var a1 = 1;
var a2 = 2;
var a3 = "test";
var a4 = 3.1415;

# Stressing numbers and strings
var str1 = "This is a very long string literal that should test the lexer's ability to handle large strings.";
var str2 = "Another string with escape characters: \n \t \\ \" ";
var num1 = 1234567890;
var num2 = -9876543210.12345;

# Function definitions with deep nesting
var complexFunction = func {
    var innerFunc1 = func {
        var x = 10;
        return x + 1;
    };
    var innerFunc2 = func {
        var y = 20;
        return y * 2;
    };
    return innerFunc1() + innerFunc2();
};

# Loop constructs
for (var i = 0; i < 10000; i += 1) {
    var j = i * 2;
    # Stressing comments and complex expressions
    # Nested expressions
    var result = (i + j) * (i - j) / (j != 0 ? j : 1);
}

# Multiple conditional statements
if (a1 == 1 and a2 < 3 or a3 != "error") {
    print("Conditions met!");
} else if (a4 >= 3.1415) {
    print("Pi condition met!");
}

# Large number of function calls with mixed operators and spacing
for (var k = 0; k < 1000; k += 1) {
    var temp = complexFunction() + k * (k - 1) + (k != 0 ? 1 / k : 0);
}

# Deeply nested loops and conditions
for (var m = 0; m < 500; m += 1) {
    for (var n = 0; n < 100; n += 1) {
        # Using math.fmod instead of % for modulus
        if (math.fmod(m * n, 2) == 0) {
            var temp2 = (m * n) / (m + n + 1);
            print("Nested loop iteration: ", m, n, temp2);
        }
    }
}