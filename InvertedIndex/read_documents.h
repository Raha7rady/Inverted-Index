#pragma once
#include <string>
#include "document.h"

/*
 * Reads a document from disk and loads its raw content.
 * Parameters:
 *   - filename: path to the document file (.txt, extracted PDF, etc.)
 *   - docID:    unique numeric ID assigned to the document
 *
 * Returns:
 *   Document struct containing filename, docID, and raw text content.
 */
Document readDocument(const std::string& filename, int docID);
