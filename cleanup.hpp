#ifndef CLEANUP_HPP
#define CLEANUP_HPP
#include <stack>
#include <filesystem>

class Cleanup {

private:
    // Variables
    bool m_is_test_run = false;
    bool m_is_recursive = false;
    int  m_days_between_deletion ;
    int  m_days_before_deletion = 0;
    int  m_ignore_after_num_of_days = 0;
    std::stack<std::filesystem::path> m_paths;

    // Functions
    int parse_arguments(int argc, char **argv);
    bool is_valid_directory(std::string path);
    bool is_valid_regex_pattern(const std::string &regex);
    void discover_directories_recursive(std::filesystem::path dir);
    void match_and_delete(std::filesystem::path& path);

public:
    int execute(int argc, char **argv);

};

#endif