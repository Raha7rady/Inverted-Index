#pragma once
#include <string>
#include <vector>
#include <unordered_set>

/*
 * Converts all characters in a string to lowercase.
 */
std::string toLowerCase(const std::string& input);

/*
 * Removes punctuation and non-alphanumeric characters.
 * Keeps only letters, digits, and whitespace.
 */
std::string removePunctuation(const std::string& text);

/*
 * Tokenizes text into words.
 * Steps:
 *   1) remove punctuation
 *   2) split by whitespace
 *   3) lowercase
 *   4) remove stopwords
 */
std::vector<std::string> tokenize(
    const std::string& text,
    const std::unordered_set<std::string>& stopwords
);

/*
 * Loads a default English stopword set.
 * Hard-coded minimal set. Can be extended or loaded from file.
 */
std::unordered_set<std::string> loadStopWords();
