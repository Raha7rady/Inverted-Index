#pragma once
#include <map>
#include <vector>
#include <string>
#include <unordered_map>

/*
 * Convert unordered inverted index into an ordered map (alphabetical terms).
 */
std::map<std::string, std::vector<int>>
buildSortedIndex(const std::unordered_map<std::string, std::vector<int>>& invertedIndex);

/*
 * Print a B-Tree-like graphical view to the console.
 * - sortedIndex: terms (map) produced by buildSortedIndex
 * - nodeSize: maximum keys per node (controls visual grouping)
 *
 * NOTE: This is a visualization (simulation), not a full B-Tree implementation.
 */
void printBTreeGraphical(const std::map<std::string, std::vector<int>>& sortedIndex,
    size_t nodeSize = 3);
