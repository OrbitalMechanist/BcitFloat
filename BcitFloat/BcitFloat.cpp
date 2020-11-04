// BcitFloat.cpp : Converts a BCIT 10-bit float to decimal. This is a one-file program.
//
// (c) Maksym Korchagov, 2020. Version 1. USE AT OWN RISK! Not guaranteed to work.

#include <iostream>
#include <string>

int BIAS = 7;

int digitToInt(char c) {
    return c - 48;
}

int main()
{   
    //input
    std::cout << "INPUT BCIT FLOAT\n";
    std::string inString;
    std::cin >> inString;
    if (inString.length() != 10) {
        std::cout << "INCORRECT INPUT" << std::endl;
        std::cout << "INCORRECT LENGTH" << std::endl;
        system("pause"); //get rid of these and replace them with some other stopper if you want to use it on non-Windows systems.
        quick_exit(1);
    }
    for (size_t i = 0; i < 10; i++)
    {
        if (inString[i] != '1' && inString[i] != '0') {
            std::cout << "INCORRECT INPUT" << std::endl;
            std::cout << "UNACCEPTABLE CHARACTER " << inString[i] << std::endl;
            system("pause");
            quick_exit(2);
        }
    }

    //processing starts here
    int exp = 0;
    float mant = 0;
    float result = 0;
    
    //calculate exponent and mantissa
    exp = digitToInt(inString[1]) * 8 + digitToInt(inString[2]) * 4 + digitToInt(inString[3]) * 2 + digitToInt(inString[4]) - BIAS;
    std::cout << "Exponent: " << exp << std::endl;

    mant = (float)digitToInt(inString[5]) / 2 + (float)digitToInt(inString[6]) / 4 + (float)digitToInt(inString[7]) / 8 
        + (float)digitToInt(inString[8]) / 16 + (float)digitToInt(inString[9]) / 32;
    std::cout << "Mantissa: " << mant << std::endl;

    //Do the conversion!
    if (exp == 8 && mant == 0) { //Special: infinity
        std::cout << ((inString[0] == '1') ? "Negative " : "") << "Infinity" << std::endl;
    }
    else if (exp == 8) { //Special: NaN
        std::cout << "Not A Number (NaN)" << std::endl;
    }
    else if (exp == -7 && mant == 0) { //Special: 0
        std::cout << ((inString[0] == '1') ? "-" : "") << "0" << std::endl;
    }
    else if (exp == -7) { //Special: unnormalized
        result = mant * pow(2, -6) * (float)((inString[0] == '1') ? -1 : 1);
        std::cout << result << std::endl;
    }
    else { //Standard
        result = ((mant + (float)1) * pow(2, exp)) * (float)((inString[0] == '1') ? -1 : 1);
        std::cout << result << std::endl;
    }
    system("pause");
}