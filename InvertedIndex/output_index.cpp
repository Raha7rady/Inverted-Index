#include "output_index.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <filesystem>
#include <iomanip>

namespace fs = std::filesystem;

/* ---------------------------------------------------------
 * Internal helper functions (not exposed to users)
 * --------------------------------------------------------- */
namespace {

    /*
     * Convert unordered_map → ordered map (sorted by term).
     * Also ensures docID lists are sorted + unique.
     */
    std::map<std::string, std::vector<int>>
        normalizeIndex(const std::unordered_map<std::string, std::vector<int>>& rawIndex)
    {
        std::map<std::string, std::vector<int>> normalized;

        for (const auto& kv : rawIndex) {
            std::vector<int> docs = kv.second;

            std::sort(docs.begin(), docs.end());
            docs.erase(std::unique(docs.begin(), docs.end()), docs.end());

            normalized.emplace(kv.first, std::move(docs));
        }

        return normalized;
    }

    /*
     * Format document list into a compact string: "[1, 2, 3]"
     */
    std::string formatDocList(const std::vector<int>& docs)
    {
        std::ostringstream oss;
        oss << "[";

        for (size_t i = 0; i < docs.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << docs[i];
        }

        oss << "]";
        return oss.str();
    }

} // namespace


/* ---------------------------------------------------------
 * Pretty-print Inverted Index on console
 * --------------------------------------------------------- */
void printInvertedIndex(
    const std::unordered_map<std::string, std::vector<int>>& index,
    bool showDocCount)
{
    auto sorted = normalizeIndex(index);

    // Determine column width for aligned output
    size_t maxTermLen = 0;
    for (const auto& kv : sorted)
        maxTermLen = std::max(maxTermLen, kv.first.size());

    std::cout << "\n=================== Inverted Index ===================\n";

    for (const auto& kv : sorted) {

        std::cout << std::left
            << std::setw(static_cast<int>(maxTermLen + 2))
            << kv.first
            << ": "
            << formatDocList(kv.second);

        if (showDocCount)
            std::cout << "  (df=" << kv.second.size() << ")";

        std::cout << "\n";
    }

    std::cout << "=======================================================\n";
}


/* ---------------------------------------------------------
 * Save index to TXT file
 * --------------------------------------------------------- */
bool writeIndexToTXT(
    const std::unordered_map<std::string, std::vector<int>>& index,
    const std::string& outPath)
{
    try {
        auto sorted = normalizeIndex(index);

        fs::path p(outPath);
        if (p.has_parent_path())
            fs::create_directories(p.parent_path());

        std::ofstream ofs(outPath);
        if (!ofs.is_open()) {
            std::cerr << "❌ Error: Cannot open file: " << outPath << "\n";
            return false;
        }

        for (const auto& kv : sorted)
            ofs << kv.first << ": " << formatDocList(kv.second) << "\n";

        return true;
    }
    catch (const std::exception& ex) {
        std::cerr << "❌ Exception in writeIndexToTXT: " << ex.what() << "\n";
        return false;
    }
}


/* ---------------------------------------------------------
 * Save index to CSV file (Excel-friendly)
 * --------------------------------------------------------- */
bool writeIndexToCSV(
    const std::unordered_map<std::string, std::vector<int>>& index,
    const std::string& outPath,
    char sep)
{
    try {
        auto sorted = normalizeIndex(index);

        fs::path p(outPath);
        if (p.has_parent_path())
            fs::create_directories(p.parent_path());

        std::ofstream ofs(outPath);
        if (!ofs.is_open()) {
            std::cerr << "❌ Error: Cannot open CSV file: " << outPath << "\n";
            return false;
        }

        ofs << "term,docIDs\n";

        for (const auto& kv : sorted) {
            ofs << "\"" << kv.first << "\",";

            for (size_t i = 0; i < kv.second.size(); ++i) {
                if (i > 0) ofs << sep;
                ofs << kv.second[i];
            }

            ofs << "\n";
        }

        return true;
    }
    catch (const std::exception& ex) {
        std::cerr << "❌ Exception in writeIndexToCSV: " << ex.what() << "\n";
        return false;
    }
}
