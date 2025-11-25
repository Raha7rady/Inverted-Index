#include "read_documents.h"
#include <fstream>
#include <sstream>
#include <iostream>

/*
 * Load raw text from a file.
 * Reads the file line by line and concatenates text into a single string.
 */
Document readDocument(const std::string& filename, int docID) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file: " << filename << std::endl;
        exit(EXIT_FAILURE); // fail fast – file missing is a critical error
    }

    std::stringstream buffer;
    std::string line;

    while (std::getline(file, line)) {
        buffer << line << " ";   // preserve spacing between lines
    }

    Document doc;
    doc.docID = docID;
    doc.filename = filename;
    doc.content = buffer.str();  // raw text before preprocessing

    return doc;
}
