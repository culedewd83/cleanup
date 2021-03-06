#include "cleanup.hpp"
#include "args.hxx"
#include <regex>

int Cleanup::execute(int argc, char **argv) {
    // auto now = time(NULL);
    // auto* tm = localtime(&now);
    // tm->tm_mday += 14;
    // auto later = mktime(tm);
    // char* dt = ctime(&later);
    // std::cout << "The current local date and time is: " << dt << std::endl;

    int argResult = parse_arguments(argc, argv);
    if (argResult != 0) {
        return argResult;
    }

    std::cout << "path: " << m_paths.top() << std::endl;
    std::cout << "days: " << m_days_between_deletion << std::endl;
    std::cout << "days before to ignore: " << m_days_before_deletion << std::endl;
    std::cout << "ignore after x days: " << m_ignore_after_num_of_days << std::endl;

    return 0;
}

int Cleanup::parse_arguments(int argc, char **argv) {
    args::ArgumentParser parser("Cleanup can be used to delete files that match certain conditions such as older then X days while keeping one file per X days", "This goes after the options.");
    args::HelpFlag help(parser, "", "Display this help menu", {'h', "help"});
    args::ValueFlag<std::string> directory(parser, "path", "Directory to begin cleanup.", {'d', "dir"});
    args::ValueFlag<int> days(parser, "days", "Number of days between NOT deleting a matching file. This is a required arument.", {'n', "num"});
    args::ValueFlag<int> days_before(parser, "days", "Beginning today, the number of days to ignore before deleting matching files. Default is 0.", {'b', "before"});
    args::ValueFlag<int> days_after(parser, "days", "Ignore all files after this number of days. When before days is 0, this must be at least 1. When before days is greater than 1, it must be at least 2 more than before days.", {'a', "after"});
    args::ValueFlag<std::string> pattern(parser, "regex pattern", "A regex pattern to match files for cleanup. Files not matching the pattern will be ignored. If a regex pattern is not provided, all files will be included.", {'p', "pattern"});
    args::Flag test_run(parser, "", "Perform a 'test run'. Outputs the files that match the condition for deletion without deleting them.", {'t', "test"});
    args::Flag recursive(parser, "", "Recurse sub-directories", {'r', "recursive"});

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

    m_days_before_deletion = days_before ? days_before.Get() : 0;

    if (days_after) {
        m_ignore_after_num_of_days = days_after.Get();
        if ((m_days_before_deletion == 0 && m_ignore_after_num_of_days < 1) || (m_days_before_deletion > 0 && (m_ignore_after_num_of_days - m_days_before_deletion) < 2)) {
            std::cerr << "The ignore after days must be more than begin after days" << std::endl; 
            std::cerr << parser;
        return 1;
        }
    }

    if (pattern && !is_valid_regex_pattern(pattern.Get())) {
        std::cerr << "The povided regex pattern is invalid." << std::endl; 
        std::cerr << parser;
        return 1;
    }

    if (m_is_recursive) {
        discover_directories_recursive(m_paths.top());
    }

    while (m_paths.size() > 0) {
        match_and_delete(m_paths.top());
        m_paths.pop();
    }

    return 0;
}

bool Cleanup::is_valid_directory(std::string path) {
    return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}

bool Cleanup::is_valid_regex_pattern(const std::string &regex) {
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

void Cleanup::match_and_delete(std::filesystem::path& path) {
    for (auto& file : std::filesystem::directory_iterator(path)) {
        std::cout << file << std::endl;
        // try {
        //     if (!file.is_directory() && file.is_regular_file()) {
        //         try {
        //          std::cout << file << std::endl;
        //         } catch (...) {

        //         }
        //     }
        // } catch (...) {

        // }
    }
}