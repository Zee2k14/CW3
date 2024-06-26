#include "File.hpp"

/**
 * @brief Constructor for the File class.
 * @param name The name of the file.
 */
File::File(const std::string& name) : name(name) {}

/**
 * @brief Gets the name of the file.
 * @return The name of the file.
 */
std::string File::getName() const {
    return name;
}

/**
 * @brief Writes data to the file.
 * @param newData The data to write to the file.
 */
void File::write(const std::vector<char>& newData) {
    data = newData; // Overwrite the existing data with new data
}

/**
 * @brief Reads data from the file.
 * @return The data contained in the file.
 */
std::vector<char> File::read() const {
    return data; // Return the data stored in the file
}

/**
 * @brief Gets a reference to the data in the file.
 * @return A reference to the vector of data.
 */
std::vector<char>& File::getData() { 
    return data; // Return a reference to the data vector
}
