#include "FileDescriptor.hpp"

/**
 * @brief Constructor for the FileDescriptor class.
 * @param file The file to associate with this file descriptor.
 */
FileDescriptor::FileDescriptor(File& file) : file(file), position(0) {}

/**
 * @brief Sets the current position within the file.
 * @param pos The position to seek to.
 */
void FileDescriptor::seek(size_t pos) {
    position = pos; // Set the current position to the specified value
}

/**
 * @brief Reads a specified number of bytes from the file.
 * @param length The number of bytes to read.
 * @return A vector containing the bytes read from the file.
 */
std::vector<char> FileDescriptor::read(size_t length) {
    std::vector<char> data = file.read(); // Read the entire file data
    if (position + length > data.size()) { // Check if the read length exceeds the file size
        length = data.size() - position; // Adjust the length to read only available data
    }
    // Extract the requested portion of data starting from the current position
    std::vector<char> result(data.begin() + position, data.begin() + position + length);
    position += length; // Update the current position
    return result; // Return the extracted data
}

/**
 * @brief Writes data to the file at the current position.
 * @param data The data to write to the file.
 */
void FileDescriptor::write(const std::vector<char>& data) {
    std::vector<char> currentData = file.read(); // Read the current file data
    // Check if the write operation exceeds the current file size
    if (position + data.size() > currentData.size()) {
        currentData.resize(position + data.size()); // Resize the file data to accommodate new data
    }
    // Copy the new data into the current data starting from the current position
    std::copy(data.begin(), data.end(), currentData.begin() + position);
    file.write(currentData); // Write the updated data back to the file
    position += data.size(); // Update the current position
}
