#include "FileSystem.hpp"
#include <stdexcept>
#include <sstream>

/**
 * @brief Helper function to split a path into its components.
 * @param path The file path to split.
 * @return A vector of strings representing the parts of the path.
 */
std::vector<std::string> FileSystem::splitPath(const std::string& path) const {
    std::vector<std::string> parts;
    std::stringstream ss(path);
    std::string part;
    while (std::getline(ss, part, '/')) { // Split the path by '/'
        if (!part.empty()) { // Ignore empty parts (e.g., consecutive slashes)
            parts.push_back(part);
        }
    }
    return parts;
}

/**
 * @brief Helper function to traverse to a directory given a root directory and a vector of path parts.
 * @param root The root directory to start from.
 * @param pathParts The parts of the path to traverse.
 * @return A pointer to the directory if found.
 * @throws std::runtime_error if the directory is not found.
 */
Directory* FileSystem::traverseToDirectory(Directory& root, const std::vector<std::string>& pathParts) const {
    Directory* currentDir = &root; // Start traversal from the root directory
    for (const auto& part : pathParts) {
        bool found = false;
        for (auto& subDir : currentDir->getSubdirectories()) { // Search for the next part in subdirectories
            if (subDir.getName() == part) {
                currentDir = &subDir; // Move to the found subdirectory
                found = true;
                break;
            }
        }
        if (!found) {
            throw std::runtime_error("Directory not found: " + part); // Directory not found
        }
    }
    return currentDir; // Return the final directory reached
}

/**
 * @brief Helper function to determine if a path is absolute.
 * @param path The path to check.
 * @return true if the path is absolute, false otherwise.
 */
bool FileSystem::isAbsolutePath(const std::string& path) const {
    return !path.empty() && path[0] == '/'; // Absolute path starts with '/'
}

/**
 * @brief Constructor for the FileSystem class.
 */
FileSystem::FileSystem() : rootDirectory("root") {
    currentDirectory = &rootDirectory; // Set the initial current directory to the root
}

/**
 * @brief Creates a file in the current directory.
 * @param filename The name of the file to create.
 */
void FileSystem::createFile(const std::string& filename) {
    currentDirectory->addFile(File(filename)); // Add a new file to the current directory
}

/**
 * @brief Deletes a file from the current directory.
 * @param filename The name of the file to delete.
 */
void FileSystem::deleteFile(const std::string& filename) {
    currentDirectory->removeFile(filename); // Remove the file from the current directory
}

/**
 * @brief Reads data from a file in the current directory.
 * @param filename The name of the file to read.
 * @return A vector of characters containing the file data.
 * @throws std::runtime_error if the file is not found.
 */
std::vector<char> FileSystem::readFile(const std::string& filename) {
    File* file = currentDirectory->findFile(filename); // Find the file in the current directory
    if (file) {
        return file->read(); // Return the file data
    }
    throw std::runtime_error("File not found: " + filename); // File not found
}

/**
 * @brief Writes data to a file in the current directory.
 * @param filename The name of the file to write to.
 * @param data The data to write to the file.
 * @throws std::runtime_error if the file is not found.
 */
void FileSystem::writeFile(const std::string& filename, const std::vector<char>& data) {
    File* file = currentDirectory->findFile(filename); // Find the file in the current directory
    if (file) {
        file->write(data); // Write the data to the file
        return;
    }
    throw std::runtime_error("File not found: " + filename); // File not found
}

/**
 * @brief Creates a directory in the current directory.
 * @param dirname The name of the directory to create.
 */
void FileSystem::createDirectory(const std::string& dirname) {
    currentDirectory->addDirectory(Directory(dirname, currentDirectory)); // Add a new directory with the current directory as its parent
}

/**
 * @brief Deletes a directory from the current directory.
 * @param dirname The name of the directory to delete.
 */
void FileSystem::deleteDirectory(const std::string& dirname) {
    currentDirectory->removeDirectory(dirname); // Remove the directory from the current directory
}

/**
 * @brief Gets the root directory of the file system.
 * @return A reference to the root directory.
 */
Directory& FileSystem::getRootDirectory() {
    return rootDirectory;
}

/**
 * @brief Gets the current working directory.
 * @return A pointer to the current working directory.
 */
Directory* FileSystem::getCurrentDirectory() {
    return currentDirectory;
}

/**
 * @brief Changes the current working directory.
 * @param path The path of the directory to change to.
 * @throws std::runtime_error if the directory is not found.
 */
void FileSystem::changeDirectory(const std::string& path) {
    if (path == "..") { // Handle changing to parent directory
        if (currentDirectory->getParentDirectory()) {
            currentDirectory = currentDirectory->getParentDirectory(); // Move to the parent directory
        }
    } else {
        auto pathParts = splitPath(path); // Split the path into parts
        Directory* newCurrentDirectory = isAbsolutePath(path) ? traverseToDirectory(rootDirectory, pathParts) : traverseToDirectory(*currentDirectory, pathParts); // Traverse to the target directory
        currentDirectory = newCurrentDirectory; // Set the new current directory
    }
}
