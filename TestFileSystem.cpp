#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "FileSystem.hpp"
#include <algorithm>

// Test for creating a directory
TEST_CASE("Create Directory", "[filesystem]") {
    FileSystem fs;
    fs.createDirectory("home");
    REQUIRE(fs.getCurrentDirectory()->listContents().size() == 1);
    REQUIRE(fs.getCurrentDirectory()->listContents()[0] == "home");
}

// Test for creating a file and checking its existence
TEST_CASE("Create and Check File Existence", "[filesystem]") {
    FileSystem fs;
    fs.createFile("test.txt");
    REQUIRE(fs.getCurrentDirectory()->listContents().size() == 1);
    REQUIRE(fs.getCurrentDirectory()->listContents()[0] == "test.txt");
}

// Test for writing to a file and verifying data integrity
TEST_CASE("Write File and Verify Data", "[filesystem]") {
    FileSystem fs;
    fs.createFile("test.txt");
    std::vector<char> data{'H', 'e', 'l', 'l', 'o'};
    fs.writeFile("test.txt", data);

    std::vector<char> readData = fs.readFile("test.txt");
    REQUIRE(readData == data);
}

// Test for reading from a file and verifying data integrity
TEST_CASE("Read File and Verify Data", "[filesystem]") {
    FileSystem fs;
    fs.createFile("test.txt");
    std::vector<char> data{'H', 'e', 'l', 'l', 'o'};
    fs.writeFile("test.txt", data);

    std::vector<char> readData = fs.readFile("test.txt");
    REQUIRE(readData == data);
}

// Test for deleting a file and verifying its deletion
TEST_CASE("Delete File and Verify Deletion", "[filesystem]") {
    FileSystem fs;
    fs.createFile("test.txt");
    REQUIRE(fs.getCurrentDirectory()->listContents().size() == 1);
    fs.deleteFile("test.txt");
    REQUIRE(fs.getCurrentDirectory()->listContents().empty());
}

// Test for deleting a directory and verifying its deletion
TEST_CASE("Delete Directory and Verify Deletion", "[filesystem]") {
    FileSystem fs;
    fs.createDirectory("home");
    REQUIRE(fs.getCurrentDirectory()->listContents().size() == 1);
    fs.deleteDirectory("home");
    REQUIRE(fs.getCurrentDirectory()->listContents().empty());
}

// Test for changing directories
TEST_CASE("Change Directory", "[filesystem]") {
    FileSystem fs;
    fs.createDirectory("home");
    fs.changeDirectory("home");
    REQUIRE(fs.getCurrentDirectory()->getName() == "home");

    fs.changeDirectory("..");
    REQUIRE(fs.getCurrentDirectory()->getName() == "root");
}

// Test for creating nested directories and changing directories
TEST_CASE("Create Nested Directories and Change Directories", "[filesystem]") {
    FileSystem fs;
    fs.createDirectory("home");
    fs.changeDirectory("home");
    fs.createDirectory("user");
    REQUIRE(fs.getCurrentDirectory()->listContents().size() == 1);
    REQUIRE(fs.getCurrentDirectory()->listContents()[0] == "user");

    fs.changeDirectory("user");
    REQUIRE(fs.getCurrentDirectory()->getName() == "user");

    fs.changeDirectory("..");
    REQUIRE(fs.getCurrentDirectory()->getName() == "home");

    fs.changeDirectory("..");
    REQUIRE(fs.getCurrentDirectory()->getName() == "root");
}

// Test for handling non-existent file read
TEST_CASE("Read Non-existent File", "[filesystem]") {
    FileSystem fs;
    REQUIRE_THROWS_AS(fs.readFile("nonexistent.txt"), std::runtime_error);
}

// Test for handling non-existent file write
TEST_CASE("Write Non-existent File", "[filesystem]") {
    FileSystem fs;
    std::vector<char> data{'H', 'e', 'l', 'l', 'o'};
    REQUIRE_THROWS_AS(fs.writeFile("nonexistent.txt", data), std::runtime_error);
}

// Test for handling non-existent directory change
TEST_CASE("Change to Non-existent Directory", "[filesystem]") {
    FileSystem fs;
    REQUIRE_THROWS_AS(fs.changeDirectory("nonexistent"), std::runtime_error);
}

// Test for nested directory and file operations
TEST_CASE("Nested Directory and File Operations", "[filesystem]") {
    FileSystem fs;
    fs.createDirectory("home");
    fs.changeDirectory("home");
    fs.createDirectory("user");
    fs.changeDirectory("user");
    fs.createFile("file.txt");
    std::vector<char> data{'T', 'e', 's', 't'};
    fs.writeFile("file.txt", data);

    std::vector<char> readData = fs.readFile("file.txt");
    REQUIRE(readData == data);

    fs.changeDirectory("..");
    REQUIRE(fs.getCurrentDirectory()->getName() == "home");
    fs.changeDirectory("..");
    REQUIRE(fs.getCurrentDirectory()->getName() == "root");
}

// Test for listing directory contents
TEST_CASE("List Directory Contents", "[filesystem]") {
    FileSystem fs;
    fs.createDirectory("dir1");
    fs.createDirectory("dir2");
    fs.createFile("file1.txt");
    fs.createFile("file2.txt");

    auto contents = fs.getCurrentDirectory()->listContents();
    std::vector<std::string> expectedContents = {"dir1", "dir2", "file1.txt", "file2.txt"};
    
    // Sort both lists before comparison
    std::sort(contents.begin(), contents.end());
    std::sort(expectedContents.begin(), expectedContents.end());
    
    REQUIRE(contents == expectedContents);
}

// Test for changing to parent directory from root (should stay in root)
TEST_CASE("Change Directory to Parent from Root", "[filesystem]") {
    FileSystem fs;
    fs.changeDirectory("..");
    REQUIRE(fs.getCurrentDirectory()->getName() == "root");
}
