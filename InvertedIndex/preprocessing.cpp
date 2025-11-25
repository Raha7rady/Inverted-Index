#include "preprocessing.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <cctype>

/*
 * Convert string to lowercase using std::tolower.
 */
std::string toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

/*
 * Replace punctuation and non-alphanumeric characters with spaces.
 * Regex: anything NOT A-Z, a-z, 0-9, or whitespace.
 */
std::string removePunctuation(const std::string& text) {
    static const std::regex pattern(R"([^A-Za-z0-9\s])");
    return std::regex_replace(text, pattern, " ");
}

/*
 * Tokenize text:
 *   - remove punctuation
 *   - split by spaces
 *   - lowercase
 *   - remove stopwords
 */
std::vector<std::string> tokenize(
    const std::string& text,
    const std::unordered_set<std::string>& stopwords
) {
    std::vector<std::string> tokens;

    // Clean text
    std::string clean = removePunctuation(text);
    std::istringstream iss(clean);
    std::string word;

    // Extract tokens
    while (iss >> word) {
        word = toLowerCase(word);

        // Skip stopwords
        if (!word.empty() && stopwords.find(word) == stopwords.end()) {
            tokens.push_back(word);
        }
    }

    return tokens;
}

/*
 * Basic English stopword list.
 * Can be expanded or moved to a file-based loader.
 */
std::unordered_set<std::string> loadStopWords() {
    return {
        "the", "is", "and", "a", "an", "in", "on", "of",
        "for", "to", "with", "as", "by", "at", "it",
        "this", "that", "from", "be", "or", "are"
    };
}
