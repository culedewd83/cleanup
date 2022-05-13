#include "cleanup.hpp"
#include "args.hxx"
#include <regex>

int Cleanup::execute(int argc, char **argv) {
    int argResult = parseArguments(argc, argv);
    if (argResult != 0) {
        return argResult;
    }

    std::cout << "path: " << m_paths.top() << std::endl;
    std::cout << "days: " << m_days_between_deletion << std::endl;

    return 0;
}

int Cleanup::parseArguments(int argc, char **argv) {
    args::ArgumentParser parser("Cleanup can be used to delete files that match certain conditions such as older then X days while keeping one file per X days", "This goes after the options.");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::ValueFlag<std::string> directory(parser, "path", "Directory to begin cleanup.", {'d', "dir"});
    args::ValueFlag<int> days(parser, "Days", "Number of days between NOT deleting a matching file. This is a required arument.", {'n', "num"});
    args::ValueFlag<std::string> pattern(parser, "Pattern", "A regex pattern to match files for cleanup. Files not matching the pattern will be ignored. If a regex pattern is not provided, all files will be included.", {'p', "pattern"});
    args::Flag testRun(parser, "Test Run", "Perform a 'test run'. Outputs the files that match the condition for deletion without deleting them.", {'t', "test"});
    args::Flag recursive(parser, "Recursive", "Recurse sub-directories", {'r', "recursive"});

    try {
        parser.ParseCLI(argc, argv);
    } catch (const args::Help&) {
        std::cout << parser;
        return 1; // I hate that it return 1 (error) but for now it fixes a bug
    } catch (const args::ParseError& e) {
        std::cerr << "Error parsing arguments." << std::endl << std::endl;
        std::cerr << parser;
        return 1;
    } catch (const args::ValidationError& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    if (directory) {
        if (!is_valid_directory(directory.Get())) {
            std::cerr << "Directory: " << directory.Get() << std::endl << "The provided directory is invalid." << std::endl;
            return 1;
        } else {
            m_paths.push(std::filesystem::path(directory.Get()));
        }
    } else {
        m_paths.push(std::filesystem::path(std::filesystem::current_path()));
    }

    if (!days) {
        std::cerr << "The number of days is required." << std::endl; 
        std::cerr << parser;
        return 1;
    }

    m_days_between_deletion = days.Get();

    if (pattern && !isValidRegexPattern(pattern.Get())) {
        std::cerr << "The povided regex pattern is invalid." << std::endl; 
        std::cerr << parser;
        return 1;
    }

    if (m_is_recursive) {
        discover_directories_recursive(m_paths.top());
    }

    return 0;
}

bool Cleanup::is_valid_directory(std::string path) {
    return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}

bool Cleanup::isValidRegexPattern(const std::string &regex) {
    try {
        std::regex re(regex);
    } catch (const std::regex_error& ) {
        return false;
    }
    return true;
}

void Cleanup::discover_directories_recursive(std::filesystem::path dir) {
    for (const auto & file : std::filesystem::recursive_directory_iterator(dir)) {
        if (file.is_directory()) {
            m_paths.push(file.path());
        }
    }
}