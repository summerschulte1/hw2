#include <iostream>
#include <set>
#include <string>
#include "util.h" // Make sure this includes the declaration for parseStringToWords

using namespace std;

int main() {
    cout << "Give me a string of words." << endl;

    string input;
    getline(cin, input); // Corrected to read the entire line

    set<string> parsedInput = parseStringToWords(input);

    cout << "Printing parsed string of keywords: " << endl;

    int idx = 1;
    for(set<string>::const_iterator it = parsedInput.begin(); it != parsedInput.end(); ++it) {
        cout << "Keyword " << idx << ": " << *it << endl;
        idx++;
    }

    return 0;
}
