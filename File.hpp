#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <vector>

/**
 * @class File
 * @brief A class representing a file that contains a name and data.
 */
class File {
private:
    std::string name; ///< The name of the file.
    std::vector<char> data; ///< The data contained in the file.

public:
    /**
     * @brief Constructor for the File class.
     * @param name The name of the file.
     */
    File(const std::string& name);

    /**
     * @brief Gets the name of the file.
     * @return The name of the file.
     */
    std::string getName() const;

    /**
     * @brief Writes data to the file.
     * @param newData The data to write to the file.
     */
    void write(const std::vector<char>& newData);

    /**
     * @brief Reads data from the file.
     * @return The data contained in the file.
     */
    std::vector<char> read() const;

    /**
     * @brief Gets a reference to the data in the file.
     * @return A reference to the vector of data.
     */
    std::vector<char>& getData(); 
};

#endif 