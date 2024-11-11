#ifndef CONFIG_GENERATOR_H
#define CONFIG_GENERATOR_H

// Function prototypes
int load_custom_config(const char *custom_config_path, char config_map[][2][256]);
const char* get_custom_value(const char *param, char config_map[][2][256], int map_size);
void generate_postgresql_conf(const char *custom_config_path);

#endif // CONFIG_GENERATOR_H