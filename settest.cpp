#include <iostream>
#include <set>
#include <string>
#include "util.h" // Make sure this includes the declaration for parseStringToWords

using namespace std;

int main() {

    string input1;
    string input2; 
    cout << "Give me a string of words." << endl;

    getline(cin, input1); // Corrected to read the entire line
    set<string> parsedInput1 = parseStringToWords(input1);

    cout << "Give me a a second string of words." << endl;
    getline(cin, input2); // Corrected to read the entire line
    set<string> parsedInput2 = parseStringToWords(input2);


    cout << "Printing parsed string of keywords for Input 1: " << endl;

    int idx = 1;
    for(set<string>::const_iterator it = parsedInput1.begin(); it != parsedInput1.end(); ++it) {
        cout << "Keyword " << idx << ": " << *it << endl;
        idx++;
    }

    cout << "Printing parsed string of keywords for Input 2: " << endl;

    idx = 1;
    for(set<string>::const_iterator it = parsedInput2.begin(); it != parsedInput2.end(); ++it) {
        cout << "Keyword " << idx << ": " << *it << endl;
        idx++;
    }

    set<string> intersection = setIntersection(parsedInput1, parsedInput2); 

    cout << "The set intersection is: " << endl; 
    
    idx = 1;
    for(set<string>::const_iterator it = intersection.begin(); it != intersection.end(); ++it) {
        cout << idx << ": " << *it << endl;
        idx++;
    }

    set<string> unionSet = setUnion(parsedInput1, parsedInput2); 
    cout << "The set union is: " << endl; 

    idx = 1;
    for(set<string>::const_iterator it = unionSet.begin(); it != unionSet.end(); ++it) {
        cout << idx << ": " << *it << endl;
        idx++;
    }

    return 0;
}