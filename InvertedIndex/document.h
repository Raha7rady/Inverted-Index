#pragma once
#include <string>
#include <vector>

/*
 * Represents a single document in the system.
 * Each document has:
 * - docID:     Unique numeric ID
 * - filename:  Name of the file (PDF/TXT/Word/…)
 * - content:   Raw text extracted from the file
 * - tokens:    Preprocessed list of tokens
 */

struct Document {
    int docID = 0;                 // Unique document ID
    std::string filename;          // File name
    std::string content;           // Raw extracted text
    std::vector<std::string> tokens; // List of tokens after preprocessing
};
