#include <iostream>
#include <string>
#include <numeric>
using namespace std;

// string str1 = "OBCNOOBCNOOBCNOOBCNOOBCNOOBCNOOBCNOOBCNO";

class Solution {
public:
    void smallestRepeatingSubstring(const string& str, string& repeatingPattern, int& numberOfRepititions) {
        repeatingPattern = string{str[0]};
        numberOfRepititions = 1;

        size_t positionInPattern = 0; // where we are in pattern
        bool tryingToCompletePattern = false;
        size_t tryingToCompletePatternStartingAt = 0;

        for (size_t i = 1; i < str.size(); ++i) {
            const char next_char = str[i];

            if (next_char == repeatingPattern[positionInPattern]) {
                // matching current pattern
                if (!tryingToCompletePattern) {
                    tryingToCompletePattern = true;
                    tryingToCompletePatternStartingAt = i; // mark where repetition began
                }

                positionInPattern++;

                // finished one repetition
                if (positionInPattern == repeatingPattern.size()) {
                    numberOfRepititions++;
                    positionInPattern = 0;
                }
            } else {
                // mismatch
                if (tryingToCompletePattern) {
                    // pattern was wrong, extend it
                    repeatingPattern += str[tryingToCompletePatternStartingAt];
                    tryingToCompletePattern = false;
                    numberOfRepititions = 1;
                    positionInPattern = 0;
                    i = tryingToCompletePatternStartingAt; // restart loop at mismatch start
                } else {
                    repeatingPattern += next_char; // still building initial pattern
                }
            }
        }

        // If we ended with an incomplete repetition, then the whole string is the pattern
        if (tryingToCompletePattern && (positionInPattern > 0)) {
            repeatingPattern = str;
            numberOfRepititions = 1;
        } else if (numberOfRepititions == 0) {
            // string did not repeat, pattern is whole string
            repeatingPattern = str;
            numberOfRepititions = 1;
        }
    }

    string gcdOfStrings(string str1, string str2) {
        string smallestRepeatingSubstr_str1;
        string smallestRepeatingSubstr_str2;
        int numRepitionsOfSmallestRepeatingSubstr_str1;
        int numRepitionsOfSmallestRepeatingSubstr_str2;

        smallestRepeatingSubstring(str1, smallestRepeatingSubstr_str1, numRepitionsOfSmallestRepeatingSubstr_str1);
        smallestRepeatingSubstring(str2, smallestRepeatingSubstr_str2, numRepitionsOfSmallestRepeatingSubstr_str2);
        
        if(smallestRepeatingSubstr_str1 == smallestRepeatingSubstr_str2){
            const size_t numRepitionsOfSmallestRepeatingSubstrInGCD = gcd(numRepitionsOfSmallestRepeatingSubstr_str1, numRepitionsOfSmallestRepeatingSubstr_str2);
            string gcdString{""};
            for (size_t i = 0; i < numRepitionsOfSmallestRepeatingSubstrInGCD; ++i){
                gcdString += smallestRepeatingSubstr_str1;
            }

            return gcdString;
        }
        return "";
    }
};

int main()
{
  Solution gcdSolver;
  string str1 = "OBCNOOBCNOOBCNOOBCNOOBCNOOBCNOOBCNOOBCNO";
  string str2 = "OBCNOOBCNOOBCNOOBCNOOBCNOOBCNOOBCNOOBCNOOBCNOOBCNOOBCNOOBCNOOBCNO";
  string gcdString = gcdSolver.gcdOfStrings(str1, str2);
  cout << gcdString << std::endl;
  return 0;   
}
