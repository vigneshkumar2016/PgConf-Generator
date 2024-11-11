#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config_generator.h"

// Function to read parameters from custom.conf and return a mapping
int load_custom_config(const char *custom_config_path, char config_map[][2][256]) {
    FILE *file = fopen(custom_config_path, "r");
    if (!file) {
        perror("Custom config file empty or NULL");
        return 0;
    }

    int index = 0;
    while (fscanf(file, "%255s = %255s\n", config_map[index][0], config_map[index][1]) != EOF) {
        index++;
        if (index >= 100) break; // Limit to 100 custom parameters
    }

    fclose(file);
    return index;
}

// Function to find a parameter value in the custom config map
const char* get_custom_value(const char *param, char config_map[][2][256], int map_size) {
    for (int i = 0; i < map_size; i++) {
        if (strcmp(config_map[i][0], param) == 0) {
            return config_map[i][1];
        }
    }
    return NULL;  // Return NULL if parameter not found
}

void generate_postgresql_conf(const char *custom_config_path) {
    // Load custom configuration overrides
    char config_map[100][2][256]; // Map of parameter name -> value
    int custom_config_size = load_custom_config(custom_config_path, config_map);

    // Default values
    const char *default_port = "5432";
    const char *default_data_dir = "/var/lib/postgresql/data";
    const char *default_log_dir = "/var/log/postgresql";
    const char *default_max_connections = "100";
    const char *default_shared_buffers = "128MB";
    const char *default_work_mem = "4MB";
    const char *default_maintenance_work_mem = "64MB";
    const char *default_effective_cache_size = "4GB";
    const char *default_checkpoint_segments = "16";
    const char *default_wal_buffers = "16MB";
    const char *default_autovacuum_max_workers = "3";
    const char *default_max_parallel_workers = "8";
    const char *default_max_worker_processes = "8";

    // Open file to write the PostgreSQL configuration
    FILE *fp = fopen("postgresql.conf", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    // Writing configuration values to the postgresql.conf file
    fprintf(fp, "# PostgreSQL configuration file generated by config_generator\n\n");

    // Override values from custom.conf if provided
    const char *custom_value;

    // Read parameters from custom.conf
    custom_value = get_custom_value("port", config_map, custom_config_size);
    fprintf(fp, "port = %s\n", custom_value ? custom_value : default_port); // Use custom or default

    custom_value = get_custom_value("data_directory", config_map, custom_config_size);
    fprintf(fp, "data_directory = '%s'\n", custom_value ? custom_value : default_data_dir);

    custom_value = get_custom_value("log_directory", config_map, custom_config_size);
    fprintf(fp, "log_directory = '%s'\n", custom_value ? custom_value : default_log_dir);

    custom_value = get_custom_value("max_connections", config_map, custom_config_size);
    fprintf(fp, "max_connections = %s\n", custom_value ? custom_value : default_max_connections);

    custom_value = get_custom_value("shared_buffers", config_map, custom_config_size);
    fprintf(fp, "shared_buffers = '%s'\n", custom_value ? custom_value : default_shared_buffers);

    custom_value = get_custom_value("work_mem", config_map, custom_config_size);
    fprintf(fp, "work_mem = '%s'\n", custom_value ? custom_value : default_work_mem);

    custom_value = get_custom_value("maintenance_work_mem", config_map, custom_config_size);
    fprintf(fp, "maintenance_work_mem = '%s'\n", custom_value ? custom_value : default_maintenance_work_mem);

    custom_value = get_custom_value("effective_cache_size", config_map, custom_config_size);
    fprintf(fp, "effective_cache_size = '%s'\n", custom_value ? custom_value : default_effective_cache_size);

    custom_value = get_custom_value("checkpoint_segments", config_map, custom_config_size);
    fprintf(fp, "checkpoint_segments = %s\n", custom_value ? custom_value : default_checkpoint_segments);

    custom_value = get_custom_value("wal_buffers", config_map, custom_config_size);
    fprintf(fp, "wal_buffers = '%s'\n", custom_value ? custom_value : default_wal_buffers);

    custom_value = get_custom_value("autovacuum_max_workers", config_map, custom_config_size);
    fprintf(fp, "autovacuum_max_workers = %s\n", custom_value ? custom_value : default_autovacuum_max_workers);

    custom_value = get_custom_value("max_parallel_workers", config_map, custom_config_size);
    fprintf(fp, "max_parallel_workers = %s\n", custom_value ? custom_value : default_max_parallel_workers);

    custom_value = get_custom_value("max_worker_processes", config_map, custom_config_size);
    fprintf(fp, "max_worker_processes = %s\n", custom_value ? custom_value : default_max_worker_processes);

    fprintf(fp, "max_wal_size = '1GB'\n");
    fprintf(fp, "min_wal_size = '80MB'\n");
    fprintf(fp, "wal_level = 'replica'\n");
    fprintf(fp, "archive_mode = on\n");

    // Archive command and log line prefix
    const char *archive_source = "%p";  // Placeholder for source path
    const char *archive_target = "%f";  // Placeholder for target path
    fprintf(fp, "archive_command = 'cp %s /var/lib/postgresql/archive/%s'\n", archive_source, archive_target);

    fprintf(fp, "log_line_prefix = '%m [%%p] %%q%%u@%%d ' # Add custom log format\n");

    // Default values for logging, can also be overridden by custom.conf
    custom_value = get_custom_value("log_statement", config_map, custom_config_size);
    fprintf(fp, "log_statement = '%s'\n", custom_value ? custom_value : "ddl");

    custom_value = get_custom_value("log_duration", config_map, custom_config_size);
    fprintf(fp, "log_duration = '%s'\n", custom_value ? custom_value : "on");

    fclose(fp);
}