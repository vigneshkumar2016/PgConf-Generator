#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/config_generator.h"

void print_usage() {
    printf("Usage: ./pg_config_generator --generate-config-file [--read-custom-config <custom_config_file>]\n");
}

int main(int argc, char *argv[]) {
    char *custom_config_file = NULL;
    int generate_config = 0;

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--generate-config-file") == 0) {
            generate_config = 1;
        } else if (strcmp(argv[i], "--read-custom-config") == 0 && i + 1 < argc) {
            custom_config_file = argv[i + 1];
            i++;  // Skip the next argument because it's the file name
        } else {
            print_usage();
            return 1;
        }
    }

    if (generate_config) {
        // Generate the PostgreSQL config file
        generate_postgresql_conf(custom_config_file);
    } else {
        print_usage();
    }

    return 0;
}