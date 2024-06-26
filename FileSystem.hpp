#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <string>
#include <vector>
#include "Directory.hpp"
#include "File.hpp"

/**
 * @class FileSystem
 * @brief A class representing a simple file system with basic file and directory operations.
 */
class FileSystem {
private:
    Directory rootDirectory; ///< The root directory of the file system.
    Directory* currentDirectory; ///< The current working directory.

    /**
     * @brief Splits a file path into its component parts.
     * @param path The file path to split.
     * @return A vector of strings representing the parts of the path.
     */
    std::vector<std::string> splitPath(const std::string& path) const;

    /**
     * @brief Traverses to a directory given a root directory and a vector of path parts.
     * @param root The root directory to start from.
     * @param pathParts The parts of the path to traverse.
     * @return A pointer to the directory if found.
     * @throws std::runtime_error if the directory is not found.
     */
    Directory* traverseToDirectory(Directory& root, const std::vector<std::string>& pathParts) const;

    /**
     * @brief Determines if a given path is absolute.
     * @param path The path to check.
     * @return true if the path is absolute, false otherwise.
     */
    bool isAbsolutePath(const std::string& path) const;

public:
    /**
     * @brief Constructor for the FileSystem class.
     */
    FileSystem();

    /**
     * @brief Creates a file in the current directory.
     * @param filename The name of the file to create.
     */
    void createFile(const std::string& filename);

    /**
     * @brief Deletes a file from the current directory.
     * @param filename The name of the file to delete.
     */
    void deleteFile(const std::string& filename);

    /**
     * @brief Reads data from a file in the current directory.
     * @param filename The name of the file to read.
     * @return A vector of characters containing the file data.
     * @throws std::runtime_error if the file is not found.
     */
    std::vector<char> readFile(const std::string& filename);

    /**
     * @brief Writes data to a file in the current directory.
     * @param filename The name of the file to write to.
     * @param data The data to write to the file.
     * @throws std::runtime_error if the file is not found.
     */
    void writeFile(const std::string& filename, const std::vector<char>& data);

    /**
     * @brief Creates a directory in the current directory.
     * @param dirname The name of the directory to create.
     */
    void createDirectory(const std::string& dirname);

    /**
     * @brief Deletes a directory from the current directory.
     * @param dirname The name of the directory to delete.
     */
    void deleteDirectory(const std::string& dirname);

    /**
     * @brief Gets the root directory of the file system.
     * @return A reference to the root directory.
     */
    Directory& getRootDirectory();

    /**
     * @brief Gets the current working directory.
     * @return A pointer to the current working directory.
     */
    Directory* getCurrentDirectory();

    /**
     * @brief Changes the current working directory.
     * @param path The path of the directory to change to.
     * @throws std::runtime_error if the directory is not found.
     */
    void changeDirectory(const std::string& path);
};

#endif 