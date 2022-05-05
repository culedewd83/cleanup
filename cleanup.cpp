#include <iostream>
#include <filesystem>
#include "args.hxx"

int main(int argc, char **argv)
{
    // Arguments
    args::ArgumentParser parser("Cleanup can be used to delete files that match certain conditions such as older then X days while keeping one file per X days", "This goes after the options.");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::ValueFlag<std::string> directory(parser, "path", "Directory to begin cleanup.", {'d', "dir"});
    args::ValueFlag<int> days(parser, "Days", "Number of days between keeping a matching file. This is a required arument.", {'n', "num"});
    args::Flag testRun(parser, "Test Run", "Perform a 'test run'. Outputs the files that match the condition for deletion without deleting them.", {'t', "test"});
    args::Flag recursive(parser, "Recursive", "Recurse sub-directories", {'r', "recursive"});

    // Variables
    std::filesystem::path path(std::filesystem::current_path());

    // Parse the arguments
    try {
        parser.ParseCLI(argc, argv);
    } catch (const args::Help&) {
        std::cout << parser;
        return 0;
    } catch (const args::ParseError& e) {
        std::cerr << "Error parsing arguments." << std::endl << std::endl;
        std::cerr << parser;
        return 1;
    } catch (const args::ValidationError& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    
    const bool isTestRun = testRun;
    const bool isRecursive = recursive;

    if (directory) {
        std::filesystem::path p(directory.Get());
        
        // Check is path exists
        if (!std::filesystem::exists(p)) {
            std::cerr << "The provided directory does not exist." << std::endl; 
            return 1;
        }

        // Check if path is a directory
        if (!std::filesystem::is_directory(p)) {
            std::cerr << "The provided path is not a directory." << std::endl; 
            return 1;
        }

        // Override the default path to the one provided
        path = p;
    }

    // Make sure the number of days was provided
    if (!days) {
        std::cerr << "The number of days is required." << std::endl; 
        std::cerr << parser;
        return 1;
    }

    const int numberOfDays = days.Get();

    return 0;
}