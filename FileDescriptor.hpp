#ifndef FILEDESCRIPTOR_HPP
#define FILEDESCRIPTOR_HPP

#include <vector>
#include "File.hpp"

/**
 * @class FileDescriptor
 * @brief A class that provides an interface to read from and write to a File object.
 */
class FileDescriptor {
private:
    File& file; ///< Reference to the associated file.
    size_t position; ///< Current position within the file for reading/writing.

public:
    /**
     * @brief Constructor for the FileDescriptor class.
     * @param file The file to associate with this file descriptor.
     */
    FileDescriptor(File& file);

    /**
     * @brief Sets the current position within the file.
     * @param pos The position to seek to.
     */
    void seek(size_t pos);

    /**
     * @brief Reads a specified number of bytes from the file.
     * @param length The number of bytes to read.
     * @return A vector containing the bytes read from the file.
     */
    std::vector<char> read(size_t length);

    /**
     * @brief Writes data to the file at the current position.
     * @param data The data to write to the file.
     */
    void write(const std::vector<char>& data);
};

#endif 
