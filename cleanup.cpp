#include <iostream>
#include "args.hxx"

int main(int argc, char **argv)
{
    args::ArgumentParser parser("Cleanup can be used to delete files that match certain conditions such as older then X days while keeping one file per X days", "This goes after the options.");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

    try {
        parser.ParseCLI(argc, argv);
    } catch (const args::Help&) {
        std::cout << parser;
        return 0;
    } catch (const args::ParseError& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    
    return 0;
}