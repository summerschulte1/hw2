#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  //split at puncutation and return the substrings?
  //sub strings only count if they are at least 2 characters 
  //do we need to trim the words??
  std::set<std::string> keywords;
  std::string currword;
	rawWords = convToLower(rawWords);
  for (char c: rawWords) {//iterate through rawWords
    //check each char to make sure its a letter and not a 
    //punctuation or space 

    if (!std::ispunct(c) && !std::isspace(c)) { //should i use ispunc()?
      //if its a valid char, add to the current word
      currword += c;
    }
    else { //its a punct or a white space
    //add chars to new word
    //once we hit here, we add the currword to keywords if its valid
     
        if (currword.length() >= 2) {
          keywords.insert(currword);
        }
        currword.clear();
    }
  }
  //handle the last word thats still in currword
  if (currword.length() >= 2) {
    keywords.insert(currword);
  }
  return keywords;


}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
