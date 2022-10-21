#include "RunCaesarCipher.hpp"
#include <string>
#include <vector>
#include <algorithm>

std::string runCaesarCipher(const std::string& inputText, const size_t key, const bool encrypt) {
    const std::vector<char> alphabet {
        'A', 'B', 'C', 'D', 
        'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X',
        'Y', 'Z'
    };
    const size_t lenAlphabet {alphabet.size()};
    std::string newText {""};

    for (const char& el : inputText) {
        auto it = std::find(alphabet.begin(), alphabet.end(), el);
        if (it != alphabet.end()) {
            const int index = it - alphabet.begin();
            if (encrypt) {
                newText += alphabet[(index + key) % lenAlphabet];
            } else {
                const int tempKey {static_cast<int>(key)};
                int newIndex {0};
                if (index - tempKey < 0) {
                    newIndex = (index - tempKey);
                    // We could use a shift >= 2 * 26 
                    while (newIndex < 0) {
                        // Keep adding to get back to our happy place
                        newIndex += 26;
                    }
                } else {
                    newIndex = (index - tempKey) % lenAlphabet;
                }
                newText += alphabet[newIndex];
            }
        }
    }
    return newText;
}