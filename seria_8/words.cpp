#include <iostream>
#include <string>
#include <map>
#include <sstream>

typedef std::map<std::string, int> WordCountMap;

void countWords(const std::string& input, WordCountMap& wordCounts) {
    std::istringstream iss(input);
    std::string word;

    while (iss >> word) {
        ++wordCounts[word];
    }
}

int main() {
    std::string input = "pies kot żółw kot kot pies żółw";

    WordCountMap wordCounts;
    countWords(input, wordCounts);

    for (const auto& pair : wordCounts) {
        std::cout << pair.first << " ilość wystąpień: " << pair.second << " times\n";
    }

    return 0;
}