#ifndef CLEANUP_HPP
#define CLEANUP_HPP
#include <stack>
#include <filesystem>

class Cleanup {

private:
    bool m_isTestRun;
    bool m_isRecursive;
    int  m_daysBetweenDeletion;
    std::stack<std::filesystem::path> m_paths;

    int parseArguments(int argc, char **argv);
    bool isValidDirectory(std::string path);
    bool isValidRegexPattern(const std::string &regex);

public:
    int execute(int argc, char **argv);

};

#endif