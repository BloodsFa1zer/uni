#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, int> wordToNumber = {
        {"Zero", 0}, {"One", 1}, {"Two", 2}, {"Three", 3}, {"Four", 4},
        {"Five", 5}, {"Six", 6}, {"Seven", 7}, {"Eight", 8}, {"Nine", 9},
        {"Ten", 10}, {"Eleven", 11}, {"Twelve", 12}, {"Thirteen", 13},
        {"Fourteen", 14}, {"Fifteen", 15}, {"Sixteen", 16}, {"Seventeen", 17},
        {"Eighteen", 18}, {"Nineteen", 19},
        {"Twenty", 20}, {"Thirty", 30}, {"Forty", 40}, {"Fifty", 50},
        {"Sixty", 60}, {"Seventy", 70}, {"Eighty", 80}, {"Ninety", 90},
        {"Hundred", 100},

        {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
        {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
        {"ten", 10}, {"eleven", 11}, {"twelve", 12}, {"thirteen", 13},
        {"fourteen", 14}, {"fifteen", 15}, {"sixteen", 16}, {"seventeen", 17},
        {"eighteen", 18}, {"nineteen", 19},
        {"twenty", 20}, {"thirty", 30}, {"forty", 40}, {"fifty", 50},
        {"sixty", 60}, {"seventy", 70}, {"eighty", 80}, {"ninety", 90},
        {"hundred", 100},
};

string processText(const string& txt) {
    string text = txt;
    replace(text.begin(), text.end(), '-', ' ');

    size_t pos = text.find("and");

    // While "and " is found, replace it with a space
    while (pos != string::npos) {
        text.replace(pos, 4, "");  // 4 is the length of "and "
        pos = text.find("and");
    }

    return text;
}

string convertWordsToNumber(const string& txt) {
    int currentNumber = 0;
    istringstream iss(processText(txt));
    vector<string> words;
    string word;
    ostringstream result;
    vector<int> numbers;
    bool isNumberEnds = false;

    while (iss >> word) {
        if (wordToNumber.find(word) != wordToNumber.end()) {
            int value = wordToNumber[word];

            if (value == 100) {
                currentNumber *= value;
            } else {
                currentNumber += value;
            }
            isNumberEnds = false;
        } else {
            isNumberEnds = true;
            result << word << " ";
        }

        if (isNumberEnds && currentNumber != 0) {
            result << to_string(currentNumber) << " ";
            currentNumber = 0;
        }
    }


    string modifiedString = result.str();
    // Remove the trailing space
    modifiedString.pop_back();

    return modifiedString;
}


int main() {
    ofstream outputFile("../output.txt");
    ifstream inputFile("../input.txt");

    // Check if the file is open
    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        string modifiedLine = convertWordsToNumber(line);
        outputFile << modifiedLine << "\n";
    }
    cout << "text successfully rewrote to file!!!";

    return 0;
}
