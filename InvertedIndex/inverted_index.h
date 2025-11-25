#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include "document.h"

/*
 * Builds a standard (non-positional) Inverted Index.
 * Output:
 *   term -> [list of document IDs]
 */
std::unordered_map<std::string, std::vector<int>> buildInvertedIndex(
    const std::vector<Document>& documents
);

/*
 * Simple console printer for the inverted index.
 * This is only for debugging or quick visualization.
 */
void printInvertedIndexSimple(
    const std::unordered_map<std::string, std::vector<int>>& index
);
