#include "display_terms.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

/*
 * Build a sorted index from unordered inverted index
 */
std::map<std::string, std::vector<int>>
buildSortedIndex(const std::unordered_map<std::string, std::vector<int>>& invertedIndex) {
    std::map<std::string, std::vector<int>> sorted;
    for (const auto& kv : invertedIndex)
        sorted[kv.first] = kv.second;
    return sorted;
}

/*
 * Node structure for printing simulation
 */
struct TreeNode {
    std::vector<std::string> keys;
    std::vector<TreeNode*> children;
};

/*
 * Recursively build a visual B-tree for printing
 */
static TreeNode* buildTree(const std::vector<std::string>& keys, size_t nodeSize, size_t& index) {
    if (index >= keys.size()) return nullptr;

    TreeNode* node = new TreeNode();
    size_t remaining = keys.size() - index;
    size_t count = std::min(remaining, nodeSize);
    for (size_t i = 0; i < count; ++i)
        node->keys.push_back(keys[index++]);

    // For non-leaf nodes, create children
    if (index < keys.size()) {
        for (size_t i = 0; i <= node->keys.size(); ++i) {
            TreeNode* child = buildTree(keys, nodeSize, index);
            if (child) node->children.push_back(child);
        }
    }
    return node;
}

/*
 * Compute max key width
 */
static size_t computeMaxKeyWidth(TreeNode* node) {
    if (!node) return 0;
    size_t maxWidth = 0;
    for (const auto& k : node->keys)
        maxWidth = std::max(maxWidth, k.size());
    for (auto* child : node->children)
        maxWidth = std::max(maxWidth, computeMaxKeyWidth(child));
    return maxWidth;
}

/*
 * Print a single node box
 */
static void printNodeBox(const std::vector<std::string>& keys, size_t widthPerKey, int offset) {
    for (const auto& k : keys) std::cout << std::string(offset, ' ') << "+" << std::string(widthPerKey + 2, '-') << "+";
    std::cout << "\n";
    for (const auto& k : keys) {
        std::string cell = k;
        if (cell.size() > widthPerKey) {
            if (widthPerKey > 3) cell = cell.substr(0, widthPerKey - 3) + "...";
            else cell = cell.substr(0, widthPerKey);
        }
        std::cout << std::string(offset, ' ') << "| " << std::left << std::setw((int)widthPerKey) << cell << " |";
    }
    std::cout << "\n";
    for (const auto& k : keys) std::cout << std::string(offset, ' ') << "+" << std::string(widthPerKey + 2, '-') << "+";
    std::cout << "\n";
}

/*
 * Recursive pretty print for B-tree
 */
static void printTree(TreeNode* node, size_t widthPerKey, int offset = 0, int level = 0) {
    if (!node) return;

    std::cout << "Level " << level << ":\n";
    printNodeBox(node->keys, widthPerKey, offset);

    if (!node->children.empty()) {
        int childOffset = offset;
        for (auto* child : node->children) {
            // Connector line
            std::cout << std::string(childOffset + (int)((widthPerKey + 2) / 2), ' ') << "|\n";
            // Diagonal
            std::cout << std::string(childOffset + (int)((widthPerKey + 2) / 2) - 1, ' ') << "/ \\\n";

            printTree(child, widthPerKey, childOffset, level + 1);
            // Update offset for next child
            childOffset += (int)((widthPerKey + 2) * child->keys.size() + 2);
        }
    }
}

/*
 * Main B-tree graphical function
 */
void printBTreeGraphical(const std::map<std::string, std::vector<int>>& sortedIndex,
    size_t nodeSize) {

    std::cout << "\n================ B-TREE GRAPHICAL VIEW ================\n";

    if (sortedIndex.empty()) {
        std::cout << "(Index is empty)\n";
        return;
    }

    // Collect keys
    std::vector<std::string> keys;
    for (const auto& kv : sortedIndex)
        keys.push_back(kv.first);

    // Build tree
    size_t index = 0;
    TreeNode* root = buildTree(keys, nodeSize, index);

    // Compute max key width
    size_t widthPerKey = computeMaxKeyWidth(root);
    widthPerKey = std::max<size_t>(widthPerKey, 6);

    // Print recursively
    printTree(root, widthPerKey);

    std::cout << "\n=======================================================\n";
}
