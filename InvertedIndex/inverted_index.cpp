#include "inverted_index.h"
#include <algorithm>

/*
 * Build a non-positional inverted index.
 *
 * Steps:
 *   1) Temporary structure: term -> set(docIDs)
 *   2) Convert each set to a sorted vector
 *
 * This ensures unique docIDs and deterministic ordering.
 */
std::unordered_map<std::string, std::vector<int>> buildInvertedIndex(
    const std::vector<Document>& documents
) {
    // Temporary index: sets ensure no duplicate doc IDs
    std::unordered_map<std::string, std::unordered_set<int>> tempIndex;

    for (const auto& doc : documents) {
        for (const auto& term : doc.tokens) {
            tempIndex[term].insert(doc.docID);
        }
    }

    // Final index: convert sets to sorted vectors
    std::unordered_map<std::string, std::vector<int>> invertedIndex;

    for (const auto& entry : tempIndex) {
        const std::string& term = entry.first;

        // Copy set → vector
        std::vector<int> docList(entry.second.begin(), entry.second.end());

        // Sort for consistency (important for IR reproducibility)
        std::sort(docList.begin(), docList.end());

        invertedIndex[term] = std::move(docList);
    }

    return invertedIndex;
}

/*
 * Simple console printer.
 * Used mainly for debugging.
 */
void printInvertedIndexSimple(
    const std::unordered_map<std::string, std::vector<int>>& index
) {
    std::cout << "--------------- Inverted Index (Simple) ---------------\n";

    // Sort terms alphabetically
    std::vector<std::string> terms;
    terms.reserve(index.size());
    for (const auto& entry : index)
        terms.push_back(entry.first);

    std::sort(terms.begin(), terms.end());

    // Print index
    for (const auto& term : terms) {
        const auto& docIDs = index.at(term);

        std::cout << term << " -> [";

        for (size_t i = 0; i < docIDs.size(); ++i) {
            std::cout << docIDs[i];
            if (i < docIDs.size() - 1)
                std::cout << ", ";
        }

        std::cout << "]\n";
    }

    std::cout << "--------------------------------------------------------\n";
}
