// #include <iostream>
// #include <filesystem>
// #include <regex>
// #include <stack>
// #include "args.hxx"
#include "cleanup.hpp"

// bool isValidRegexPattern(const std::string &regex) {
//     try {
//         std::regex re(regex);
//     } catch (const std::regex_error& ) {
//         return false;
//     }
//     return true;
// }

int main(int argc, char **argv)
{
    // // Arguments
    // args::ArgumentParser parser("Cleanup can be used to delete files that match certain conditions such as older then X days while keeping one file per X days", "This goes after the options.");
    // args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    // args::ValueFlag<std::string> directory(parser, "path", "Directory to begin cleanup.", {'d', "dir"});
    // args::ValueFlag<int> days(parser, "Days", "Number of days between NOT deleting a matching file. This is a required arument.", {'n', "num"});
    // args::ValueFlag<std::string> pattern(parser, "Pattern", "A regex pattern to match files for cleanup. Files not matching the pattern will be ignored. If a regex pattern is not provided, all files will be included.", {'p', "pattern"});
    // args::Flag testRun(parser, "Test Run", "Perform a 'test run'. Outputs the files that match the condition for deletion without deleting them.", {'t', "test"});
    // args::Flag recursive(parser, "Recursive", "Recurse sub-directories", {'r', "recursive"});

    // // Variables
    // std::stack<std::filesystem::path> paths;

    // // Parse the arguments
    // try {
    //     parser.ParseCLI(argc, argv);
    // } catch (const args::Help&) {
    //     std::cout << parser;
    //     return 0;
    // } catch (const args::ParseError& e) {
    //     std::cerr << "Error parsing arguments." << std::endl << std::endl;
    //     std::cerr << parser;
    //     return 1;
    // } catch (const args::ValidationError& e) {
    //     std::cerr << e.what() << std::endl;
    //     std::cerr << parser;
    //     return 1;
    // }
    
    // const bool isTestRun = testRun;
    // const bool isRecursive = recursive;

    // if (directory) {
    //     std::filesystem::path p(directory.Get());
        
    //     // Check is path exists
    //     if (!std::filesystem::exists(p)) {
    //         std::cerr << "Directory: " << directory.Get() << std::endl << "The provided directory does not exist." << std::endl; 
    //         return 1;
    //     }

    //     // Check if path is a directory
    //     if (!std::filesystem::is_directory(p)) {
    //         std::cerr << "Directory: " << directory.Get() << std::endl << "The provided path is not a directory." << std::endl; 
    //         return 1;
    //     }

    //     paths.push(p);
    // } else {
    //     paths.push(std::filesystem::path(std::filesystem::current_path()));
    // }

    // // Make sure the number of days was provided
    // if (!days) {
    //     std::cerr << "The number of days is required." << std::endl; 
    //     std::cerr << parser;
    //     return 1;
    // }

    // const int numberOfDays = days.Get();

    // if (pattern && !isValidRegexPattern(pattern.Get())) {
    //     std::cerr << "The povided regex pattern is invalid." << std::endl; 
    //     std::cerr << parser;
    //     return 1;
    // }

    // std::cout << "path: " << paths.top() << std::endl;
    // std::cout << "days: " << numberOfDays << std::endl;
    Cleanup clean;
    int result = clean.execute(argc, argv);
    return result;
}