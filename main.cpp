#include <iostream>
#include <sstream>
#include "lexer.h"
#include "parser.h"

int main() {
    std::ostringstream oss;
    oss << std::cin.rdbuf(); 

    try {
        std::istringstream ss(oss.str());
        Lexer lexer(ss);
        Parser parser(lexer);

        double result = parser.parseAndEval();
        std::cout << "Result = " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
    }

    return 0;
}

//.\lab5.exe
//output
//^Z для конца ввода