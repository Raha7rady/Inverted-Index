#pragma once
#include <unordered_map>
#include <vector>
#include <string>

/*
 * Pretty-print the inverted index in a clean tabular format.
 * showDocCount = prints df(term) beside each posting list.
 */
void printInvertedIndex(
    const std::unordered_map<std::string, std::vector<int>>& index,
    bool showDocCount = false
);

/*
 * Save inverted index into a human-readable TXT file.
 * Format: term: [1, 3, 5]
 */
bool writeIndexToTXT(
    const std::unordered_map<std::string, std::vector<int>>& index,
    const std::string& outPath
);

/*
 * Save inverted index into a CSV file.
 * CSV columns:
 *      term, docIDs
 * docIDs are stored in a sep-separated list inside the cell.
 */
bool writeIndexToCSV(
    const std::unordered_map<std::string, std::vector<int>>& index,
    const std::string& outPath,
    char sep = ','
);
