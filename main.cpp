#include "cleanup.hpp"

int main(int argc, char **argv)
{
    Cleanup clean;
    int result = clean.execute(argc, argv);
    return result;
}