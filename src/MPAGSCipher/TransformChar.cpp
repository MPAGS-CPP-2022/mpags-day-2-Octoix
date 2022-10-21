#include "TransformChar.hpp"

#include <cctype>
#include <string>

std::string transformChar(const char inChar) {
    // Uppercase alphabetic characters
    std::string returnText {""};
    if (std::isalpha(inChar)) {
        returnText += std::toupper(inChar);
    }

    // Transliterate digits to English words
    switch (inChar) {
        case '0':
            returnText += "ZERO";
            break;
        case '1':
            returnText += "ONE";
            break;
        case '2':
            returnText += "TWO";
            break;
        case '3':
            returnText += "THREE";
            break;
        case '4':
            returnText += "FOUR";
            break;
        case '5':
            returnText += "FIVE";
            break;
        case '6':
            returnText += "SIX";
            break;
        case '7':
            returnText += "SEVEN";
            break;
        case '8':
            returnText += "EIGHT";
            break;
        case '9':
            returnText += "NINE";
            break;
    }
    return returnText;
    // If the character isn't alphabetic or numeric, DONT add it
    // essentially this does add something but it is just empty so it adds nothing
}