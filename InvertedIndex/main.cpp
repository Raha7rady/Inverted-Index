//#include <iostream>
//#include <vector>
//#include <string>
//#include <unordered_set>
//
//#include "document.h"
//#include "preprocessing.h"     // توابع tokenize و loadStopWords
//#include "read_documents.h"    // تابع readDocument
//#include "inverted_index.h"    // buildInvertedIndex
//#include "display_terms.h"     // buildSortedIndex + printBTreeGraphical
//#include "output_index.h"      // printInvertedIndex + writeIndexToTXT/CSV
//
//int main() {
//    // لیست فایل‌های سند پروژه
//    std::vector<std::string> filenames = {
//        "document1.txt",
//        "document2.txt",
//        "document3.txt"
//    };
//
//    std::vector<Document> documents;
//    int docID = 1;
//
//    // بارگذاری stop words
//    std::unordered_set<std::string> stopwords = loadStopWords();
//
//    // خواندن و پیش‌پردازش اسناد
//    for (const auto& fname : filenames) {
//        Document doc = readDocument(fname, docID++);
//        doc.tokens = tokenize(doc.content, stopwords);
//        documents.push_back(doc);
//
//        std::cout << "Document #" << doc.docID
//            << " (" << doc.filename << ") - "
//            << doc.tokens.size() << " tokens after preprocessing.\n";
//    }
//
//    std::cout << "--------------------------------------\n";
//
//    // ساخت Inverted Index
//    std::unordered_map<std::string, std::vector<int>> inverted = buildInvertedIndex(documents);
//
//    // چاپ Inverted Index روی کنسول
//    printInvertedIndex(inverted);
//
//    // ذخیره Inverted Index در فایل
//    writeIndexToTXT(inverted, "output/inverted_index.txt");
//    writeIndexToCSV(inverted, "output/inverted_index.csv");
//
//    // ساخت Sorted Index برای نمایش B-Tree گرافیکی
//    std::map<std::string, std::vector<int>> sorted = buildSortedIndex(inverted);
//    printBTreeGraphical(sorted);
//
//    return 0;
//}


#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

#include "document.h"
#include "preprocessing.h"     // tokenize, loadStopWords
#include "read_documents.h"    // readDocument
#include "inverted_index.h"    // buildInvertedIndex
#include "display_terms.h"     // buildSortedIndex, printBTreeGraphical
#include "output_index.h"      // printInvertedIndex, writeIndexToTXT/CSV

int main() {
    // List of document files
    std::vector<std::string> filenames = {
        "document1.txt",
        "document2.txt",
        "document3.txt"
    };

    std::vector<Document> documents;
    int docID = 1;

    // Load stopwords
    std::unordered_set<std::string> stopwords = loadStopWords();

    // Read and preprocess documents
    for (const auto& fname : filenames) {
        Document doc = readDocument(fname, docID++);
        doc.tokens = tokenize(doc.content, stopwords);
        documents.push_back(doc);

        std::cout << "Document #" << doc.docID
            << " (" << doc.filename << ") - "
            << doc.tokens.size() << " tokens after preprocessing.\n";
    }

    std::cout << "--------------------------------------\n";

    // Build inverted index
    std::unordered_map<std::string, std::vector<int>> inverted = buildInvertedIndex(documents);

    // Print inverted index to console
    printInvertedIndex(inverted, true); // show document frequency

    // Save index to files
    if (writeIndexToTXT(inverted, "output/inverted_index.txt"))
        std::cout << "Inverted index saved to TXT successfully.\n";
    if (writeIndexToCSV(inverted, "output/inverted_index.csv"))
        std::cout << "Inverted index saved to CSV successfully.\n";

    // Build sorted index for B-Tree view
    std::map<std::string, std::vector<int>> sorted = buildSortedIndex(inverted);
    printBTreeGraphical(sorted, 4); // nodeSize = 4 for better visualization

    return 0;
}
