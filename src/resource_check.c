#include "../include/resource_check.h"
#include <sys/sysinfo.h>

int calculate_max_connections() {
    struct sysinfo info;
    sysinfo(&info);
    return (info.totalram / (256 * 1024 * 1024));  // Example: 1 connection per 256MB of RAM
}

int calculate_shared_buffers() {
    struct sysinfo info;
    sysinfo(&info);
    return (info.totalram / (4 * 1024 * 1024));  // Set shared_buffers to 25% of total RAM
}

int calculate_work_mem() {
    struct sysinfo info;
    sysinfo(&info);
    return (info.totalram / (256 * 1024));  // 4MB per GB of RAM
}

int calculate_maintenance_work_mem() {
    struct sysinfo info;
    sysinfo(&info);
    return (info.totalram / (256 * 1024));  // Maintenance work_mem: 4MB per GB of RAM
}

int calculate_effective_cache_size() {
    struct sysinfo info;
    sysinfo(&info);
    return (info.totalram / (2 * 1024 * 1024));  // Effective cache size: 50% of total RAM
}

int calculate_checkpoint_segments() {
    return 16;  // A reasonable default for checkpoint_segments
}

int calculate_wal_buffers() {
    return 16;  // Default wal_buffers size in MB
}

int calculate_autovacuum_max_workers() {
    return 3;  // Default value for autovacuum_max_workers
}

int calculate_max_parallel_workers() {
    return 8;  // Default value for max_parallel_workers
}

int calculate_max_worker_processes() {
    return 8;  // Default value for max_worker_processes
}