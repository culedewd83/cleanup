#ifndef CLEANUP_HPP
#define CLEANUP_HPP
#include <stack>
#include <filesystem>

class Cleanup {

private:
    // Variables
    bool m_is_test_run;
    bool m_is_recursive;
    int  m_days_between_deletion;
    int  m_days_before_deletion;
    std::stack<std::filesystem::path> m_paths;

    // Functions
    int parse_arguments(int argc, char **argv);
    bool is_valid_directory(std::string path);
    bool is_valid_regex_pattern(const std::string &regex);
    void discover_directories_recursive(std::filesystem::path dir);

public:
    int execute(int argc, char **argv);

};

#endif