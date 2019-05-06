#include "header.h"

int main(int argc, char *argv[]) {
    unsigned int n;
    if (argc == 1) {
        return avl("in.txt", "out.txt");
    } else if (argc == 3) {
        return avl(argv[1], argv[2]);
    } else {
        print_help();
        return 1;
    }
}