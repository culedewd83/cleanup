#ifndef CLEANUP_HPP
#define CLEANUP_HPP
#include <stack>
#include <filesystem>

class Cleanup {

private:
    // Variables
    bool m_isTestRun;
    bool m_isRecursive;
    int  m_daysBetweenDeletion;
    std::stack<std::filesystem::path> m_paths;

    // Functions
    int parseArguments(int argc, char **argv);
    bool is_valid_directory(std::string path);
    bool isValidRegexPattern(const std::string &regex);
    void discover_directories_recursive(std::filesystem::path dir);

public:
    int execute(int argc, char **argv);

};

#endif