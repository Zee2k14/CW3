#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include "File.hpp"

using namespace std;

/**
 * @class Directory
 * @brief A class representing a directory that can contain files and subdirectories.
 */
class Directory {
private:
    string name;  ///< The name of the directory.
    vector<File> files;  ///< A vector containing the files in the directory.
    vector<Directory> subdirectories;  ///< A vector containing the subdirectories in the directory.
    Directory* parentDirectory;  ///< A pointer to the parent directory.

public:
    /**
     * @brief Constructor for the Directory class.
     * @param name The name of the directory.
     * @param parent A pointer to the parent directory. Defaults to nullptr.
     */
    Directory(const string& name, Directory* parent = nullptr); 

    /**
     * @brief Adds a file to the directory.
     * @param file The file to add.
     */
    void addFile(const File& file);

    /**
     * @brief Removes a file from the directory.
     * @param filename The name of the file to remove.
     */
    void removeFile(const string& filename);

    /**
     * @brief Adds a subdirectory to the directory.
     * @param dir The subdirectory to add.
     */
    void addDirectory(const Directory& dir);

    /**
     * @brief Removes a subdirectory from the directory.
     * @param dirname The name of the subdirectory to remove.
     */
    void removeDirectory(const string& dirname);

    /**
     * @brief Lists the contents of the directory.
     * @return A vector of strings containing the names of files and subdirectories in the directory.
     */
    vector<string> listContents() const;

    /**
     * @brief Gets the name of the directory.
     * @return The name of the directory.
     */
    string getName() const;

    /**
     * @brief Gets the files in the directory.
     * @return A reference to the vector of files.
     */
    vector<File>& getFiles(); 

    /**
     * @brief Gets the subdirectories in the directory.
     * @return A reference to the vector of subdirectories.
     */
    vector<Directory>& getSubdirectories(); 

    /**
     * @brief Gets the parent directory.
     * @return A pointer to the parent directory.
     */
    Directory* getParentDirectory() const; 

    /**
     * @brief Finds a file in the directory.
     * @param filename The name of the file to find.
     * @return A pointer to the file if found, nullptr otherwise.
     */
    File* findFile(const string& filename); 
};

#endif 
