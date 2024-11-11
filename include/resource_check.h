#ifndef RESOURCE_CHECK_H
#define RESOURCE_CHECK_H

int calculate_max_connections();
int calculate_shared_buffers();
int calculate_work_mem();
int calculate_maintenance_work_mem();
int calculate_effective_cache_size();
int calculate_checkpoint_segments();
int calculate_wal_buffers();
int calculate_autovacuum_max_workers();
int calculate_max_parallel_workers();
int calculate_max_worker_processes();

#endif