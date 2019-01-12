#include <iostream>
#include "Main.h"

// using namespace boot;
int main(int argc, char *argv[]) {
    try {
        Main maini;
        maini.main(argc, argv);
        return 0;
    } catch (const char *exception) {
        printf("%s",exception);
    }
}