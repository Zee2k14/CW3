#include "Directory.hpp"
#include <algorithm>

/**
 * @brief Constructor for the Directory class.
 * @param name The name of the directory.
 * @param parent A pointer to the parent directory. Defaults to nullptr.
 */
Directory::Directory(const string& name, Directory* parent) : name(name), parentDirectory(parent) {}

/**
 * @brief Adds a file to the directory.
 * @param file The file to add.
 */
void Directory::addFile(const File& file) {
    files.push_back(file); // Add the file to the files vector
}

/**
 * @brief Removes a file from the directory.
 * @param filename The name of the file to remove.
 */
void Directory::removeFile(const string& filename) {
    files.erase(remove_if(files.begin(), files.end(), [&](const File& file) {
        return file.getName() == filename; // Check if the file name matches
    }), files.end()); // Erase the file from the vector
}

/**
 * @brief Adds a subdirectory to the directory.
 * @param dir The subdirectory to add.
 */
void Directory::addDirectory(const Directory& dir) {
    subdirectories.push_back(dir); // Add the directory to the subdirectories vector
}

/**
 * @brief Removes a subdirectory from the directory.
 * @param dirname The name of the subdirectory to remove.
 */
void Directory::removeDirectory(const string& dirname) {
    subdirectories.erase(remove_if(subdirectories.begin(), subdirectories.end(), [&](const Directory& dir) {
        return dir.getName() == dirname; // Check if the directory name matches
    }), subdirectories.end()); // Erase the directory from the vector
}

/**
 * @brief Lists the contents of the directory.
 * @return A vector of strings containing the names of files and subdirectories in the directory.
 */
vector<string> Directory::listContents() const {
    vector<string> contents;
    for (const auto& file : files) {
        contents.push_back(file.getName()); // Add the file name to contents
    }
    for (const auto& dir : subdirectories) {
        contents.push_back(dir.getName()); // Add the directory name to contents
    }
    return contents; // Return the list of contents
}

/**
 * @brief Gets the name of the directory.
 * @return The name of the directory.
 */
string Directory::getName() const {
    return name;
}

/**
 * @brief Gets the files in the directory.
 * @return A reference to the vector of files.
 */
vector<File>& Directory::getFiles() {
    return files; // Return the vector of files
}

/**
 * @brief Gets the subdirectories in the directory.
 * @return A reference to the vector of subdirectories.
 */
vector<Directory>& Directory::getSubdirectories() {
    return subdirectories; // Return the vector of subdirectories
}

/**
 * @brief Gets the parent directory.
 * @return A pointer to the parent directory.
 */
Directory* Directory::getParentDirectory() const {
    return parentDirectory; // Return a pointer to the parent directory
}

/**
 * @brief Finds a file in the directory.
 * @param filename The name of the file to find.
 * @return A pointer to the file if found, nullptr otherwise.
 */
File* Directory::findFile(const string& filename) {
    for (auto& file : files) {
        if (file.getName() == filename) { // Check if the file name matches
            return &file; // Return a pointer to the file
        }
    }
    return nullptr; // Return nullptr if the file is not found
}
