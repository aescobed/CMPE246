#include <iostream>
#include <string>

// Function to explain the structure of a C++ function
void explainFunctionStructure() {
    std::cout << "In C++, a function typically consists of the following parts:\n\n";
    std::cout << "1. Return Type: Specifies the type of value the function returns.\n";
    std::cout << "2. Function Name: A unique name to identify the function.\n";
    std::cout << "3. Parameters: A list of inputs the function can take (optional).\n";
    std::cout << "4. Function Body: The block of code that performs the task.\n\n";
    std::cout << "Example:\n";
    std::cout << "int add(int a, int b) {\n    return a + b;\n}\n\n";
    std::cout << "In this example:\n";
    std::cout << "- The return type is 'int'.\n";
    std::cout << "- The function name is 'add'.\n";
    std::cout << "- The parameters are 'int a' and 'int b'.\n";
    std::cout << "- The function body contains 'return a + b;'.\n\n";
}

// Function to demonstrate basic programming concepts
void demonstrateBasicConcepts() {
    std::cout << "Basic Programming Concepts:\n\n";

    // Variables
    int a = 5;
    double b = 3.14;
    std::string c = "Hello, World!";
    std::cout << "1. Variables:\n";
    std::cout << "- int a = " << a << ";\n";
    std::cout << "- double b = " << b << ";\n";
    std::cout << "- std::string c = \"" << c << "\";\n\n";

    // Conditional Statements
    std::cout << "2. Conditional Statements:\n";
    if (a > 3) {
        std::cout << "- a is greater than 3\n";
    } else {
        std::cout << "- a is not greater than 3\n";
    }
    std::cout << "\n";

    // Loops
    std::cout << "3. Loops:\n";
    std::cout << "- For Loop: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n\n";

    // Functions
    std::cout << "4. Functions:\n";
    std::cout << "- Functions help break code into reusable blocks.\n";
    std::cout << "- Example: The function 'add' adds two numbers.\n";
}

// Example function: Add two numbers
int add(int a, int b) {
    return a + b;
}

int main() {
    std::cout << "Welcome to the C++ Tutorial Program!\n\n";

    // Demonstrate basic programming concepts
    demonstrateBasicConcepts();
  
    // Explain the structure of a function
    explainFunctionStructure();

    // Demonstrate a simple function call
    int result = add(2, 3);
    std::cout << "\nExample Function Call:\n";
    std::cout << "The result of add(2, 3) is: " << result << "\n";

    return 0;
}
