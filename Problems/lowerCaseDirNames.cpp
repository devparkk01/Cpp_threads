/*
Algorithmic exercise for lowercasing all directories and sub-directories names.
*/

#include <iostream>
#include <filesystem>
#include <algorithm>
#include <string>

using namespace std; 
namespace fs = std::filesystem;

// Helper function to convert a string to lowercase
string toLowercase(const string &str) {
    string lowerString = str;
    for(int i = 0 ; i < lowerString.size() ; ++i) {
        lowerString[i] = tolower(lowerString[i]);
    }
    return lowerString;
}

// Function to lowercase directory names recursively
void lowercaseDirectoryNames(const fs::path &directoryPath) {
    if (!fs::is_directory(directoryPath)) return;

    for (const auto &entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_directory(entry.path())) {
            fs::path currentPath = entry.path();
            fs::path lowerPath = currentPath.parent_path() / toLowercase(currentPath.filename().string());

            if (currentPath != lowerPath) {
                fs::rename(currentPath, lowerPath); // Rename the directory
            }

            lowercaseDirectoryNames(lowerPath); // Recur for subdirectories
        }
    }
}

int main() {
    string rootPath;
    cout << "Enter the root directory path: ";
    getline(cin, rootPath);
    cout << rootPath << endl; 

    try {
        lowercaseDirectoryNames(rootPath);
        cout << "All directory names have been lowercased successfully.\n";
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
